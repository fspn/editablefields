<?php

/**
 * @file
 * Views handler: Product price field.
 */

/**
 * Returns a formatted price value to display in the View.
 */
class uc_product_handler_field_price extends views_handler_field_numeric {

  /**
   * Overrides views_handler::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['format'] = array('default' => 'uc_price');

    return $options;
  }

  /**
   * Overrides views_handler::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options;

    $form['format'] =  array(
      '#title' => t('Format'),
      '#type' => 'radios',
      '#options' => array(
        'uc_price' => t('Ubercart price'),
        'numeric' => t('Numeric'),
        'clicktoedit' => t('Click to Edit'),
      ),
      '#default_value' => $options['format'],
      '#weight' => 1,
    );

    // Change weight and dependency of the previous field on the parent numeric ones
    $weight = 2;
    foreach (array('set_precision', 'precision', 'decimal', 'separator', 'prefix', 'suffix') as $field) {
      if (isset($form[$field]['#dependency'])) {
        $form[$field]['#dependency'] += array('radio:options[format]' => array('numeric'));
        $form[$field]['#dependency_count'] = count($form[$field]['#dependency']);
      }
      else {
        $form[$field]['#dependency'] = array('radio:options[format]' => array('numeric'));
      }

      $form[$field]['#weight'] = ++$weight;
    }
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
//  var_dump(editablefields_load_js());
    //var_dump(parent::render($values));
//   dpm(node_load($values->nid),$values->nid);
//dpm($values);

    if ($this->options['format'] == 'numeric') {
      return parent::render($values);
    }
 if ($this->options['format'] == 'clicktoedit') {
	/* editablefields_load_js();

    $class = "editablefields clicktoedit";
    $pre = '<div class="' . $class . '" nid="' . $values->nid . '" field="' . $this->field . '" delta="' . '0' . '">';
    $pre .= theme('editablefields_clicktoedit_message');
    $post = '</div>';

    $product = node_load($values->nid);
    $context = array(
      'revision' => 'themed',
      'type' => 'product',
      'class' => array(
        'product',
        $this->field,
      ),
      'field' => $this->real_field,
      'subject' => array(
        'node' => $product,
      ),
    );
    $options = array('label' => FALSE);
   return $pre . theme_uc_product_price($product->{$this->real_field}, $context, $options) . $post;*/

 $items = uc_currency_format($this->get_value($values));
//    $shield = new EditableFieldsShield();
//    $shield->arguments = array($values->_field_data['nid']['entity_type'], $values->_field_data['nid']['entity'], uc_currency_format($this->get_value($values)),$instance, 'und', $items, $display);
$ajax = array(
    'callback' => 'edit_fields_form_update_sell_price',
    'wrapper' => 'edit_field-item-'.$values->nid,
    'effect' => 'fade',
    'event' => 'click',
    'progress' => array(
      'type' => 'throbber',
      'message' => t('Please wait'),
    ),
  );
  //$form_id = $values->_field_data['nid']['entity_type'] . '_node_form';
//  module_load_include('inc', 'node', 'node.pages');
//  $form = call_user_func_array('drupal_retrieve_form', array($form_id, $form_state, $values->_field_data['nid']['entity']));
/*$element['#arguments']=$shield;
  $element['field'] = call_user_func_array('editablefields_fallback_formatter', $element['#arguments']->arguments);
  if (empty($element['field']) && !empty($element['#arguments']->arguments[6]['settings']['empty_text'])) {
    $element['field'] = array(
      '#markup' => $element['#arguments']->arguments[6]['settings']['empty_text'],
    );
  }*/
//$cloned_entity = clone $values->_field_data['nid']['entity'];

