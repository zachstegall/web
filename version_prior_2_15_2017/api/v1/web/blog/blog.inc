<?php

include_once "../db.inc";

class BlogPosts
{
	public $posts = array();
}

class Blog 
{
	public $id = "";
	public $title = "";
	public $ts = "";
	public $user_id = "";
	public $body = "";

	function Blog ()
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
		$o = $db->getBlog( $id );
		$b = NULL;
		if( $o )
		{
			$b = new Blog();
			$b->id = $o['id'];
			$b->title = $o['title'];
			$b->ts = $o['ts'];
			$b->user_id = $o['user_id'];
			$b->body = $o['body'];
		}

		return $b;
	}

	function getListWithCount($cnt)
	{
		$db = new DB();
		$dbo = $db->getBlogPostsWithCount($cnt);
		$bp = new BlogPosts();
		$posts = array();
		foreach ( $dbo as $o )
		{
			$b = new Blog();
			$b->id = $o['id'];
			$b->title = $o['title'];
			$b->ts = $o['ts'];
			$b->user_id = $o['user_id'];
			$b->body = $o['body'];
			
			$posts[] = $b;
		}

		$bp->posts = $posts;
		return $bp;
	}
}

?>
