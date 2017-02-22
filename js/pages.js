function addLinks ( div, curpage ) {
  var innerDiv = document.createElement("div");
  innerDiv.setAttribute("id", "links");

  if ( curpage != "hello" )
  {
    var a = document.createElement("a");
    a.setAttribute("id", "link");
    a.setAttribute("onclick", "next( this.innerHTML, true )");
    a.appendChild(document.createTextNode("hello"));
    innerDiv.appendChild(a);
  }

  if ( curpage != "note" )
  {
    var a = document.createElement("a");
    a.setAttribute("id", "link");
    a.setAttribute("onclick", "next( this.innerHTML, false )");
    a.appendChild(document.createTextNode("note"));
    innerDiv.appendChild(a);
  }

  div.appendChild(innerDiv);
}

function buildHello () {
  var div = document.createElement("div");
  div.setAttribute("id", "hello");

  var header = document.createElement("h2");
  var headerTextNode = document.createTextNode("hello");
  header.appendChild(headerTextNode);
  div.appendChild(header);
  addLinks(div, "hello");

  var paragraph = document.createElement("p");
  paragraph.setAttribute("id", "last");
  var paragraphText = "zach stegall<br>sde, mobile - alexa<br>" + getAge();
  paragraph.innerHTML = paragraphText;

  div.appendChild(paragraph);
  document.getElementById("main").appendChild(div);

  return div;
}

function buildNote () {
  // -- Header Display
  var div = document.createElement("div");
  div.setAttribute("id", "note");

  var h2 = document.createElement("h2");
  var h2TextNode = document.createTextNode("note");
  h2.appendChild(h2TextNode);
  div.appendChild(h2);
  addLinks(div, "note");
  // --

  $.get("data/notes.json", function(response) {
    var postArray = response.notes;

    // Outer div
    var noteBody = document.createElement("div");
    noteBody.setAttribute("id", "notebody");

    for (var i = 0; i < postArray.length; i++)
    {
      var b = postArray[i];
      var bodySection = document.createElement("div");
      bodySection.setAttribute("id", "notebodysection");

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

      if (i == (postArray.length-1))
        p.setAttribute("id", "last");

      bodySection.appendChild(h3);
      bodySection.appendChild(h4);
      bodySection.appendChild(p);
      noteBody.appendChild(bodySection);
    }

    div.appendChild(noteBody);

    document.getElementById("main").appendChild(div);

    animateIn( div );
  });

  return div;
}
