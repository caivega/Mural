# Mural
---
This is an experimental project which implements [CanvasRenderingContext2D][CanvasRenderingContext2D] using amazing [Cinder][Cinder] framework and [duktape][duktape]. 

It's design to be something like **Ejecta for Desktop**. The ONLY reason that I start this instead of using [Node-webkit][Node-webkit] is the executable file size. Nearly 100m size for a simple game which I want to share with friends sounds crazy and no one want to download another **Chrome** just to play a it.

I'm very proud of the result, even it's not completed, lots of features not supported actually. The compiled executable file is about 2m and less than 1m gzipped (I know it's not internet thing :D).

## Supported APIs
### General DOM stuff
See `assets/scripts/mural.js`
### LocalStorage
Not implemented yet, but already under development.
### CanvasRenderingContext2D
- [x] strokeStyle, fillStyle (only color support for now)
- [x] globalAlpha
- [x] lineWidth
- [x] save, restore
- [x] beginPath, closePath
- [x] moveTo, lineTo
- [x] rect, arc
- [x] stroke, fill
- [x] strokeRect, fillRect
- [x] strokeText, fillText (this 2 method performs the same)
- [x] drawImage (supports both Image and CanvasRenderingContext2D)
- [x] translate, rotate, scale
- [x] clearRect
- [x] bezierCurveTo
- [x] arcTo
- [x] quadraticCurveTo
- [ ] font
- [ ] globalCompositeOperation
- [ ] imageSmoothingEnabled
- [ ] lineCap
- [ ] lineJoin
- [ ] miterLimit
- [ ] shadowBlur
- [ ] shadowColor
- [ ] shadowOffsetX
- [ ] shadowOffsetY
- [ ] texAlign
- [ ] textBaseline
- [ ] measureText
- [ ] setTrasform
- [ ] transform
- [ ] createLinearGradient
- [ ] createRadialGradient
- [ ] createPattern

## Progress of developing
I always prefer [Trello][trello] for project management, the tasks list can be found here [Mural at Trello][mural-trello]

## Build and Run
1. Download Cinder from [http://libcinder.org/download/](http://libcinder.org/download/) and unzip it
2. Create a `apps` folder at the root
3. Clone the repo into `apps`: `git clone https://github.com/pixelpicosean/Mural.git`
4. Open project file and have fun
*Development using Cinder v0.8.6, the dev version not tested yet*

## Hacking
It's better to compile in release mode and directly modify `index.js` in `assets/scripts` to see the result.
If you want to help develop, please run in debug mode and see what's happening.
Note that the release version will simple ignore issue (even fatal errors) but will log everything including script syntax in debug mode.

## Supported Platforms
Currently only support Windows and OSX._([Cinder](Cinder) only support Windows, OSX and iOS)_
For other platforms plz try:
- [Ejecta][Ejecta](iOS)
- [Ejecta-X][Ejecta-X](Android)
- [Cocoonjs][Cocoonjs](iOS & Android)
- [Node-webkit][Node-webkit](Windows, OSX and Linux)

## Note
Currently JavaScript API is not **safe**. By saying not **safe** I mean any miss use will immediatly **crash** the app.
Also the JavaScript is running under `strict` mode which is mostly the reason of a **crash** :P

---

The MIT License (MIT)

Copyright (c) 2014 Sean Bohan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

[CanvasRenderingContext2D]: https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D
[Cinder]: https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D
[duktape]: http://duktape.org/
[Ejecta]: http://impactjs.com/ejecta
[Ejecta-X]: http://wizcorp.github.io/Ejecta-X/
[Cocoonjs]: https://www.ludei.com/cocoonjs/
[Node-webkit]: https://github.com/rogerwang/node-webkit
[trello]: https://trello.com
[mural-trello]: https://trello.com/b/9cpESvdR/mural
