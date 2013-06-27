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
  dpm($order);

  $result_list = $order->data['result_list'];
  $error_list = $order->data['error_list'];
  
  foreach ($result_list as $ok_item){
    save_result_as_node($ok_item);
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
    

  return $pane_form;
  
}

/**
 * save result to node
 */
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
//   $node->field_template_name['und'][0]['value'] = $result['data']['vms'][0]['name'];
//   $node->field_cpu['und'][0]['value'] =$result['data']['vms'][0]['cpu'];
//   $node->field_power_status['und'][0]['value'] =$result['data']['vms'][0]['powerStatus'];
//   $node->field_memory['und'][0]['value'] =$result['data']['vms'][0]['memory'];
//   $node->field_storage['und'][0]['value'] =$result['data']['vms'][0]['hardDisk'][0]['size'];
//   $node->field_storage['und'][0]['value'] ='40960 Mb';//test data,the storage data not prepared.
//   $node->field_ip_address['und'][0]['value'] =$result['data']['vms'][0]['network'][0]['ipAddress'];
  $node->field_task_id['und'][0]['value'] =$result['data']['taskId'];
  $node->field_vappid['und'][0]['value'] =$result['data']['vappId'];
  $node->field_progress['und'][0]['value'] =0;
  $node = node_submit($node); // Prepare node for saving
  node_save($node);
  //dpm($result);
  }catch (Exception $e) {
    drupal_set_message($e->__toString(),'error');
  }
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

