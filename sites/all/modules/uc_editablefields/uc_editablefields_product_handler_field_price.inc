<?php

/**
 * Return a formatted price value to display in the View.
 */
class uc_editablefields_product_handler_field_price extends uc_product_handler_field_price {

  // Extend formatter options.
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options;

    // Default formatter options.
    $format_options = array(
      'uc_price' => t('Ubercart price'),
      'numeric' => t('Numeric'),
    );

    // Add only 'clicktoedit' formatter.
    $format_options['clicktoedit'] = t('Click to Edit');

    $form['format'] =  array(
      '#title' => t('Format'),
      '#type' => 'radios',
      '#options' => $format_options,
      '#default_value' => $options['format'],
      '#weight' => 1,
    );

  }

  // Render the field.
  function render($values) {
    if ($this->options['format'] != 'clicktoedit') {
      return parent::render($values);
    }

    editablefields_load_js();

    $class = "editablefields clicktoedit";
    $pre = '<div class="' . $class . '" nid="' . $values->nid . '" field="' . $this->field . '" delta="' . '0' . '">';
    $pre .= theme('editablefields_clicktoedit_message');
    $post = '</div>';

    $product = node_load($values->{$this->aliases['nid']});
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

    return $pre . uc_price($product->{$this->real_field}, $context, $options) . $post;

  }

}