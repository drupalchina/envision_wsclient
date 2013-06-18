<?php



function exec_wsclient(){
  $service = wsclient_service_load('envision_webservice');
  
  try {
    $result = $service->delete('test1');
  }catch (WSClientException $e) {
     print($e->__toString());
  }
  print_r('result:'.$result);
  return;
}