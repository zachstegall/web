<?php

include_once "../result.inc";
include_once "note.inc";

if( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$result = new Result();

	if( isset($_REQUEST['cnt']) )
		$res = Note::getListWithCount($_REQUEST['cnt']);
	else
		$res = Note::getList();

	$failMsg = "Get note posts failed.";
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
