(function($){

  $(function() {

    // highlight.js will take our code blocks and add syntax highlighting for
    // us. Here we just tell it to take over things.
    preCode("pre.highlight code, pre.uikit-api-text code, pre.php code.php, textarea");

    if (window.hljs) {
      $('pre > code').each(function(i, e) { hljs.highlightBlock(e); });
    }

    // Prevent empty anchor tags from being followed.
    $('article').on('click', '[href="#"], [href=""]', function (e) {
      e.preventDefault();
    });

  });


  /**
   * Copyright (c) 2014, Leon Sorokin
   * All rights reserved. (MIT Licensed)
   *
   * preCode.js - painkiller for <pre><code> & <textarea>
   */

  function preCode(selector) {

    var els = Array.prototype.slice.call(document.querySelectorAll(selector), 0);

    els.forEach(function(el, idx, arr){
      var txt = el.textContent
        .replace(/^[\r\n]+/, "")	// strip leading newline
        .replace(/\s+$/g, "");		// strip trailing whitespace

      if (/^\S/gm.test(txt)) {
        el.textContent = txt;
        return;
      }

      var mat, str, re = /^[\t ]+/gm, len, min = 1e3;

      while (mat = re.exec(txt)) {
        len = mat[0].length;

        if (len < min) {
          min = len;
          str = mat[0];
        }
      }

      if (min == 1e3) return;

      el.textContent = txt.replace(new RegExp("^" + str, 'gm'), "");
    });
  }

})(jQuery);

(function($) {
  Drupal.behaviors.externalLinks = {
    attach: function () {
      $('a').each(function() {
        if (this.hostname != location.host) {
          // Make sure all external links open in a new tab.
          $(this).prop('target', '_blank');

          if (/drupal/i.test(this.hostname)) {
            $(this).addClass('drupal-api');
          }
        }
      });
    }
  };
})(jQuery);