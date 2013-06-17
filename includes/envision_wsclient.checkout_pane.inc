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
  // Ensure this include file is loaded when the form is rebuilt from the cache.
//   dpm($order);
//   $result = call_envision_webservice($order);
  
//   dpm($order);
  foreach ($order->commerce_line_items['und'] as $item_id){
    dpm(call_envision_webservice($item_id));
  }
  
  
//   dpm($order);
  
//   dpm($result===NULL?'null':$result);
  
  $pane_form = array(
    '#prefix' => '<div id="content-from-webservice">',
    '#suffix' => '</div>',
  );
  
  
  $pane_form['result'] = array(
    '#type' => 'textfield',
    '#title' => t('Call Result'),
    '#default_value' => 'hello',
  );
  
  return $pane_form;
  
}

function call_envision_webservice($item_id){
  
  $item=commerce_line_item_load($item_id['line_item_id']);
  $product = commerce_product_load($item->commerce_product['und'][0]['product_id']);
  
  $serviceName = taxonomy_term_load($product->field_service_name['und'][0]['tid'])->name;
  $hireDays = $item->quantity;
  $vmSize = '';
  $templateName = $product->title;
  $maxWindQuantity = taxonomy_term_load($product->field_max_wind_machine_quantity['und'][0]['tid'])->name;
  $maxVisitors = taxonomy_term_load($product->field_max_visitors['und'][0]['tid'])->name;
  
//   dpm('serviceName='.$serviceName.chr(13)
//   .'hireDays='.$hireDays.chr(13)
//   .'templateName='.$templateName.chr(13)
//   .'maxWindQuantity='.$maxWindQuantity.chr(13)
//   .'maxVisitors='.$maxVisitors.chr(13)
//   );
  
  $service = wsclient_service_load('envision_creagevapp');
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
