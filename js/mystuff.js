var gallery;
var timer;
var timedFunction;

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

    createPhotoScapeTimer();

}

$.get( 'img/1.jpg', function( content ) {
  // wrap content in jQuery object
  var $content = $( content );
  // add jQuery object
  $grid.append( $content ).masonry( 'appended', $content );
});

function createPhotoScapeTimer() {
    // window.clearInterval(timer);
    // timer = window.setInterval(timedFunction, 2000);
}

window.onload = $(function(){

    $(".typeText").typed({
      stringsElement: $('#typed-strings'),
      typeSpeed: 10,
      backSpeed: 5,
    });

    timedFunction = function(){
        if (gallery != null) {
            gallery.next();
        }
    }


    var value = window.innerWidth/Math.ceil(window.innerWidth/120);

    var elementsToChange = document.getElementsByClassName("grid-item");
    for (var integer = 0; integer < elementsToChange.length; integer++) {
        elementsToChange[integer].style.width = value.toString() + "px";
    }

    elementsToChange = document.getElementsByClassName("grid-item--width2");
    for (var integer = 0; integer < elementsToChange.length; integer++) {
        elementsToChange[integer].style.width = (value*2).toString() + "px";
    }

    var elem = document.querySelector('.grid');
    var msnry = new Masonry( elem, {
      // options
      percentPosition: true,
      itemSelector: '.grid-item',
      columnWidth: value
    });

});

window.addEventListener("keydown", function(event){
    if (event.keyCode = 37 || event.keyCode == 39) {
        createPhotoScapeTimer();
    }
});

window.addEventListener("touchmove", function(){
    createPhotoScapeTimer();
});