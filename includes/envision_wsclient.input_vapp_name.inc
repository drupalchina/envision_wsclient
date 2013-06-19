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
  

  
  foreach ($order->commerce_line_items['und'] as $item_id){
    $item=commerce_line_item_load($item_id['line_item_id']);
    $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);

    $pane_form[$item_id['line_item_id'].''] = array(
      '#type' => 'fieldset',
      '#title' => t($product->title.''),
      '#collapsible' => TRUE,
      '#group' => 'vertical_tabs',
    );
    $pane_form[$item_id['line_item_id'].'']['vapp-name'] = array(
      '#type' => 'textfield',
      '#title' => t('Please enter the vapp name.'),
      '#default_value' => 'test1',
      '#size' => 60,
      '#required' => TRUE,
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
  

  $check_repeate=array();
  foreach($form_state['values']['input_vapp_name_pane'] as $item){
    if(in_array($item['vapp-name'],$check_repeate)){
      form_set_error('input_vapp_name_pane][vapp-name','Repeated name.');
      return FALSE;
    }else{
      array_push($check_repeate,$item['vapp-name']);
    }
    $row = db_query('SELECT nid FROM node WHERE title = :mytitle and type =:type', 
      array(':mytitle' => $item['vapp-name'],':type'=>'running_service'))->fetchField();
    if(!$row==''){
      form_set_error('input_vapp_name_pane][vapp-name','This name already exist');
      return FALSE;
    }

  }
  return TRUE;
}

/**
 * Checkout pane callback: submit the shipping checkout pane.
 */
function envision_wsclient_input_vapp_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  
//   $order->data=null;
  foreach($order->commerce_line_items['und'] as &$item){
    $key = $item['line_item_id'].'';
    $value = $form_state['values']['input_vapp_name_pane'][$key]['vapp-name'];
    $order->data[$key]=$value;
    //$form_state['values']['input_vapp_name_pane'][$item['line_item_id'].'']);
  }
//   dpm($order);
}

/**
 * Checkout pane callback: show the selected shipping service on the review pane.
 */
function envision_wsclient_input_vapp_pane_review($form, $form_state, $checkout_pane, $order) {
  
}
