<?php

include_once "../result.inc";
include_once "blog.inc";

if( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$result = new Result();

	if( isset($_REQUEST['cnt']) )
		$res = Blog::getListWithCount($_REQUEST['cnt']);
	else
		$res = Blog::getList();

	$failMsg = "Get blog posts failed.";
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
