function buildSongs () {
  var div = document.getElementById("content");

  $.get("data/songs.json", function(response) {
    var postArray = response.songs;

    for (var i = 0; i < postArray.length; i++)
    {
      var b = postArray[i];

      var h3 = document.createElement("h3");
      h3.appendChild(document.createTextNode( b.title ));

      var h4 = document.createElement("h4");
      h4.appendChild(document.createTextNode( getDateString(b.ts) ));

      var img = document.createElement("img");
      img.setAttribute("id", "album");
      img.setAttribute("src", "images/" + b.img);

      var p = document.createElement("p");
      p.innerHTML = b.body + "<br><br>";
      p.appendChild(img);

      div.appendChild(h3);
      div.appendChild(h4);
      div.appendChild(p);
    }
  });
}
