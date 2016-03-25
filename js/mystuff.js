var gallery;
var msnry;
var columnWidth = window.innerWidth/Math.ceil(window.innerWidth/120);
var imageClasses =
[
{imgPath: "img\\1.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\2.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\3.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\4.jpg", classString: "grid-item"},
// {imgPath: "img\\5.jpg", classString: "grid-item"},
// {imgPath: "img\\6.jpg", classString: "grid-item"},
// {imgPath: "img\\7.jpg", classString: "grid-item"},
// {imgPath: "img\\8.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\9.jpg", classString: "grid-item"},
// {imgPath: "img\\10.jpg", classString: "grid-item"},
// {imgPath: "img\\11.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\12.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\13.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\14.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\15.jpg", classString: "grid-item"},
// {imgPath: "img\\16.jpg", classString: "grid-item"},
// {imgPath: "img\\17.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\18.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\19.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\20.jpg", classString: "grid-item"},
// {imgPath: "img\\21.jpg", classString: "grid-item"},
// {imgPath: "img\\22.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\23.jpg", classString: "grid-item"},
// {imgPath: "img\\24.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\25.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\26.jpg", classString: "grid-item"},
// {imgPath: "img\\27.jpg", classString: "grid-item"},
// {imgPath: "img\\28.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\29.jpg", classString: "grid-item"},
// {imgPath: "img\\30.jpg", classString: "grid-item"},
// {imgPath: "img\\31.jpg", classString: "grid-item grid-item--width2"},
// {imgPath: "img\\32.jpg", classString: "grid-item"},
// {imgPath: "img\\33.jpg", classString: "grid-item"},
// {imgPath: "img\\34.jpg", classString: "grid-item"},
// {imgPath: "img\\35.jpg", classString: "grid-item"},
// {imgPath: "img\\36.jpg", classString: "grid-item"},
// {imgPath: "img\\37.jpg", classString: "grid-item"},
// {imgPath: "img\\38.jpg", classString: "grid-item"},
// {imgPath: "img\\39.jpg", classString: "grid-item"},
// {imgPath: "img\\40.jpg", classString: "grid-item"},
// {imgPath: "img\\41.jpg", classString: "grid-item"},
// {imgPath: "img\\42.jpg", classString: "grid-item"},
// {imgPath: "img\\43.jpg", classString: "grid-item"},
// {imgPath: "img\\44.jpg", classString: "grid-item"},
// {imgPath: "img\\45.jpg", classString: "grid-item"},
// {imgPath: "img\\46.jpg", classString: "grid-item"},
// {imgPath: "img\\47.jpg", classString: "grid-item"},
// {imgPath: "img\\48.jpg", classString: "grid-item"},
// {imgPath: "img\\49.jpg", classString: "grid-item"}
];

var photoSwapNum = 0;

function openPhotoSwipe(myIndex) {

    var pswpElement = document.querySelectorAll('.pswp')[0];

    var images = document.getElementsByClassName('grid-img');
    var items = [];

    // build items array
    for (var i = 0; i < images.length; i++) {
        var image = new Image();
        image.src = images[i].src;

        items.push({
            src: image.src,
            w:   image.width,
            h:   image.height
        })

    }

    // define options
    var options = {

        index: myIndex,

        history: false,
        focus: false,
        bgOpacity: 0.75,

        showAnimationDuration: 0,
        hideAnimationDuration: 0,
        closeEl:false,
        fullscreenEl: false,
        zoomEl: false,
        shareEl: false,
        counterEl: false,
        shareEl: false,

        modal: false,
        closeOnScroll: false,

        loop: true,

        getDoubleTapZoom: function(isMouseClick, item) {}

    };

    gallery = new PhotoSwipe( pswpElement, PhotoSwipeUI_Default, items, options);
    gallery.init();

}

function loadImages() {

    var images = [];

    for (var i = 0; i < imageClasses.length; i++) {

        images[i] = new Image();
        images[i].classString = imageClasses[i].classString;
        images[i].onload = function() {

            // create the div for the item.
            var element = document.createElement("div");
            element.className = this.classString;

            if (this.classString == "grid-item") {

                element.style.width = columnWidth.toString() + "px";

            } else {

                element.style.width = (columnWidth*2).toString() + "px";

            }

            document.getElementById("masonry-grid").appendChild(element);

            // create the image
            var image = document.createElement("img");
            image.setAttribute("src", this.src);
            image.className = "grid-img";
            image.setAttribute("onclick", "openPhotoSwipe(" + photoSwapNum + ");");
            element.appendChild(image);
            photoSwapNum++;

            msnry.appended(element);

        }
        images[i].src = imageClasses[i].imgPath;
    }

}

function startTyping() {

    $(".typeText").typed({
      stringsElement: $('#typed-strings'),
      typeSpeed: 10,
      backSpeed: 5,
    });

}

function generateMasonryTiles() {

    var elem = document.querySelector('.grid');
    msnry = new Masonry( elem, {
      // options
      percentPosition: true,
      itemSelector: '.grid-item',
      columnWidth: columnWidth
    });

    loadImages();

}

window.onload = $(function(){

    generateMasonryTiles();
    startTyping();

});