// Make 'window' the global scope
self = window = this;
window.top = window.parent = window;

(function(window) {
    // RAF & Timer implementation
    var animFrameCallbacks1 = [], animFrameCallbacks2 = [], currCallbackIdx = 1, rafRemoveList1 = [], rafRemoveList2 = [], nextAnimFrameCallbackID = 0;
    var timeoutCallbacks = [], timeoutRemoveList = [], nextTimeoutCallbackID = 0;
    var intervalCallbacks = [], intervalRemoveList = [], nextIntervalCallbackID = 0;
    __MURAL__.tickAnimFrame = function tickAnimFrame() {
        var i, len;
        for (i = 0, len = rafRemoveList1.length; i < len; i++) {
            animFrameCallbacks1.splice(animFrameCallbacks1.indexOf(rafRemoveList1[i]), 1);
        }
        for (i = 0, len = rafRemoveList2.length; i < len; i++) {
            animFrameCallbacks2.splice(animFrameCallbacks1.indexOf(rafRemoveList2[i]), 1);
        }
        rafRemoveList1.length = 0;
        rafRemoveList2.length = 0;
        if (currCallbackIdx === 1) {
            currCallbackIdx = 2;
            for (i = 0, len = animFrameCallbacks1.length; i < len; i++) {
                animFrameCallbacks1[i].callback();
            }
            animFrameCallbacks1.length = 0;
        }
        else {
            currCallbackIdx = 1;
            for (i = 0, len = animFrameCallbacks2.length; i < len; i++) {
                animFrameCallbacks2[i].callback();
            }
            animFrameCallbacks2.length = 0;
        }

        var now = Date.now();
        // setTimeout
        for (i = 0, len = timeoutRemoveList.length; i < len; i++) {
            timeoutCallbacks.splice(timeoutCallbacks.indexOf(timeoutRemoveList[i]), 1);
        }
        timeoutRemoveList.length = 0;
        i = timeoutCallbacks.length - 1;
        do {
            if (i < 0) {
                break;
            }
            if (timeoutCallbacks[i].time < now) {
                timeoutCallbacks[i].callback();
                timeoutCallbacks.splice(i, 1);
            }
        }
        while (i--);
        // setInterval
        for (i = 0, len = intervalRemoveList.length; i < len; i++) {
            intervalCallbacks.splice(intervalCallbacks.indexOf(intervalRemoveList[i]), 1);
        }
        intervalRemoveList.length = 0;
        i = intervalCallbacks.length - 1;
        do {
            if (i < 0) {
                break;
            }
            if (intervalCallbacks[i].time < now) {
                intervalCallbacks[i].callback();
                intervalCallbacks[i].time = now + intervalCallbacks[i].interval;
            }
        }
        while (i--);
    };


    // window.devicePixelRatio = __MURAL__.devicePixelRatio;
    window.innerWidth = __MURAL__.screenWidth;
    window.innerHeight = __MURAL__.screenHeight;

    window.screen = {
        availWidth: window.innerWidth,
        availHeight: window.innerHeight
    };

    window.navigator = {
        language: __MURAL__.language,
        userAgent: __MURAL__.userAgent,
        appVersion: __MURAL__.appVersion,
        platform: __MURAL__.platform
    };

    // The console object
    window.console = {
        _log: function(level, args) {
            var txt = level + ':';
            for (var i = 0, len = args.length; i < len; i++) {
                txt += ' ' + (typeof args[i] === 'string' ? args[i] : JSON.stringify(args[i]));
            }
            print(txt);
        },

        assert: function() {
            var args = Array.prototype.slice.call(arguments);
            var assertion = args.shift();
            if (!assertion) {
                print('Assertion failed: ' + args.join(', '));
            }
        }
    };
    window.console.debug = function() { window.console._log('DEBUG', arguments); };
    window.console.info =  function() { window.console._log('INFO', arguments); };
    window.console.warn =  function() { window.console._log('WARN', arguments); };
    window.console.error = function() { window.console._log('ERROR', arguments); };
    window.console.log =   function() { window.console._log('LOG', arguments); };

    var consoleTimers = {};
    console.time = function(name) {
        consoleTimers[name] = Date.now();
    };

    console.timeEnd = function(name) {
        var timeStart = consoleTimers[name];
        if (!timeStart) {
            return;
        }

        var timeElapsed = Date.now() - timeStart;
        console.log(name + ': ' + timeElapsed + 'ms');
        delete consoleTimers[name];
    };

    // Timers
    window.performance = {
        now: function() {
            return Date.now();
        }
    };
    window.setTimeout = function(cb, t) {
        var id = nextTimeoutCallbackID++;
        timeoutCallbacks.push({
            id: id,
            callback: cb,
            time: Date.now() + t
        });
        return id;
    };
    window.setInterval = function(cb, t) {
        var id = nextIntervalCallbackID++;
        intervalCallbacks.push({
            id: id,
            callback: cb,
            time: Date.now() + t,
            interval: t
        });
        return id;
    };
    window.clearTimeout = function(id) {
        var i = timeoutCallbacks.length - 1;
        do {
            if (i < 0) {
                break;
            }
            if (timeoutCallbacks[i].id === id) {
                // timeoutCallbacks.splice(i, 1);
                timeoutRemoveList.push(timeoutCallbacks[i]);
                return;
            }
        }
        while (i--);
    };
    window.clearInterval = function(id) {
        var i = intervalCallbacks.length - 1;
        do {
            if (i < 0) {
                break;
            }
            if (intervalCallbacks[i].id === id) {
                // intervalCallbacks.splice(i, 1);
                intervalRemoveList.push(intervalCallbacks[i]);
                return;
            }
        }
        while (i--);
    };
    window.requestAnimationFrame = function(cb) {
        var id = nextAnimFrameCallbackID++;
        if (currCallbackIdx === 1) {
            animFrameCallbacks1.push({
                id: id,
                callback: cb
            });
        }
        else {
            animFrameCallbacks2.push({
                id: id,
                callback: cb
            });
        }
        return id;
    };
    window.cancelAnimationFrame =function(id) {
        for (var i = 0, len = animFrameCallbacks1.length; i < len; i++) {
            if (animFrameCallbacks1[i].id === id) {
                rafRemoveList1.push(animFrameCallbacks1[i]);
                return;
            }
        }
        for (var i = 0, len = animFrameCallbacks2.length; i < len; i++) {
            if (animFrameCallbacks2[i].id === id) {
                rafRemoveList2.push(animFrameCallbacks2[i]);
                return;
            }
        }
    };

    // The native Image, Audio, HttpRequest and LocalStorage class mimic the real elements
    window.Image = window.HTMLImageElement = __MURAL__.Image;

    __MURAL__.eventMixin.call(__MURAL__.Canvas.prototype);
    window.HTMLCanvasElement = __MURAL__.Canvas;
    window.CanvasRenderingContext2D = __MURAL__.CanvasContext;
    window.__default__canvas__ = new __MURAL__.Canvas();

    // window.Audio = __MURAL__.Audio;
    // window.Video = __MURAL__.Video;
    // window.XMLHttpRequest = __MURAL__.HttpRequest;
    // window.WebSocket = __MURAL__.WebSocket;

    (function(window) {
        var handler = {
            get: function (targ, key, recv) {
                return targ[key] || targ.getItem(key);
            },
            set: function (targ, key, val, recv) {
                targ.setItem(key, val);
                return true;
            },
            deleteProperty: function (targ, key) {
                return false;
            }
        };
        var localStorage = new __MURAL__.LocalStorage();
        window.localStorage = new Proxy(localStorage, handler);
    })(window);

    // Setup window events
    window.Event = window.MouseEvent = window.KeyboardEvent = __MURAL__.Event;
    __MURAL__.eventMixin.call(window);

    window.location = { href: 'index' };

    // Set up a "fake" HTMLElement
    HTMLElement = function(tagName) {
        this.tagName = tagName.toUpperCase();
        this.children = [];
        this.style = {};
    };

    HTMLElement.prototype.appendChild = function(element) {
        this.children.push(element);

        // If the child is a script element, begin to load it
        if (element.tagName && element.tagName.toLowerCase() == 'script') {
            window.setTimeout(function() {
                // TODO: module search and load
                /*require(element.src);
                if (element.onload) {
                    element.onload({
                        type: 'load',
                        currentTarget: element
                    });
                }*/
                print("script loading not available yet");
            }, 1);
        }
    };

    HTMLElement.prototype.insertBefore = function(newElement, existingElement) {
        // Just append; we don't care about order here
        this.children.push(newElement);
    };

    HTMLElement.prototype.removeChild = function(node) {
        for (var i = this.children.length; i--;) {
            if (this.children[i] === node) {
                this.children.splice(i, 1);
            }
        }
    };

    HTMLElement.prototype.getBoundingClientRect = function() {
        return {
            top: 0,
            left: 0,
            width: window.innerWidth,
            height: window.innerHeight
        };
    };

    HTMLElement.prototype.setAttribute = function(attr, value) {
        this[attr] = value;
    };

    HTMLElement.prototype.getAttribute = function(attr) {
        return this[attr];
    };

    HTMLElement.prototype.addEventListener = function(event, method) {
        if (event === 'load') {
            this.onload = method;
        }
    };

    HTMLElement.prototype.removeEventListener = function(event, method) {
        if (event === 'load') {
            this.onload = undefined;
        }
    };

    // The document object
    window.document = {
        readystate: 'complete',
        documentElement: window,
        location: window.location,
        visibilityState: 'visible',
        hidden: false,
        style: {},

        head: new HTMLElement('head'),
        body: new HTMLElement('body'),

        createElement: function(name) {
            if (name === 'canvas') {
                var canvas = new __MURAL__.Canvas();
                canvas.type = 'canvas';
                return canvas;
            }
            else if (name == 'audio') {
                return new __MURAL__.Audio();
            }
            else if (name == 'video') {
                return new __MURAL__.Video();
            }
            else if (name === 'img') {
                return new window.Image();
            }
            else if (name === 'input' || name === 'textarea') {
                return new __MURAL__.KeyInput();
            }
            return new HTMLElement(name);
        },

        getElementById: function(id) {
            if (id === 'canvas') {
                return window.__default__canvas__;
            }
            return null;
        },

        getElementsByTagName: function(tagName) {
            var elements = [], children, i;

            tagName = tagName.toLowerCase();

            if (tagName === 'head') {
                elements.push(document.head);
            }
            else if (tagName === 'body') {
                elements.push(document.body);
            }
            else {
                children = document.body.children;
                for (i = 0; i < children.length; i++) {
                    if (children[i].tagName.toLowerCase() === tagName) {
                        elements.push(children[i]);
                    }
                }
                children = undefined;
            }
            return elements;
        },

        dispatchMouseEvent: function(type, which, buttons, altKey, ctrlKey, metaKey, shiftKey, x, y, movementX, movementY) {
            var evt = document.createEvent(type);

            evt.altKey = altKey;
            evt.ctrlKey = ctrlKey;
            evt.metaKey = metaKey;
            evt.shiftKey = shiftKey;

            evt.which = which;
            evt.button = (which - 1 > 0) ? (which - 1) : 0;
            evt.buttons = buttons;
            evt.clientX = evt.screenX = x;
            evt.clientY = evt.screenY = y;
            evt.movementX = movementX;
            evt.movementY = movementY;

            document.dispatchEvent(evt);
            if (window.__default__canvas__) {
                window.__default__canvas__.dispatchEvent(evt);
            }
        },

        dispatchKeyEvent: function(type, keyCode, code, metaKey) {
            var evt = document.createEvent(type);
            evt.keyCode = keyCode;
            evt.code = code;
            evt.metaKey = metaKey;
            document.dispatchEvent(evt);
            if (window.__default__canvas__) {
                window.__default__canvas__.dispatchEvent(evt);
            }
        },

        dispatchNamedEvent: function(type) {
            document.dispatchEvent(document.createEvent(type));
        }
    };
    __MURAL__.eventMixin.call(window.document);

    // Utils
    window.getAverageFPS = __MURAL__.getAverageFPS;

})(this);
