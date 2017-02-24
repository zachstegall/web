function buildNotes () {
  var div = document.getElementById("content");

  $.get("data/notes.json", function(response) {
    var postArray = response.notes;

    for (var i = 0; i < postArray.length; i++)
    {
      var b = postArray[i];

      var h3 = document.createElement("h3");
      h3.appendChild(document.createTextNode( b.title ));

      var h4 = document.createElement("h4");
      h4.appendChild(document.createTextNode( getDateString(b.ts) ));

      var p = document.createElement("p");
      p.setAttribute("class", "notes");
      p.innerHTML = b.body;

      div.appendChild(h3);
      div.appendChild(h4);
      div.appendChild(p);
    }
  });
}
