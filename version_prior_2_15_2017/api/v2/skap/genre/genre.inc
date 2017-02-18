<?php

include_once "../result.inc";
include_once "../db.inc";

class GenreList
{
  public $genres = array();
}

class Genre
{
  public $id = "";
  public $title = "";

  function Genre()
  {
    $this->id = "";
    $this->title = "";
  }

  function getList()
  {
    $gl = new GenreList();
    $genres = array();
    $db = new DB();
    $dbu = $db->getGenres();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $g = new Genre();
        $g->id = $o['id'];
        $g->title = $o['title'];

        $genres[] = $g;
      }
    }

    $gl->genres = $genres;
    return $gl;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createGenre($id, $title);
		return $ret;
	}
}

?>
