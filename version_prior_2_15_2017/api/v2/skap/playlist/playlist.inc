<?php

include_once "../result.inc";
include_once "../db.inc";

class PlaylistList
{
  public $playlists = array();
}

class Playlist
{
  public $id = "";
  public $title = "";

  function Song()
  {
    $this->id = "";
    $this->title = "";
  }

  function getList()
  {
    $pll = new PlaylistList();
    $playlists = array();
    $db = new DB();
    $dbu = $db->getPlaylists();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $p = new Playlist();
        $p->id = $o['id'];
        $p->title = $o['title'];

        $playlists[] = $p;
      }
    }

    $pll->playlists = $playlists;
    return $pll;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createPlaylist($id, $title);
		return $ret;
	}
}

?>
