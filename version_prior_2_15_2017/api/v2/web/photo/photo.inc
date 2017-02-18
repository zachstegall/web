<?php

include_once "../db.inc";

class PhotoList
{
	public $photos = array();
}

class Photo
{
	public $title = "";

	function Photo ()
	{
		$this->title = "";
	}

	function getForPage( $page )
	{
		$db = new DB();
		$dbu = $db->getPhotosOnPage( $page );
		$photos = array();
		$pl = new PhotoList();
		foreach ( $dbu as $o )
		{
			$photos[] = $o['title'];
		}

		$pl->photos = $photos;
		return $pl;
	}

	function getPageCount ()
	{
		$db = new DB();
		$max = $db->getPhotosPageCount();
		return $max;
	}
}

?>
