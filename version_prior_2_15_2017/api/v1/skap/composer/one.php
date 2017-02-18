<?php

include "song.inc";

$result = new Result();
$res = Composer::create($_REQUEST['id'], $_REQUEST['title']);
if ($res)
	$result->printSuccess($res);
else
	$result->printError(400, NULL, "Create composer failed.");

?>
