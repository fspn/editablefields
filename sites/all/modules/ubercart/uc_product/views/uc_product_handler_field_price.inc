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
return '<div class="editablefield-item">'.uc_currency_format($this->get_value($values)).'</div>';




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
