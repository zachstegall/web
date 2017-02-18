<?php

include_once "../result.inc";
include_once "photo.inc";

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$result = new Result();
	
	if( isset( $_REQUEST['page'] ) )
		$res = Photo::getForPage( $_REQUEST['page'] );
	else
		$res = Photo::get();

	$failMsg = "Photo load failed.";
}
else if ( $_SERVER['REQUEST_METHOD'] == 'PUT' )
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
