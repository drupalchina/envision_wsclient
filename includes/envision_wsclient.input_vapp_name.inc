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
function envision_wsclient_input_vapp_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {

  return TRUE;
}

/**
 * Checkout pane callback: submit the shipping checkout pane.
 */
function envision_wsclient_input_vapp_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {

}

/**
 * Checkout pane callback: show the selected shipping service on the review pane.
 */
function envision_wsclient_input_vapp_pane_review($form, $form_state, $checkout_pane, $order) {
  
}
