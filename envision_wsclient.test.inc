<?php



function exec_wsclient(){
    $service = wsclient_service_load('envision_webservice');
  try {
    $result = $service->create('test-1','2','new-uploaded');
  }catch (WSClientException $e) {
    drupal_set_message($e->__toString(),'error');
    $result = $e->__toString();
  }
  dpm($result);
  print_r($result);
  return $result;
}