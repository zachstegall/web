<?php

class DB
{
	private static $sHost = NULL;
	private static $sName = NULL;
	private static $sUser = NULL;
	private static $sPswd = NULL;

	private static $sInit = false;

	private $dbconn = NULL;

	function DB ()
	{
		if( !self::$sInit )
		{
			self::$sHost = "my-db-instance.cc0qeksfgjkv.us-west-2.rds.amazonaws.com";
			self::$sName = "my_database";
			self::$sUser = "db_user";
			self::$sPswd = "CoverZach123";

			self::$sInit = true;
		}

		$this->dbconn = pg_connect("host=".self::$sHost." dbname=".self::$sName." user=".self::$sUser." password=".self::$sPswd) or die('Could not connect: ' . pg_last_error());
	}

	function getNote ( $id )
	{
		$query = 'select * from note where id = $1;';
		$result = pg_query_params($this->dbconn, $query, array($id));
		if ( $result )
		{
			return pg_fetch_assoc($result);
		}
		else
		{
			return NULL;
		}
	}

	function getNotePostsWithCount ( $cnt )
	{
		$query = 'select * from note order by ts desc limit $1;';
		$result = pg_query_params($this->dbconn, $query, array($id));
		if ( $result )
		{
			return pg_fetch_all($result);
		}
		else
		{
			return NULL;
		}
	}

	function getPhotosOnPage ( $page )
	{
		$query = 'select title from photo where page_id = $1 order by ts desc;';
		$result = pg_query_params($this->dbconn, $query, array($page));
		if( $result )
		{
			return pg_fetch_all($result);
		}
		else
		{
			return NULL;
		}
	}

	function getPhotosPageCount ()
	{
		$query = 'select max(page_id) from photo;';
		$result = pg_query_params($this->dbconn, $query, array());
		if( $result )
		{
			return pg_fetch_assoc($result);
		}
		else
		{
			return NULL;
		}
	}

	function createNote($id, $title, $body, $user_id, $ts)
  {
    $query = 'insert into note (id, title, body, user_id, ts) values ($1, $2, $3, $4, $5);';
    $result = pg_query_params($this->dbconn, $query, array($id, $title, $body, $user_id, $ts));
		if ( $result )
    {
      return pg_affected_rows($result);
    }
    else
    {
      return NULL;
    }
  }
}

?>
