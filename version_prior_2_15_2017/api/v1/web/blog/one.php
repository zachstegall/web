<?php

include_once "../result.inc";
include_once "blog.inc";

$result = new Result();

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$res = Blog::get( $_REQUEST['id'] );
	$failMsg = "Get blog failed.";
}
else if ( $_SERVER['REQUEST_METHOD'] == 'PUT' )
{
	$failMsg = "Update blog failed.";
}
else
{
	$failMsg = "Create blog failed.";
}

if ( $result )
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
