<?php

/**
 * @file
 * Callback functions for the shipping module's checkout panes.
 */


/**
 * Checkout pane callback: returns the shipping service pane's settings form.
 */
function envision_wsclient_input_vapp_pane_settings_form($checkout_pane) {
//   dpm($checkout_pane);
}

/**
 * Checkout pane callback: builds a shipping quote selection form.
 */
function envision_wsclient_input_vapp_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  
  $pane_form['tips'] = array(
        '#type' => 'item',
        '#title' => t('Tips'),
        '#markup' => 'The virtual application name is use for an <em>unique identifier</em>',
  );
  
  foreach ($order->commerce_line_items['und'] as $item_id){
    $item=commerce_line_item_load($item_id['line_item_id']);
    $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);

    $pane_form[$item_id['line_item_id'].''] = array(
      '#type' => 'fieldset',
      '#title' => t($product->title.''),
      '#collapsible' => TRUE,
      '#group' => 'vertical_tabs',
    );
    $pane_form[$item_id['line_item_id'].'']['vapp_name'] = array(
//       '#type' => 'item',
//       '#title' => t('Auto generated vritual application name .'),
//       '#markup' => ''.$product->title.'-'.microtime(TRUE).rand(1000,9999),
      
      '#type' => 'textfield',
      '#title' => t('Auto generated vritual application name .'),
      '#size' => 60,
      '#maxlength' => 128,
      '#default_value' => ''.$product->title.'-'.microtime(TRUE).rand(1000,9999),
      '#attributes' => array('disabled' => 'disabled'),
      '#disabled' => TRUE,
    );
  }
  
  

  return $pane_form;
}



/**
 * Ajax callback: Returns the shipping details form elements that match the
 * currently selected shipping service.
 */
function envision_wsclient_input_vapp_pane_service_details_refresh($form, $form_state) {
  
}

/**
 * Ajax callback: Returns recalculated shipping services.
 */
function commerce_shipping_recalculate_services_refresh($form, $form_state) {
  
}

/**
 * Checkout pane callback: validate the shipping service selection and details.
 */
function envision_wsclient_input_vapp_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  

//   $check_repeate=array();
//   foreach($form_state['values']['input_vapp_name_pane'] as $item){
//     if(in_array($item['vapp-name'],$check_repeate)){
//       form_set_error('input_vapp_name_pane][vapp-name','Repeated name.');
//       return FALSE;
//     }else{
//       array_push($check_repeate,$item['vapp-name']);
//     }
//     $row = db_query('SELECT nid FROM node WHERE title = :mytitle and type =:type', 
//       array(':mytitle' => $item['vapp-name'],':type'=>'running_service'))->fetchField();
//     if(!$row==''){
//       form_set_error('input_vapp_name_pane][vapp-name','This name already exist');
//       return FALSE;
//     }

//   }
  return TRUE;

}

/**
 * Checkout pane callback: submit the shipping checkout pane.
 */
function envision_wsclient_input_vapp_pane_checkout_form_submit($form, &$form_state, $vapp_name_pane, $order) {
  
//   $order->data=null;
//   foreach($order->commerce_line_items['und'] as &$item){
//     $key = $item['line_item_id'].'';
//     $value = $form_state['values']['input_vapp_name_pane'][$key]['vapp_name'];
//     $order->data[$key]=$value;
//     //$form_state['values']['input_vapp_name_pane'][$item['line_item_id'].'']);
//   }
//   dpm($order);

  $initial_time=microtime(TRUE);
  
  $result_list = array();
  $error_list = array();
  foreach ($order->commerce_line_items['und'] as $item){
    $key = $item['line_item_id'].'';
    $service_name = $form_state['values']['input_vapp_name_pane'][$key]['vapp_name'];
    $result = call_envision_webservice($item,$service_name);
    if($result['status']=='OK'){
      $result['data']['vappName']=$service_name;
      array_push($result_list,$result);
    }else{
      array_push($error_list,$result);
    }
  }
  
  $order->data['result_list']=$result_list;
  $order->data['error_list']=$error_list;
  
  $call_wsclient_time=microtime(TRUE)-$initial_time;
  drupal_set_message('Webservice call consume time:'.$call_wsclient_time);
}



/**
 * Call web service.
 */
function call_envision_webservice($item_id,$service_name){

  $item=commerce_line_item_load($item_id['line_item_id']);
  $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);

  $serviceName = $service_name;
  $hireDays = $item->quantity;
//   $templateName = $product->title;
  $templateName = 'BAO-S-1';
  
  dpm('$templateName:'.$templateName);
  
  $service = wsclient_service_load('envision_webservice');
  try {
    $result = $service->async_create($serviceName,$hireDays,$templateName);
  }catch (WSClientException $e) {
    drupal_set_message($e->__toString(),'error');
    $result = $e->__toString();
  }
  return $result;
}