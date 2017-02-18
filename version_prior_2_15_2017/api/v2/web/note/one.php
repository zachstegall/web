<?php

include_once "../result.inc";
include_once "note.inc";

$result = new Result();


if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
	$res = Note::get( $_REQUEST['id'] );
	$failMsg = "Get note failed.";
}
else if ( $_SERVER['REQUEST_METHOD'] == 'PUT' )
{
	$failMsg = "Update note failed.";
}
else
{
	$body = file_get_contents('php://input', false , null, -1 , $_SERVER['CONTENT_LENGTH'] );
	$input = json_decode($body, true);

  if ( isset( $input['id'] ) && isset( $input['title'] ) && isset( $input['body'] ) && isset( $input['user_id'] ) )
	{
		$res = Note::create($input['id'], $input['title'], $input['body'], $input['user_id'], (time()*1000));
	}

	$failMsg = "Create note failed.";
}

if ( $res )
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
