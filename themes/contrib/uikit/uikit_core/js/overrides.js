/**
 * @file
 * Attaches behaviors to the UIkit theme.
 */

(function ($) {
  'use strict';

  $('a').each(function () {
    var href = $(this).attr('href');

    if (href === '# ') {
      $(this).attr('href', '#');

      if ($(this).parent('[data-uk-dropdown]').length) {
        $(this).attr('href', '').on('click', function (e) {
          e.preventDefault();
        });
      }
    }
  });
})(jQuery);
