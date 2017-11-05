'use strict'

const _cr = require("cached-request")
const _r = require("request")
const f = require("fathom-web")
const Fnode = require("fathom-web/fnode").Fnode
const utils = require("fathom-web/utils")
const util = require("util")
const domino = require("domino")
const sleep = require("sleep")
const fs = require('fs')
const url = require('url')

if(typeof(String.prototype.trim) === "undefined") {
    String.prototype.trim = function() {
        return String(this).replace(/^\s+|\s+$/g, '');
    };
}

if (typeof(Fnode.prototype.getScore) === "undefined") {
    Fnode.prototype.getScore = function() {
      // find the first score and just return it
      // return this._types.values().next().value.score
      const first = utils.first(this._types.values())
      return first != undefined ? first.score : 0
    }
}

const findParent = function(element, findCallback) {
  const parent = element.parentElement
  if (parent === undefined) {
    return undefined
  } else if (findCallback(parent)) {
    return element.parentElement;
  } else {
    return findParent(parent, findCallback)
  }
}

function scoreSort(nodes) {
  const array = Array.from(nodes)
  function compare(a, b) {
    const diff = b.getScore() - a.getScore()
    if (diff > 0) {
      return 1
    } else if (diff < 0) {
      return -1
    } else {
      return utils.domSort([a,b])
    }
  }
  // console.log(Object.getOwnPropertyNames(array[0]))
  // console.log(array.map(f => f))
  // console.log(array.sort(compare).map(f => f.element.textContent))
  return array.sort(compare);
}

const ruleset = f.ruleset,
      rule = f.rule,
      dom = f.dom,
      type = f.type,
      out = f.out

const request = _cr(_r)
request.setCacheDirectory("./cache")
request.setValue("ttl", 1000 * 3600) // millis

const list_page = ruleset(
  rule(dom(".result-info a"), out("link"))
)

const detail_page = ruleset(
  rule(dom(".gallery img"), out("img"))
)
const download = function(uri, filename, callback){
  _r.head(uri, function(err, res, body){
    console.log('content-type:', res.headers['content-type']);
    console.log('content-length:', res.headers['content-length']);
    const type = res.headers['content-type'].split("/")[1];
    _r(uri).pipe(fs.createWriteStream(filename + "." + type)).on('close', callback);
  });
}

var facts;
const urls = {
  "w4m" : "https://newyork.craigslist.org/search/cas?query=w4m&sort=date&hasPic=1",
  "wta" : "https://newyork.craigslist.org/search/wta&sort=date&hasPic=1",
  "ppp" : "https://newyork.craigslist.org/search/ppp?",
  "puppies" : "https://newyork.craigslist.org/search/sss?query=puppies&sort=rel&hasPic=1"
}

var selectedKey = "puppies"

var count = 0
for (var i = 0; i < 120*3; i+=120) {

  request({ url: urls[selectedKey] + `s=${i}&hasPic=1` }, (err, res, body) => {
    // extra toString required because body is different when responding from cache
    // probably won't work if request is not html (ie png, etc)
    // const dombody = jsdom.jsdom(body.toString())
    const d = domino.createDocument(body.toString(), true)

    facts = list_page.against(d)
    // const tits = facts.get(dom("h3")).map(f => f.element.innerHTML)
    // const links = facts.get(type("linky")).map(f => f.element.innerHTML)
    const links = facts.get("link")
      .map(f => f.element.href.trim())
      .filter(link => link.length > 5)
    links.forEach(link => {
      sleep.sleep(1);

      request({ url : link }, (err, res, body) => {
        sleep.sleep(1.0)
        if (err || !body) {
          // console.log(err)
          console.log("link early return: " + link)
          return
        }
        const d = domino.createDocument(body.toString(), true)
        const detailFacts = detail_page.against(d)
        const imgs = detailFacts.get("img").map(f => f.element.src.trim())
        console.log("link: " + imgs)

        imgs.forEach( i => {
          const imgURL = url.parse(i).pathname.slice(1); // slice to remove prefix '/'
          const filename = `images/${selectedKey}/img-${count}_${imgURL}`
          download(i,filename , _ => console.log("wrote: " + filename))
          count++
        })

      })
    })

  })

}

