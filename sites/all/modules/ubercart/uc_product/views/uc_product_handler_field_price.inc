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
dpm($values);

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
    'callback' => 'editablefields_form_update',
    'wrapper' => $values->nid,
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
// $form['field']= drupal_build_form('product',form_state_defaults());
 $form['field'] = array(
  '#type' => 'item',
  '#markup' => uc_currency_format($this->get_value($values)),
  '#attributes' => array('class' => array('editablefield-item')),
);
//dpm($values->_field_data['nid']['entity_type']);
//dpm($cloned_entity);
    //$form['field'] =$element;
    /*= array(
      '#pre_render' => array('editablefields_lazy_render_fields'),
      '#arguments' => $shield,
    );*/
    // Click to edit mode: generate a AJAX-bound submit handler.
    $form['actions']['edit'] = array(
      '#name' => 'edit-' . $values->nid,
      '#type' => 'submit',
      '#value' => t('Edit this field'),
      '#submit' => array('editablefields_form_submit_edit_mode'),
      '#ajax' => $ajax,
//      '#limit_validation_errors' => array($form['#parents']),
      '#attributes' => array(
        'class' => array(
          'editablefield-edit',
//          'editablefield-edit-' . $edit_style,
        ),
      ),
    );


//dpm(drupal_render($form));
//render($form)
dpm($form);
return '<div class="editablefield-item">'.render($form).'</div>';




    }
    if ($this->options['format'] == 'uc_price') {
      $value = $this->get_value($values);

      if (is_null($value) || ($value == 0 && $this->options['empty_zero'])) {
        return '';
      }

      return uc_currency_format($value);
    }

  }
}
