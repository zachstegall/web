<?php

include_once "../result.inc";
include_once "../db.inc";

class ArtistList
{
  public $artists = array();
}

class Artist
{
  public $id = "";
  public $title = "";

  function Artist()
  {
    $this->id = "";
    $this->title = "";
  }

	function getArtist($id)
	{
		$db = new DB();
		$o = $db->getArtist($id);
		
		$a = new Artist();
		$a->id = $o['id'];
		$a->title = $o['title'];
		return $a;
	}

  function getList()
  {
    $al = new ArtistList();
    $artists = array();
    $db = new DB();
    $dbu = $db->getArtists();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $a = new Artist();
        $a->id = $o['id'];
        $a->title = $o['title'];

        $artists[] = $a;
      }
    }

    $al->artists = $artists;
    return $al;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createArtist($id, $title);
		return $ret;
	}
}

?>
