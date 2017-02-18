<?php

include_once "../result.inc";
include_once "photo.inc";

if( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$result = new Result();
	$res = Photo::getPageCount();
	$failMsg = "Get page count failed.";
}
else if( $_SERVER['REQUEST_METHOD'] == 'PUT' )
{

}
else
{

}

if( $res )
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
