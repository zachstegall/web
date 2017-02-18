<?php

include "song.inc";
include "../playlist/playlist.inc";
include "../genre/genre.inc";
include "../composer/composer.inc";
include "../artist/artist.inc";
include "../albumartist/albumartist.inc";
include "../album/album.inc";

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$result = new Result();
	
	if( isset($_REQUEST['cnt']) )
	{
		$res = Song::getListWithCount( $_REQUEST['cnt'] );
		$failMsg = "Load songs with count failed.";
	}
	else
	{
		$res = Song::getList();
		$failMsg = "Load songs failed.";
	}
}
else if ( $_SERVER['REQUEST_METHOD'] == 'PUT' )
{
	$result = new Result();

	$body = file_get_contents('php://input', false , null, -1 , $_SERVER['CONTENT_LENGTH']);
	$decode = json_decode($body, true);
	$allInput = $decode['songs'];

	foreach ($allInput as $input)
	{
		$playcnt = isset($input['play_cnt']) ? $input['play_cnt'] : null;
		$lastts = isset($input['last_played_ts']) ? $input['last_played_ts'] : null;
		$skipcnt = isset($input['skip_cnt']) ? $input['skip_cnt'] : null;
		$rating = isset($input['rating']) ? $input['rating'] : null;

		$res = Song::update($input['id'], $input['user_id'], $playcnt, $lastts,
												$skipcnt, $rating);
	}

	$failMsg = "Update songs fail.";
}
else
{
	$result = new Result();

	$body = $HTTP_RAW_POST_DATA;
	$decode = json_decode($body, true);
	$allInput = $decode['songs'];

	foreach ($allInput as $input)
	{

		if (isset($input['playlist_id']) && isset($input['playlist_grp']))
		{
			Playlist::create($input['playlist_id'], $input['playlist_grp']);
		}
		if (isset($input['genre_id']) && isset($input['genre']))
		{
			Genre::create($input['genre_id'], $input['genre']);
		}
		if (isset($input['composer_id']) && isset($input['composer']))
		{
			Composer::create($input['composer_id'], $input['composer']);
		}
		if (isset($input['artist_id']) && isset($input['artist']))
		{
			Artist::create($input['artist_id'], $input['artist']);
		}
		if (isset($input['album_artist_id']) && isset($input['album_artist']))
		{
			AlbumArtist::create($input['album_artist_id'], $input['album_artist']);
		}
		if (isset($input['album_id']) && isset($input['album']))
		{
			Album::create($input['album_id'], $input['album']);
		}

		$bpm = isset($input['bpm']) ? $input['bpm'] : 0;
		$playcnt = isset($input['play_cnt']) ? $input['play_cnt'] : 0;
		$lastts = isset($input['last_played_ts']) ? $input['last_played_ts'] : 0;
		$albumid = isset($input['album_id']) ? $input['album_id'] : null;
		$artistid = isset($input['artist_id']) ? $input['artist_id'] : null;
		$albumartistid = isset($input['album_artist_id']) ? $input['album_artist_id'] : null;
		$genreid = isset($input['genre_id']) ? $input['genre_id'] : null;
		$composerid = isset($input['composer_id']) ? $input['composer_id'] : null;
		$playlistid = isset($input['playlist_id']) ? $input['playlist_id'] : null;
		$playback = isset($input['playback_dur']) ? $input['playback_dur'] : 0;
		$albumnum = isset($input['album_track_num']) ? $input['album_track_num'] : 0;
		$albumcnt = isset($input['album_track_cnt']) ? $input['album_track_cnt'] : 0;
		$releasets = isset($input['release_ts']) ? $input['release_ts'] : 0;
		$skipcnt = isset($input['skip_cnt']) ? $input['skip_cnt'] : 0;
		$rating = isset($input['rating']) ? $input['rating'] : 0;
	
		$res = Song::create($input['id'], $input['user_id'], $input['title'],
												$bpm, $playcnt, $lastts, $albumid, $artistid, $albumartistid, $genreid,
												$composerid, $playlistid, $playback, $albumnum, $albumcnt,
												$releasets, $skipcnt, $rating);
	}

	$failMsg = "Create songs failed.";
}


if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
