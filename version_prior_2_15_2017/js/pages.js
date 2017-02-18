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

  if ( curpage != "music" )
  {
    var a = document.createElement("a");
    a.setAttribute("id", "link");
    a.setAttribute("onclick", "next( this.innerHTML, false )");
    a.appendChild(document.createTextNode("music"));
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
/*
  if ( curpage != "snap" )
  {
    var a = document.createElement("a");
    a.setAttribute("id", "link");
    a.setAttribute("onclick", "next( this.innerHTML )");
    a.appendChild(document.createTextNode("snap"));
    innerDiv.appendChild(a);
  }
*/

  div.appendChild(innerDiv);
}

function buildHello () {
  var div = document.createElement("div");
  div.setAttribute("id", "hello");

  var header = document.createElement("h2");
  var headerTextNode = document.createTextNode("hello.");
  header.appendChild(headerTextNode);
  div.appendChild(header);
  addLinks(div, "hello");

  var paragraph = document.createElement("p");
  paragraph.setAttribute("id", "last");
  var paragraphText = "zachary stegall<br>cover media labs<br>" + getAge();
  paragraph.innerHTML = paragraphText;

  var anchorDiv = document.createElement("div");
  anchorDiv.setAttribute("id", "links");
  var anchor = document.createElement("a");
  anchor.setAttribute("id", "link");
  anchor.setAttribute("onclick", "next( this.innerHTML, false )");
  anchor.appendChild(document.createTextNode("music"));
  anchorDiv.appendChild(anchor);


  div.appendChild(paragraph);
  div.appendChild(anchorDiv);
  document.getElementById("main").appendChild(div);

  return div;
}

function buildMusic () {
  // -- Header Display
  var div = document.createElement("div");
  div.setAttribute("id", "music");

  var h2 = document.createElement("h2");
  var h2TextNode = document.createTextNode("music.");
  h2.appendChild(h2TextNode);
  div.appendChild(h2);
  addLinks(div, "music");
  // --


  // -- Get Last # Songs with their Album Image and Artist Title
  $.get( "api/v2/skap/song/many.php", { cnt: 15 }, function( response )
    {
      // Data
      var data = $.parseJSON(response);
      var songData = data.payload.songs;

      // Presentation Variables
      var aaIds = {}; // { AlbumId : ArtistId }
      var songs = {}; // { AlbumId : <SongTitle> }


      // Organize data
      for (var i = 0; i < songData.length; i++)
      {
        var s = songData[i];

        // add artist/album
        aaIds[s.album_id] = s.artist_id;

        // -- add song
        var songsForAlbum = songs[s.album_id];
        var saIndex = 0;
        if (!songsForAlbum)
          songsForAlbum = [];
        else
          saIndex = Object.keys(songsForAlbum).length;


        songsForAlbum[saIndex] = s.title;

        songs[s.album_id] = songsForAlbum;
        // --
      }


      // Loading variables
      var imageElements = {}; // { AlbumId : ImageElement }
      var titleElements = {}; // { ArtistId : <h3Element> }

      // Outer div
      var songBody = document.createElement("div");
      songBody.setAttribute("id", "musicbody");

      // Prepare elements 1 - set songs, gather ImageElements, gather h3Elements
      var i = 0;
      for (var albumId in aaIds)
      {
        var artistId = aaIds[albumId];
        var albumSongs = songs[albumId];

        // Inner div sections
        var bodySection = document.createElement("div");
        bodySection.setAttribute("id", "musicbodysection");

        var h3 = document.createElement("h3");
        var h3Img = document.createElement("img");
        h3Img.setAttribute("id", "musicimg");
        h3.appendChild(h3Img);
        imageElements[albumId] = h3Img;


        var h3Elements = titleElements[artistId];
        var h3Index = 0;
        if (!h3Elements)
          h3Elements = [];
        else
          h3Index = Object.keys(h3Elements).length;


        h3Elements[h3Index] = h3;

        titleElements[artistId] = h3Elements;


        var p = document.createElement("p");
        var pText = "";
        for (var j = 0; j < albumSongs.length; j++)
        {
          if (j == (albumSongs.length-1))
            pText = pText + albumSongs[j].toLowerCase();
          else
            pText = pText + albumSongs[j].toLowerCase() + "<br>";
        }
        p.innerHTML = pText;

        if (i == (Object.keys(aaIds).length-1))
          p.setAttribute("id", "last");

        bodySection.appendChild(h3);
        bodySection.appendChild(p);
        songBody.appendChild(bodySection);

        i++;
      }
      div.appendChild(songBody);


      // Get Album Images
      for (var albumId in imageElements)
      {
        var src = baseurl + "AlbId_" + albumId;
        var dlImage = imageElements[albumId];

        dlImage.onload = function() {

        };
        dlImage.src = src;
      }


      // Get Artist Titles
      for (var artistId in titleElements)
      {
        $.get( "api/v1/skap/artist/one.php", { id: artistId }, function( response )
        {
          data = $.parseJSON(response);
          var artist = data.payload.title;
          var artistId = data.payload.id;

          var h3Elements = titleElements[artistId];
          for (var j = 0; j < h3Elements.length; j++)
          {
            var h3 = h3Elements[j];
            h3.appendChild(document.createTextNode(" " + artist));
          }
        });
      }


      var anchorDiv = document.createElement("div");
      anchorDiv.setAttribute("id", "links");
      var anchor = document.createElement("a");
      anchor.setAttribute("id", "link");
      anchor.setAttribute("onclick", "next( this.innerHTML, false )");
      anchor.appendChild(document.createTextNode("note"));
      anchorDiv.appendChild(anchor);

      div.appendChild(anchorDiv);
      document.getElementById("main").appendChild(div);

      animateIn( div );
    });


  return div;
}

