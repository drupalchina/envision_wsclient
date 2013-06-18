<?php



function exec_wsclient(){
  $service = wsclient_service_load('envision_creagevapp');
  
  try {
    $result = $service->delete('test3');
  }catch (WSClientException $e) {
     print($e->__toString());
  }
  print('result<br>');
  print_r($result);
  return;
}