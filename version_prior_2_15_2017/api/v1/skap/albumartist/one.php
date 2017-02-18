<?php

include "song.inc";

$result = new Result();
$res = AlbumArtist::create($_REQUEST['id'], $_REQUEST['title']);
if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, "Create albumartist failed.");

?>