  //$form['field']= field_view_field($values->_field_data['nid']['entity_type'], $cloned_entity, 'sell_price');
 //$form['field']= drupal_build_form('product',form_state_defaults());
  //$form_state = form_state_defaults();
  //dpm($form_state);
  //$form1=array();
  //$form = drupal_retrieve_form('edit_form', $form_state);
 //$form=drupal_get_form('edit_form');
 //$form= drupal_prepare_form('edit_form',$form1,$form_state);
 //dpm($form);
/* $form_id='edit_form';
 $form['sell_price_form'] = array(
 '#type'=>'form',
    );
    $form['sell_price_form']['#build_id'] = 'form-' . drupal_hash_base64(uniqid(mt_rand(), TRUE) . mt_rand());
     $form['sell_price_form']['form_build_id'] = array(
    '#type' => 'hidden',
    '#value' => $form['sell_price_form']['#build_id'],
    '#id' => $form['sell_price_form']['#build_id'],
    '#name' => 'form_build_id',
    
    // Form processing and validation requires this value, so ensure the
    // submitted form value appears literally, regardless of custom #tree
    // and #parents being set elsewhere.
    '#parents' => array('form_build_id'),
  );
   $form['sell_price_form']['form_id'] = array(
      '#type' => 'hidden',
      '#value' => 'edit_form',
      '#id' => drupal_html_id("edit-edit_form"),
      
      // Form processing and validation requires this value, so ensure the
      // submitted form value appears literally, regardless of custom #tree
      // and #parents being set elsewhere.
      '#parents' => array('form_id'),
    );
     $form['sell_price_form']['#id'] = drupal_html_id($form_id);
   $form['sell_price_form']['#token'] = $form_id;
      $form['sell_price_form']['form_token'] = array(
        '#id' => drupal_html_id('edit-' . $form_id . '-form-token'),
        '#type' => 'token',
        '#default_value' => drupal_get_token($form['#token']),
        
        // Form processing and validation requires this value, so ensure the
        // submitted form value appears literally, regardless of custom #tree
        // and #parents being set elsewhere.
        '#parents' => array('form_token'),
      );
 $form['sell_price_form']['field'] = array(
  '#type' => 'textfield',
      '#value' => t(uc_currency_format($this->get_value($values),FALSE,true)),
  '#size' => 5,
  '#maxlength' => 8,

//  '#markup' => uc_currency_format($this->get_value($values)),
  '#attributes' => array('class' => array('edit_field-sell_price')),
  //'#ajax' => $ajax,
);*/
$form=drupal_get_form('form_edit_sell_price',$values->nid);
//dpm($values->_field_data['nid']['entity_type']);
//dpm($cloned_entity);
    //$form['field'] =$element;
    /*= array(
      '#pre_render' => array('editablefields_lazy_render_fields'),
      '#arguments' => $shield,
    );*/
    // Click to edit mode: generate a AJAX-bound submit handler.
/*    $form['sell_price_form']['actions']['save'] = array(
      '#name' => 'edit-' . $values->nid,
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('edit_fields_form_submit_sell_price'),
      '#id' => drupal_html_id($form_id).'-'.$values->nid,
      '#ajax' => $ajax,
//      '#limit_validation_errors' => array($form['#parents']),
      '#attributes' => array(
        'class' => array(
          'edit_field-sell_price_save',
//          'editablefield-edit-' . $edit_style,
        ),
      ),
    );*/


//dpm(drupal_render($form));
//render($form)
//dpm(($form));
return '<div id="edit_field-item-'.$values->nid.'">'.drupal_render($form).'</div>';




    }
    if ($this->options['format'] == 'uc_price') {
      $value = $this->get_value($values);

      if (is_null($value) || ($value == 0 && $this->options['empty_zero'])) {
        return '';
      }

      return uc_currency_format($value);
    }

  }
  function edit_fields_form_submit_sell_price($form, $form_state) 
  {
    dpm($form);
    dpm($form_state);
    return ;
  }
    function edit_fields_form_update_sell_price($form, $form_state) 
  {
    dpm($form);
    dpm($form_state);
    return ;
  }
  
}
