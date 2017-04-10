/**
 * @file
 * Attaches behaviors for UIkit's advanced form elements.
 *
 * Grouped checkboxes and radios do not need to be wrapped in a uk-form-row
 * element.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.uikitFormAdvanced = {
    attach: function (context) {
      var querySelector = $('fieldset[data-drupal-selector]');

      querySelector.each(function () {
        var parentID = $(this).attr('data-drupal-selector');
        var children = $('#' + parentID).children('.form-item:not(:first-of-type)');

        children.each(function () {
          var checkbox = $(this).hasClass('form-type-checkbox') || $(this).hasClass('js-form-type-checkbox');
          var radio = $(this).hasClass('form-type-radio') || $(this).hasClass('js-form-type-radio');

          if (checkbox || radio) {
            $(this).removeClass('uk-form-row');
          }
        })
      })
    }
  };
})(jQuery);