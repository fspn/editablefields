<?php

/**
 * @file
 * Plugin to provide functions needed for loading, saving, rendering
 * sell_price for editablefields.
 */

/**
 * Plugin definition.
 *
 * Available keys:
 * 'editablefields_form_builder'
 *  Loading form element that will be inserted in page when click [edit]
 *
 * 'editablefields_view'
 *  Rendering field for viewing.
 *
 * 'editablefields_submit'
 *  Saving value when it is recieved from ajax call.
 */
$plugin = array(
  'name' => 'editablefields_sell_price',
  'title' => t("Ubercard editablefields: sell_price"),
  'description' => t('Adds required callbacks for using sell_price in editablefields.'),
  // Loading form element.
  'editablefields_form_builder' => 'uc_editablefields_sell_price_editablefields_form_builder',
  // Rendering for viewing.
  'editablefields_view' => 'uc_editablefields_sell_price_editablefields_view',
  // Saving value.
  'editablefields_submit' => 'uc_editablefields_sell_price_editablefields_submit',
);

/**
 * Load form element from node form.
 *
 * @param object $node
 *   Node object.
 * @return array
 */
function uc_editablefields_sell_price_editablefields_form_builder($form_state, $node) {

  // Retrieve node form.
  $form_id = $node->type . '_node_form';

  module_load_include('inc', 'node', 'node.pages');
  $form = call_user_func_array('drupal_retrieve_form', array($form_id, $form_state, $node));
  $form_build_id = 'form-'. md5(uniqid(mt_rand(), TRUE));
  $form['#build_id'] = $form_build_id;
  drupal_prepare_form($form_id, $form, $form_state);

  // Load piece of the node form.
  $form_element = $form['base']['prices']['sell_price'];
  $form = array('sell_price' => $form_element);
  unset($form['sell_price']['#description']);
  unset($form['sell_price']['#title']);
  $form['sell_price']['#size'] = 10;

  return $form;
}

/**
 * Render field for viewing.
 *
 * @param int $nid
 * @return string
 */
function uc_editablefields_sell_price_editablefields_view($nid) {
  $node = node_load($nid);

  $context = array(
    'revision' => 'themed',
    'type' => 'product',
    'class' => array(
      'product',
    ),
    'field' => 'sell_price',
    'subject' => array(
      'node' => $node,
    ),
  );
  $options = array('label' => FALSE);

  return uc_price($node->sell_price, $context, $options);
}

/**
 * Saving value.
 */

/**
 * Saving value.
 *
 * @param int $nid
 *   nid of the node.
 * @param string $value
 *   Value of the field. $_POST['sell_price'].
 */
function uc_editablefields_sell_price_editablefields_submit($nid, $value) {
  $node = node_load($nid);
  // Save only if user can update the node.
  if (node_access('update', $node)) {
    $node->sell_price = $value;

    node_save($node);
  }
}
