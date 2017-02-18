function adjustStyle(width) {
  width = parseInt(width);
  if (width <= 414) {
    $("#size-stylesheet").attr("href", "css/narrow.css");
  } else if (width <= 711) {
    $("#size-stylesheet").attr("href", "css/medium.css");
  } else {
    $("#size-stylesheet").attr("href", "css/wide.css");
  }
}

$(function() {
  adjustStyle($(this).width());
  $(window).resize(function() {
    adjustStyle($(this).width());
  });
});


function animateIn( div ) {
  $(div).animate({
    opacity: 1.0
  },
  700, function() {
    // Animation complete.
  });
}
