<?php

include "album.inc";

$result = new Result();

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	if ( isset($_REQUEST['id']) )
	{
		$res = Album::getAlbum($_REQUEST['id']);
		$failMsg = "Get album failed.";
	}
	else
	{
		$res = Album::getList();
		$failMsg = "Get album list failed.";
	}
}
else
{
	$res = Album::create($_REQUEST['id'], $_REQUEST['title']);
	$failMsg = "Create album failed.";
}

if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
