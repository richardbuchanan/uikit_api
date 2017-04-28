/**
 * @file
 * Attaches behaviors to UIkit theme settings forms.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.uikitFieldsetSummaries = {
    attach: function (context) {
      // Provide the summary for the base style form.
      $('fieldset.uikit-theme-settings-form', context).drupalSetSummary(function (context) {
        var vals = [];

        // Base style setting.
        vals.push($('.form-item-base-style select option:selected', context).text());

        return Drupal.checkPlain(vals.join(', '));
      });

      // Provide the summary for the mobile settings form.
      $('fieldset.uikit-mobile-settings-form', context).drupalSetSummary(function (context) {
        var vals = [];

        // IE compatibility mode setting.
        if ($('.form-item-x-ua-compatible select option:selected').val() !== '0') {
          var ieMode = $('.form-item-x-ua-compatible select option:selected', context).text();
          vals.push(ieMode);
        }

        // Character set setting.
        var charset = $('.form-item-meta-charset select option:selected', context).text().split(':');
        vals.push(charset[0]);

        return Drupal.checkPlain(vals.join(', '));
      });

      // Provide the summary for the page layouts form.
      $('fieldset.uikit-layout-settings-form', context).drupalSetSummary(function (context) {
        var vals = [];
        var standardLayout = $('input[name=standard_sidebar_positions]:checked', context)['0'].labels['0'].innerText.trim();
        var tabletLayout = $('input[name=tablet_sidebar_positions]:checked', context)['0'].labels['0'].innerText.trim();
        var mobileLayout = $('input[name=mobile_sidebar_positions]:checked', context)['0'].labels['0'].innerText.trim();

        // Standard layout setting.
        vals.push('<strong>Standard layout: </strong>' + standardLayout + '</br>');

        // Tablet layout setting.
        vals.push('<strong>Tablet layout: </strong>' + tabletLayout + '</br>');

        // Mobile layout setting.
        vals.push('<strong>Mobile layout: </strong>' + mobileLayout + '</br>');

        $.fn.toString = function () {
          return this[0].outerHTML;
        };

        return vals.join('');
      });
    }
  };

  Drupal.behaviors.uikitLayoutDemo = {
    attach: function (context) {
      // Provide a graphical demonstration of the standard layout.
      $('input[name=standard_sidebar_positions]', context).click(function () {
        var itemClass = 'uk-layout-' + $(this).attr('value');
        var target = $('#edit-standard-layout-demo');

        // Remove all possible layout classes.
        target.removeClass('uk-layout-holy-grail')
          .removeClass('uk-layout-sidebars-left')
          .removeClass('uk-layout-sidebars-right');

        // Add a class based on which radio is selected.
        target.addClass(itemClass);
      });

      $('input[name=tablet_sidebar_positions]', context).click(function () {
        // Provide a graphical demonstration of the tablet layout.
        var itemClass = 'uk-layout-' + $(this).attr('value');
        var target = $('#edit-tablet-layout-demo');

        // Remove all possible layout classes.
        target.removeClass('uk-layout-holy-grail')
          .removeClass('uk-layout-sidebars-left')
          .removeClass('uk-layout-sidebar-left-stacked')
          .removeClass('uk-layout-sidebars-right')
          .removeClass('uk-layout-sidebar-right-stacked');

        // Add a class based on which radio is selected.
        target.addClass(itemClass);
      });

      $('input[name=mobile_sidebar_positions]', context).click(function () {
        // Provide a graphical demonstration of the mobile layout.
        var itemClass = 'uk-layout-' + $(this).attr('value');
        var target = $('#edit-mobile-layout-demo');

        // Remove all possible layout classes.
        target.removeClass('uk-layout-sidebars-stacked')
          .removeClass('uk-layout-sidebars-vertical');

        // Add a class based on which radio is selected.
        target.addClass(itemClass);
      });
    }
  };

  Drupal.behaviors.uikitLocalTasksDemo = {
    attach: function (context) {
      // Provide a graphical demonstration of the primary local tasks style.
      var primaryValue = $('select[name=primary_tasks_style] option:selected').val();
      var secondaryValue = $('select[name=secondary_tasks_style] option:selected').val();
      var primaryMenu = $('#edit-primary-tasks').find('ul');
      var secondaryMenu = $('#edit-secondary-tasks').find('ul');

      // Add the initial class to the demo menus.
      $('#edit-primary-tasks', context).once('edit-primary-tasks').each(function() {
        if (primaryValue === 'uk-tab') {
          $(this).find('ul').addClass(primaryValue);
        }
        else {
          $(this).find('ul')
            .addClass('uk-subnav')
            .addClass(primaryValue);
        }
      });

      $('#edit-secondary-tasks', context).once('edit-secondary-tasks').each(function() {
        $(this).find('ul')
          .addClass('uk-subnav')
          .addClass(secondaryValue);
      });

      // Change the demo menu classes when the setting is changed.
      $('select[name=primary_tasks_style]').change(function () {
        primaryMenu
          .removeClass('uk-subnav')
          .removeClass('uk-subnav-line')
          .removeClass('uk-subnav-pill')
          .removeClass('uk-tab');

        if ($(this).val() === 'uk-tab') {
          primaryMenu.addClass($(this).val());
        }
        else if ($(this).val() === '0') {
          primaryMenu.addClass('uk-subnav');
        }
        else {
          primaryMenu
            .addClass('uk-subnav')
            .addClass($(this).val());
        }
      });

      $('select[name=secondary_tasks_style]').change(function () {
        secondaryMenu.removeClass('uk-subnav-line')
          .removeClass('uk-subnav-pill');

        if ($(this).val() !== '0') {
          secondaryMenu.addClass($(this).val());
        }
      });
    }
  };
})(jQuery);
