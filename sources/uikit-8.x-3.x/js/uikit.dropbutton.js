/**
 * @file
 * Attaches behaviors for UIkit's dropbutton elements.
 *
 * Drupal uses input elements in dropdown links, but UIkit does not style these
 * correctly in the dropdown component. The uk-button class needs to be removed
 * from the dropdown components dropdown nav items.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.uikitDropButton = {
    attach: function () {
      var dropdownNav = $('.uk-nav-dropdown');
      var dropdownLinks = dropdownNav.children();

      dropdownLinks.each(function() {
        $(this).find('.uk-button').addClass('uk-button-link-reset');
      })
    }
  };
})(jQuery);