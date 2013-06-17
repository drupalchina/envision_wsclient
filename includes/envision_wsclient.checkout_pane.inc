<?php

/**
 * @file
 * Callback functions for the shipping module's checkout panes.
 */


/**
 * Checkout pane callback: returns the shipping service pane's settings form.
 */
function envision_wsclient_pane_settings_form($checkout_pane) {
//   dpm($checkout_pane);
}

/**
 * Checkout pane callback: builds a shipping quote selection form.
 */
function envision_wsclient_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  
//   $tmpArr = array(
//     'status'=>'OK',
//     'code'=>'NONE',
//     'data'=>array(
//       'customerName'=>null,
//       'vappName'=>'test1',
//       'hireDays'=>'',
//       'serviceName'=>null,
//       'vms'=>array(
//         array(
//           'name'=>'new-uploaded',
//           'cpu'=>'hertz * 10^6 X 1',
//           'os'=>'Microsoft XXX',
//           'powerStatus'=>'POWERED_OFF',
//           'network'=>array(),
//         ),
//       ),
//     ),
//     'message'=>'create vApp \'test1\' successfully',
//   );
  
  
  $result_list = array();
  foreach ($order->commerce_line_items['und'] as $item_id){
    $tmpRs = call_envision_webservice($item_id);
    dpm($tmpRs);
    array_push($result_list,$tmpRs);
  }
  

  
  
//   dpm($order);
  
//   dpm($result===NULL?'null':$result);
  
  $pane_form = array(
    '#prefix' => '<div id="content-from-webservice">',
    '#suffix' => '</div>',
  );
  
  foreach($result_list as $result){
    $pane_form[] = array(
      '#type' => 'item',
      '#title' => t($result['message']),
      '#markup' => '
      <table>
        <tr>
          <td>Vapp Name</td>
          <td>Hire Days</td>
          <td>name</td>
          <td>cpu</td>
          <td>os</td>
          <td>power status</td>
        </tr>
        <tr>
          <td>'.$result['data']['vappName'].'</td>
          <td>'.$result['data']['hireDays'].'</td>
          <td>'.$result['data']['vms'][0]['name'].'</td>
          <td>'.$result['data']['vms'][0]['cpu'].'</td>
          <td>'.$result['data']['vms'][0]['os'].'</td>
          <td>'.$result['data']['vms'][0]['powerStatus'].'</td>
        </tr>
      </table>
      ',
    );
  }
  
  
  
  return $pane_form;
  
}

function call_envision_webservice($item_id){
  
  $item=commerce_line_item_load($item_id['line_item_id']);
  $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);
  
  /* start test
  $serviceName = taxonomy_term_load($product->field_service_name['und'][0]['tid'])->name;
  $hireDays = $item->quantity;
  $vmSize = '';
  $templateName = $product->title;
  $maxWindQuantity = taxonomy_term_load($product->field_max_wind_machine_quantity['und'][0]['tid'])->name;
  $maxVisitors = taxonomy_term_load($product->field_max_visitors['und'][0]['tid'])->name;
  */
  //test data
  $serviceName='test1';
  $hireDays ='';
  $vmSize = '';
  $maxWindQuantity='';
  $maxVisitors='';
  $templateName='new-uploaded';
  
//   dpm('serviceName='.$serviceName.chr(13)
//   .'hireDays='.$hireDays.chr(13)
//   .'templateName='.$templateName.chr(13)
//   .'maxWindQuantity='.$maxWindQuantity.chr(13)
//   .'maxVisitors='.$maxVisitors.chr(13)
//   );
  
  $service = wsclient_service_load('envision_webservice');
  try {
    $result = $service->create($serviceName,$hireDays,$vmSize,$maxWindQuantity,$maxVisitors,$templateName);
  }catch (WSClientException $e) {
    drupal_set_message($e->__toString(),'error');
    $result = $e->__toString();
  }
  return $result;
}

/**
 * Ajax callback: Returns the shipping details form elements that match the
 * currently selected shipping service.
 */
function envision_wsclient_pane_service_details_refresh($form, $form_state) {
  
}

/**
 * Ajax callback: Returns recalculated shipping services.
 */
function commerce_shipping_recalculate_services_refresh($form, $form_state) {
  
}

/**
 * Validate callback for recalculating shipping services.
 */
function commerce_shipping_recalculate_services_validate($form, &$form_state) {
  // Call all validation callbacks.


  return TRUE;
}

/**
 * Submit callback for recalculating shipping services.
 */
function commerce_shipping_recalculate_services_submit($form, &$form_state) {

}

/**
 * Checkout pane callback: validate the shipping service selection and details.
 */
function envision_wsclient_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {

  return TRUE;
}

/**
 * Checkout pane callback: submit the shipping checkout pane.
 */
function envision_wsclient_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {

}

/**
 * Checkout pane callback: show the selected shipping service on the review pane.
 */
function envision_wsclient_pane_review($form, $form_state, $checkout_pane, $order) {
  
}