function buildNote () {
  // -- Header Display
  var div = document.createElement("div");
  div.setAttribute("id", "note");


  var h2 = document.createElement("h2");
  var h2TextNode = document.createTextNode("note.");
  h2.appendChild(h2TextNode);
  div.appendChild(h2);
  addLinks(div, "note");
  // --

  // -- Get Posts 5 at a time
  $.get( "api/v2/web/note/many.php", { cnt: 15 }, function( response )
    {
      // Data
      var data = $.parseJSON(response);
      var postArray = data.payload.posts;

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

        var p = document.createElement("p");
        p.innerHTML = b.body;
        //p.appendChild(document.createTextNode( b.body ));

        if (i == (postArray.length-1))
          p.setAttribute("id", "last");

        bodySection.appendChild(h3);
        bodySection.appendChild(h4);
        bodySection.appendChild(p);
        noteBody.appendChild(bodySection);
      }
      div.appendChild(noteBody);

      var anchorDiv = document.createElement("div");
      anchorDiv.setAttribute("id", "links");
      var anchor = document.createElement("a");
      anchor.setAttribute("id", "link");
      anchor.setAttribute("onclick", "next( this.innerHTML, true )");
      anchor.appendChild(document.createTextNode("hello"));
      anchorDiv.appendChild(anchor);

      div.appendChild(anchorDiv);
      document.getElementById("main").appendChild(div);

      animateIn( div );
    });

  return div;
}

function buildSnap () {
  var div = document.createElement("div");
  div.setAttribute("id", "snap");


  var h2 = document.createElement("h2");
  var h2TextNode = document.createTextNode("snap.");
  h2.appendChild(h2TextNode);
  div.appendChild(h2);
  addLinks(div, "snap");


  var images = [ { "id":"0", "src":"seagull.jpg", "title":"seagull", "date":"Apr 5, 16"  } ,
                 { "id":"1", "src":"fishing.jpg", "title":"fishing", "date":"Mar 3, 16" },
                 { "id":"2", "src":"surfing.jpg", "title":"surfing", "date":"Jul 24, 16" } ];
  var snapBody = document.createElement("div");
  snapBody.setAttribute("id", "snapbody");
  for (var i = 0; i < images.length; i++)
  {
    var bodySection = document.createElement("div");
    bodySection.setAttribute("id", "snapbodysection");
    var image = images[i];

    var h3 = document.createElement("h3");
    h3.appendChild(document.createTextNode(image["title"]));

    var h4 = document.createElement("h4");
    h4.appendChild(document.createTextNode(image["date"]));

    var img = document.createElement("img");
    img.setAttribute("src", image["src"]);

    bodySection.appendChild(h3);
    bodySection.appendChild(h4);
    bodySection.appendChild(img);
    snapBody.appendChild(bodySection);
  }
  div.appendChild(snapBody);

  document.getElementById("main").appendChild(div);

  return div;
}
