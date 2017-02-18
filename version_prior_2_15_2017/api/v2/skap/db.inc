<?php

class DB
{
  private static $sHost = NULL;
  private static $sName = NULL;
  private static $sUser = NULL;
  private static $sPswd = NULL;

  private static $sInit = false;

  private $dbconn = NULL;


  function DB()
  {
    if (!self::$sInit)
    {
      self::$sHost = "my-db-instance.cc0qeksfgjkv.us-west-2.rds.amazonaws.com";
      self::$sName = "my_database";
      self::$sUser = "db_user";
      self::$sPswd = "CoverZach123";

      self::$sInit = true;
    }

    $this->dbconn = pg_connect("host=".self::$sHost." dbname=".self::$sName." user=".self::$sUser." password=".self::$sPswd) or die('Could not connect: ' . pg_last_error());
  }

	function getSong()
	{
		$query = 'select * from song where last_played_ts = (select max(last_played_ts) from song)';
		$result = pg_query_params($this->dbconn, $query, array());
    if ( $result )
    {
      return pg_fetch_assoc($result);
    }
    else
    {
      return NULL;
    }
	}

  function getSongs()
  {
    $query = 'select id, title, artist_id, album_id from song;';
    $result = pg_query_params($this->dbconn, $query, array());
    if ( $result )
    {
      return pg_fetch_all($result);
    }
    else
    {
      return NULL;
    }
  }

	function getSongsWithCount($cnt)
	{
    $query = 'select id, title, artist_id, album_id from song order by last_played_ts desc limit $1;';
    $result = pg_query_params($this->dbconn, $query, array($cnt));
    if ( $result )
    {
      return pg_fetch_all($result);
    }
    else
    {
      return NULL;
    }
	}

	function createSongs($songs)
	{
		$res = 0;
		foreach ($songs as $s)
		{
			$ret = self::createSong($s['id'], $s['user_id'], $s['title'],
      $s['bmp'], $s['play_cnt'], $s['last_played_ts'], $s['album_id'],
      $s['artist_id'], $s['album_artist_id'], $s['genre_id'],
      $s['composer_id'], $s['playlist_id'], $s['playback_dur'],
      $s['album_track_num'], $s['album_track_cnt'],
      $s['release_ts'], $s['skip_cnt'], $s['rating']);
			if ( $ret )
				$res = $res + $ret;
		}

		return $res;
	}

	function createSong($id, $user_id, $title, $bpm, $play_cnt,
    $last_played_ts, $album_id, $artist_id, $album_artist_id,
    $genre_id, $composer_id, $playlist_id, $playback_dur,
    $album_track_num, $album_track_cnt,
    $release_ts, $skip_cnt, $rating)
	{
		$query = 'insert into song (id, user_id, title, bpm,
              play_cnt, last_played_ts, album_id, artist_id, album_artist_id,
              genre_id, composer_id, playlist_id, playback_dur, album_track_num,
              album_track_cnt, release_ts, skip_cnt, rating) values ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10,
              $11, $12, $13, $14, $15, $16, $17, $18);';
		$result = pg_query_params($this->dbconn, $query, array($id, $user_id, $title,
              $bpm, $play_cnt, $last_played_ts, $album_id, $artist_id, $album_artist_id,
              $genre_id, $composer_id, $playlist_id, $playback_dur, $album_track_num,
              $album_track_cnt, $release_ts, $skip_cnt, $rating));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

	function updateSong($id, $user_id, $play_cnt, $last_played_ts, $skip_cnt,
                  		$rating)
	{
		$query = 'update song set play_cnt = $3, last_played_ts = $4, skip_cnt = $5,
							rating = $6 where user_id = $2 and id = $1';
		$result = pg_query_params($this->dbconn, $query, array($id, $user_id, $play_cnt, 
							$last_played_ts, $skip_cnt, $rating));

		if ($result)
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createPlaylist($id, $title)
	{
		$query = 'insert into playlist (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createGenre($id, $title)
	{
		$query = 'insert into genre (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createComposer($id, $title)
	{
		$query = 'insert into composer (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createArtist($id, $title)
	{
		$query = 'insert into artist (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createAlbumArtist($id, $title)
	{
		$query = 'insert into albumartist (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}

  function createAlbum($id, $title)
	{
		$query = 'insert into album (id, title) values ($1, $2);';
		$result = pg_query_params($this->dbconn, $query, array($id, $title));
		if ( $result )
		{
			return pg_affected_rows($result);
		}
		else
		{
			return NULL;
		}
	}
	
	function getAlbum($id)
	{
		$query = 'select * from album where id = $1;';
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
	
	function getAlbums()
	{
		$query = 'select * from album;';
		$result = pg_query_params($this->dbconn, $query, array());
    if ( $result )
    {
      return pg_fetch_all($result);
    }
    else
    {
      return NULL;
    }
	}
	
	function getArtist($id)
	{
		$query = 'select * from artist where id = $1';
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
}

?>
