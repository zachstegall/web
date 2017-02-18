<?php

class EmptyResult
{

}

class Result
{
  public $status = 200;
  public $payload = "";
  public $error = "";

  function printSuccess($o)
  {
    $this->payload = $o;
    $this->printOut();
  }

  function printError($s, $o, $e)
  {
    $this->status = $s;
    $this->payload = $o;
    $this->error = $e;
    $this->printOut();
  }

  function printOut()
  {
    if ( !$this->payload )
    {
      $this->payload = new EmptyResult();
    }

    echo json_encode($this);
  }
}

?>
