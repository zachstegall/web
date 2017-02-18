<?php

include_once "../result.inc";
include_once "../db.inc";

class AlbumArtistList
{
  public $albumartists = array();
}

class AlbumArtist
{
  public $id = "";
  public $title = "";

  function AlbumArtist()
  {
    $this->id = "";
    $this->title = "";
  }

  function getList()
  {
    $aal = new AlbumArtistList();
    $albumartists = array();
    $db = new DB();
    $dbu = $db->getAlbumArtists();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $aa = new AlbumArtist();
        $aa->id = $o['id'];
        $aa->title = $o['title'];

        $albumartists[] = $aa;
      }
    }

    $aal->albumartists = $albumartists;
    return $aal;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createAlbumArtist($id, $title);
		return $ret;
	}
}

?>
