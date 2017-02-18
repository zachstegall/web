<?php

include_once "../result.inc";
include_once "../db.inc";

class ComposerList
{
  public $composers = array();
}

class Composer
{
  public $id = "";
  public $title = "";

  function Composer()
  {
    $this->id = "";
    $this->title = "";
  }

  function getList()
  {
    $cl = new ComposerList();
    $composers = array();
    $db = new DB();
    $dbu = $db->getComposers();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $c = new Composer();
        $c->id = $o['id'];
        $c->title = $o['title'];

        $composers[] = $c;
      }
    }

    $cl->composers = $composers;
    return $cl;
  }

	function create($id, $title)
	{
		$db = new DB();
		$ret = $db->createComposer($id, $title);
		return $ret;
	}
}

?>
