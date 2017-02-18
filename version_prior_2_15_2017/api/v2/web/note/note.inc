<?php

include_once "../db.inc";

class NotePosts
{
	public $posts = array();
}

class Note 
{
	public $id = "";
	public $title = "";
	public $ts = "";
	public $user_id = "";
	public $body = "";

	function Note ()
	{
		$this->id = "";
		$this->title = "";
		$this->ts = "";
		$this->user_id = "";
		$this->body = "";
	}

	function get( $id )
	{
		$db = new DB();
		$o = $db->getNote( $id );
		$n = NULL;
		if( $o )
		{
			$n = new Note();
			$n->id = $o['id'];
			$n->title = $o['title'];
			$n->ts = $o['ts'];
			$n->user_id = $o['user_id'];
			$n->body = $o['body'];
		}

		return $n;
	}

	function getListWithCount($cnt)
	{
		$db = new DB();
		$dbo = $db->getNotePostsWithCount($cnt);
		$np = new NotePosts();
		$posts = array();
		foreach ( $dbo as $o )
		{
			$n = new Note();
			$n->id = $o['id'];
			$n->title = $o['title'];
			$n->ts = $o['ts'];
			$n->user_id = $o['user_id'];
			$n->body = $o['body'];
			
			$posts[] = $n;
		}

		$np->posts = $posts;
		return $np;
	}

	function create($id, $title, $body, $user_id, $ts)
  {
    $db = new DB();
    $ret = $db->createNote($id, $title, $body, $user_id, $ts);

    return $ret;
  }
}

?>
