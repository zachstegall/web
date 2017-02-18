<?php

include_once "../result.inc";
include_once "../db.inc";

class AlbumList
{
  public $albums = array();
}

class Album
{
  public $id = "";
  public $title = "";

  function Album()
  {
    $this->id = "";
    $this->title = "";
  }

	function getAlbum($id)
	{
		$db = new DB();
		$o = $db->getAlbum($id);

		$a = new Album();
		$a->id = $o['id'];
		$a->title = $o['title'];
		return $a;
	}

  function getList()
  {
    $al = new AlbumList();
    $albums = array();
    $db = new DB();
    $dbu = $db->getAlbums();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $a = new Album();
        $a->id = $o['id'];
        $a->title = $o['title'];

        $albums[] = $a;
      }
    }

    $al->albums = $albums;
    return $al;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createAlbum($id, $title);
		return $ret;
	}
}

?>
