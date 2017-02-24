function adjustStyle(width) {
  width = parseInt(width);
  if (width <= 414) {
    $("#size-stylesheet").attr("href", "css/thin.css");
  } else if (width <= 600) {
    $("#size-stylesheet").attr("href", "css/narrow.css");
  } else if (width <= 640) {
    $("#size-stylesheet").attr("href", "css/slim.css");
  } else if (width <= 900) {
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
