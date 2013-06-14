<?php



function exec_wsclient(){
  $service = wsclient_service_load('envision_creagevapp');
  
//   $curl_options[CURLOPT_HTTPAUTH] = CURLAUTH_BASIC;
//   $curl_options[CURLOPT_USERPWD] = "corp\\XINHUANG:Password003#";
//   $curl_options[CURLOPT_PROXY] = "cnproxy.cn.alcatel-lucent.com";
//   $curl_options[CURLOPT_PROXYPORT] = 80;
//   $curl_options[CURLOPT_PROXYUSERPWD] = "ad4\kzhan004:!QAZ2wsx";
//   $service->settings['curl options'] = $curl_options;

  
  try {
    $result = $service->create('test1','123','123','123','123','new-uploaded');
  }catch (WSClientException $e) {
     print($e->__toString());
  }
  print('result<br>');
  print_r($result);
  return;
}