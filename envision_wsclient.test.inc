<?php



function exec_wsclient(){
  $service = wsclient_service_load('envision_creagevapp');
  
  $curl_options[CURLOPT_HTTPAUTH] = CURLAUTH_BASIC;
  $curl_options[CURLOPT_USERPWD] = "corp\XINHUANG:Password003#";
  $service->settings['curl options'] = $curl_options;
  
  try {
    $result = $service->create('envision');
  }catch (WSClientException $e) {
     print($e->__toString());
  }
  print('retult<br>');
  print_r($result);
  return;
}