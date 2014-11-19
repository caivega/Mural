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
- [ ] font
- [ ] globalCompositeOperation
- [ ] imageSmoothEnabled
- [ ] lineCap
- [ ] lineJoin
- [ ] miterLimit
- [ ] shadowBlur
- [ ] shadowColor
- [ ] shadowOffsetX
- [ ] shadowOffsetY
- [ ] texAlign
- [ ] textBaseline
- [ ] arcTo
- [ ] bezierCurveTo
- [ ] quadraticCurveTo
- [ ] measureText
- [ ] setTrasform
- [ ] transform
- [ ] createLinearGradient
- [ ] createRadialGradient
- [ ] createPattern

## Build and Run
1. Download Cinder from [http://libcinder.org/download/](http://libcinder.org/download/) and unzip it
2. Create a `apps` folder at the root
3. Clone the repo into `apps`: `git clone https://github.com/pixelpicosean/Mural.git`
4. Open project file and have fun
*Development using Cinder v0.8.6, the dev version not tested yet*

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

[CanvasRenderingContext2D]: https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D
[Cinder]: https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D
[duktape]: http://duktape.org/
[Ejecta]: http://impactjs.com/ejecta
[Ejecta-X]: http://wizcorp.github.io/Ejecta-X/
[Cocoonjs]: https://www.ludei.com/cocoonjs/
[Node-webkit]: https://github.com/rogerwang/node-webkit
