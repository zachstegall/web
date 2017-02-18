<?php

include "album.inc";

$result = new Result();

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$res = Album::getList();
	$failMsg = "Get album list failed.";
}

if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
