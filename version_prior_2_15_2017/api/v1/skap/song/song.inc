<?php

include_once "../result.inc";
include_once "../db.inc";

class SongList
{
  public $songs = array();
}

class Song
{
  public $id = "";
  public $user_id = "";
  public $title = "";
  public $bpm = "";
  public $play_cnt = "";
  public $last_played_ts = "";
  public $album_id = "";
  public $artist_id = "";
  public $album_artist_id = "";
  public $genre_id = "";
  public $composer_id = "";
  public $playlist_id = "";
  public $playback_dur = "";
  public $album_track_num = "";
  public $album_track_cnt = "";
  public $disc_num = "";
  public $disc_cnt = "";
  public $release_ts = "";
  public $skip_cnt = "";
  public $rating = "";
  public $lyrics = "";

  function Song()
  {
    $this->id = "";
    $this->user_id = "";
    $this->title = "";
    $this->bpm = "";
    $this->play_cnt = "";
    $this->last_played_ts = "";
    $this->album_id = "";
    $this->artist_id = "";
    $this->album_artist_id = "";
    $this->genre_id = "";
    $this->composer_id = "";
    $this->playlist_id = "";
    $this->playback_dur = "";
    $this->album_track_num = "";
    $this->album_track_cnt = "";
    $this->disc_num = "";
    $this->disc_cnt = "";
    $this->release_ts = "";
    $this->skip_cnt = "";
    $this->rating = "";
    $this->lyrics = "";
  }
  
	function getSong()
  {
    $db = new DB();
    $o = $db->getSong();
    if ( $o )
    {
			$s = new Song();	
      $s->id = $o['id'];
      $s->user_id = $o['user_id'];
      $s->title = $o['title'];
      $s->bpm = $o['bpm'];
      $s->play_cnt = $o['play_cnt'];
      $s->last_played_ts = $o['last_played_ts'];
      $s->album_id = $o['album_id'];
      $s->artist_id = $o['artist_id'];
      $s->album_artist_id = $o['album_artist_id'];
      $s->genre_id = $o['genre_id'];
      $s->composer_id = $o['composer_id'];
			$s->playlist_id = $o['playlist_id'];
      $s->playback_dur = $o['playback_dur'];
      $s->album_track_num = $o['album_track_num'];
      $s->album_track_cnt = $o['album_track_cnt'];
      $s->disc_num = $o['disc_num'];
      $s->disc_cnt = $o['disc_cnt'];
      $s->release_ts = $o['release_ts'];
      $s->skip_cnt = $o['skip_cnt'];
      $s->rating = $o['rating'];
      $s->lyrics = $o['lyrics'];
    }

    return $s;
	}

  function getList()
  {
    $sl = new SongList();
    $songs = array();
    $db = new DB();
    $dbu = $db->getSongs();
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $s = new Song();
        $s->id = $o['id'];
        $s->user_id = $o['user_id'];
        $s->title = $o['title'];
        $s->bpm = $o['bpm'];
        $s->play_cnt = $o['play_cnt'];
        $s->last_played_ts = $o['last_played_ts'];
        $s->album_id = $o['album_id'];
        $s->artist_id = $o['artist_id'];
        $s->album_artist_id = $o['album_artist_id'];
        $s->genre_id = $o['genre_id'];
        $s->composer_id = $o['composer_id'];
				$s->playlist_id = $o['playlist_id'];
        $s->playback_dur = $o['playback_dur'];
        $s->album_track_num = $o['album_track_num'];
        $s->album_track_cnt = $o['album_track_cnt'];
        $s->disc_num = $o['disc_num'];
        $s->disc_cnt = $o['disc_cnt'];
        $s->release_ts = $o['release_ts'];
        $s->skip_cnt = $o['skip_cnt'];
        $s->rating = $o['rating'];
        $s->lyrics = $o['lyrics'];

        $songs[] = $s;
      }
    }

    $sl->songs = $songs;
    return $sl;
  }

	function getListWithCount($cnt)
	{
    $sl = new SongList();
    $songs = array();
    $db = new DB();
    $dbu = $db->getSongsWithCount($cnt);
    if ( $dbu )
    {
      foreach ($dbu as $o)
      {
        $s = new Song();
        $s->id = $o['id'];
        $s->user_id = $o['user_id'];
        $s->title = $o['title'];
        $s->bpm = $o['bpm'];
        $s->play_cnt = $o['play_cnt'];
        $s->last_played_ts = $o['last_played_ts'];
        $s->album_id = $o['album_id'];
        $s->artist_id = $o['artist_id'];
        $s->album_artist_id = $o['album_artist_id'];
        $s->genre_id = $o['genre_id'];
        $s->composer_id = $o['composer_id'];
				$s->playlist_id = $o['playlist_id'];
        $s->playback_dur = $o['playback_dur'];
        $s->album_track_num = $o['album_track_num'];
        $s->album_track_cnt = $o['album_track_cnt'];
        $s->disc_num = $o['disc_num'];
        $s->disc_cnt = $o['disc_cnt'];
        $s->release_ts = $o['release_ts'];
        $s->skip_cnt = $o['skip_cnt'];
        $s->rating = $o['rating'];
        $s->lyrics = $o['lyrics'];

        $songs[] = $s;
      }
    }

    $sl->songs = $songs;
    return $sl;
	}

	function create($id, $user_id, $title, $bpm, $play_cnt, $last_played_ts,
    $album_id, $artist_id, $album_artist_id, $genre_id, $composer_id,
    $playlist_id, $playback_dur, $album_track_num, $album_track_cnt,
    $disc_num, $disc_cnt, $release_ts, $skip_cnt, $rating, $lyrics)
	{
		$db = new DB();
		$ret = $db->createSong($id, $user_id, $title, $bpm, $play_cnt, $last_played_ts,
    				$album_id, $artist_id, $album_artist_id, $genre_id, $composer_id,
    				$playlist_id, $playback_dur, $album_track_num, $album_track_cnt,
    				$disc_num, $disc_cnt, $release_ts, $skip_cnt, $rating, $lyrics);
		
		return $ret;
	}

	function createMany($songs)
	{
		$db = new DB();
		$ret = $db->createSongs($songs);
		return $ret;
	}

	function update($id, $user_id, $play_cnt, $last_played_ts, $skip_cnt, 
									$rating, $lyrics)
	{
		$db = new DB();
		$ret = $db->updateSong($id, $user_id, $play_cnt, $last_played_ts, $skip_cnt,
						$rating, $lyrics);

		return $ret;
	}
}

?>
