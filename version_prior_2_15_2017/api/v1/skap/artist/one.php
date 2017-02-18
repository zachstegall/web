<?php

include "artist.inc";

$result = new Result();

if ( $_SERVER['REQUEST_METHOD'] == 'GET' )
{
  if ( isset($_REQUEST['id']) )
  {     
    $res = Artist::getArtist($_REQUEST['id']);
    $failMsg = "Get artist failed.";
  }     
  else  
  {     
    $res = Artist::getList();
    $failMsg = "Get artist list failed.";
  }     
}
else
{
	$res = Artist::create($_REQUEST['id'], $_REQUEST['title']);
}

if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, $failMsg);

?>
