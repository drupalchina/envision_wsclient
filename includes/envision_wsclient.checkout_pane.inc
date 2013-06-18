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
  $error_list = array();
  foreach ($order->commerce_line_items['und'] as $item_id){
    $tmpArr = call_envision_webservice($item_id);
//     dpm($tmpArr);
    if($tmpArr['status']=='OK'){
      array_push($result_list,$tmpArr);
    }else{
      array_push($error_list,$tmpArr);
    }
    
  }
  
  $pane_form = array(
    '#prefix' => '<div id="content-from-webservice">',
    '#suffix' => '</div>',
  );

  //get successful items list
  $table_data='';
  $err_table_data='';
  foreach($result_list as $result){
    $table_data.='<tr>'
                    .'<td>'.$result['data']['vappName'].'</td>'
                    .'<td>'.$result['data']['hireDays'].'</td>'
                    .'<td>'.$result['data']['vms'][0]['name'].'</td>'
                    .'<td>'.$result['data']['vms'][0]['cpu'].'</td>'
                    .'<td>'.$result['data']['vms'][0]['os'].'</td>'
                    .'<td>'.$result['data']['vms'][0]['powerStatus'].'</td>'
                    .'<td>'.$result['message'].'</td>'
                 .'<tr>';
  }
  
  //show successful items list to $pane_form['OK']
    $pane_form['OK'] = array(
      '#type' => 'item',
      '#title' => t('Create Successfully List'),
      '#markup' => '
      <table class="views-table">
        <thead>
          <tr>
            <th>Vapp Name</th>
            <th>Hire Days</th>
            <th>name</th>
            <th>cpu</th>
            <th>os</th>
            <th>power status</th>
            <th>remote call status</th>
          </tr>
        </thead>
        <tbody>'.$table_data.'</tbody>
      </table>
      ',
    );
    
    //get error items list 
    foreach($error_list as $error){
      $err_table_data.='<tr>'
      .'<td>'.$error['code'].'</td>'
      .'<td>'.$error['message'].'</td>'
      .'<tr>';
    }
    //show error items list to $pane_form['FAULT']
    $pane_form['FAULT'] = array(
      '#type' => 'item',
      '#title' => ''.($err_table_data==''?$err_table_data:'Create Fault list').'',
      '#markup' => 
      '<table class="views-table">
        <thead>
          <tr>
            <th>'.($err_table_data==''?$err_table_data:'Error Code').'</th>
            <th>'.($err_table_data==''?$err_table_data:'Message').'</th>
          </tr>
        </thead>
        <tbody>'.$err_table_data.'</tbody>
      </table>
      ',
    );
    
    
    // save node to drupal and 
    $save_node_status='';
    foreach($result_list as $result){
      $save_node_status.=save_result_as_node($result).'<br>';
    }
    
    //show save node result in $pane_form['SAVE']
//     $pane_form['save'] = array(
//       '#type' => 'item',
//       '#title' => ''.($err_table_data==''?$err_table_data:'Create Fault list').'',
//       '#markup' =>
//       '<table class="views-table">
//         <thead>
//           <tr>
//             <th>'.($err_table_data==''?$err_table_data:'Error Code').'</th>
//           </tr>
//         </thead>
//         <tbody>'.$err_table_data.'</tbody>
//       </table>
//       ',
//     );
    
    
 
  return $pane_form;
  
}

function call_envision_webservice($item_id){
  
  $item=commerce_line_item_load($item_id['line_item_id']);
  $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);
  
//   dpm($product);
//   $serviceName = taxonomy_term_load($product->field_service_name['und'][0]['tid'])->name.'-'.$product->product_id;
  $serviceName = 'test1';//test data
  $hireDays = $item->quantity;
  $vmSize = '';
//   $templateName = $product->title;
  $templateName = 'new-uploaded';//test data
  $maxWindQuantity = taxonomy_term_load($product->field_max_wind_machine_quantity['und'][0]['tid'])->name;
  $maxVisitors = taxonomy_term_load($product->field_max_visitors['und'][0]['tid'])->name;
  
//test data start test
//   $serviceName='test1';
//   $hireDays ='';
//   $vmSize = '';
//   $maxWindQuantity='';
//   $maxVisitors='';
//   $templateName='new-uploaded';
//end test data
  
  dpm('serviceName='.$serviceName.chr(13)
  .'hireDays='.$hireDays.chr(13)
  .'templateName='.$templateName.chr(13)
  .'maxWindQuantity='.$maxWindQuantity.chr(13)
  .'maxVisitors='.$maxVisitors.chr(13)
  );
  
  $service = wsclient_service_load('envision_webservice');
  try {
    $result = $service->create($serviceName,$hireDays,$vmSize,$maxWindQuantity,$maxVisitors,$templateName);
  }catch (WSClientException $e) {
    drupal_set_message($e->__toString(),'error');
    $result = $e->__toString();
  }
  return $result;
}

function save_result_as_node($result){
//   dpm($result);
  global $user;
  try {
  $node = (object) NULL;;
  $node->title = $result['data']['vappName'];
  $node->type = 'running_service';
  $node->uid = $user->uid;
  $node->status = 1; //(1 or 0): published or not
  $node->promote = 0; //(1 or 0): promoted to front page
  $node->comment = 0; // 0 = comments disabled, 1 = read only, 2 = read/write
  $node->field_template_name['und'][0]['value'] = $result['data']['vms'][0]['name'];
  $node->field_cpu['und'][0]['value'] =$result['data']['vms'][0]['cpu'];
  $node->field_power_status['und'][0]['value'] =$result['data']['vms'][0]['powerStatus'];
  $node->field_network['und'][0]['value'] =$result['data']['vms'][0]['network'].'';
  $node = node_submit($node); // Prepare node for saving
  node_save($node);
  dpm($result);
  }catch (Exception $e) {
    drupal_set_message($e->__toString(),'error');
  }
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
