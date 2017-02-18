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
	$res = Song::getSong();
	$failMsg = "Load song failed.";
}
else if ( $_SERVER['REQUEST_METHOD'] == 'PUT' )
{
	$result = new Result();
	$body = file_get_contents('php://input', false , null, -1 , $_SERVER['CONTENT_LENGTH']);
	$input = json_decode($body, true);

	$res = Song::update($input['id'], $input['user_id'], $input['play_cnt'], $input['last_played_ts'],
											$input['skip_cnt'], $input['rating'], $input['lyrics']);

	$failMsg = "Update song failed.";
}
else
{
	$result = new Result();
	$body = $HTTP_RAW_POST_DATA;
	$input = json_decode($body, true);

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

	$res = Song::create($input['id'], $input['user_id'], $input['title'],
											$input['bpm'], $input['play_cnt'], $input['last_played_ts'],
											$input['album_id'], $input['artist_id'], $input['album_artist_id'],
											$input['genre_id'], $input['composer_id'], $input['playlist_id'],
											$input['playback_dur'], $input['album_track_num'],
											$input['album_track_cnt'], $input['disc_num'], $input['disc_cnt'],
											$input['release_ts'], $input['skip_cnt'], $input['rating'],
											$input['lyrics']);

	$failMsg = "Create song failed.";
}


if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
