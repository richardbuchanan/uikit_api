(function($) {

  $(document).ready(function() {
    footerPosition();
  });

  $(window).resize(function() {
    footerPosition();
  });

  $(document).click(function() {
    footerPosition();
  });

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

  function footerPosition() {
    var bodyHeight = $('body').outerHeight(true) - 30;
    var adminMenu = $('#admin-menu');
    var page = $('#page');
    var pageHeader = $('#page-header');
    var footer = $('#footer');
    var contentHeight = adminMenu.outerHeight() + page.outerHeight() + pageHeader.outerHeight() + footer.outerHeight();

    if (contentHeight < bodyHeight) {
      footer.css({
        'position': 'fixed',
        'bottom': 0,
        'width': '100%'
      });
    }
    else {
      footer.css('position', 'static');
    }
  }

  /**
   * Copyright (c) 2014, Leon Sorokin
   * All rights reserved. (MIT Licensed)
   *
   * preCode.js - painkiller for <pre><code> & <textarea>
   */

  function preCode(selector) {

    var els = Array.prototype.slice.call(document.querySelectorAll(selector), 0);

    els.forEach(function(el){
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

      if (min === 1e3) return;

      el.textContent = txt.replace(new RegExp("^" + str, 'gm'), "");
    });
  }

})(jQuery);

(function($) {

  Drupal.behaviors.externalLinks = {
    attach: function () {
      $('a').each(function() {
        if (this.hostname !== location.host) {
          // Make sure all external links open in a new tab.
          $(this).prop('target', '_blank');

          if (/drupal/i.test(this.hostname)) {
            $(this).addClass('drupal-api');
          }
        }
      });
    }
  };

  Drupal.behaviors.stickySidebar = {
    attach: function () {
      $('#region-sidebar-second-wrapper').each(function() {
        var windowHeight = $(window).outerHeight() - $('#page-header').outerHeight();
        var sidebarHeight = $(this).outerHeight();

        if (sidebarHeight > windowHeight) {
          $(this).removeAttr('data-uk-sticky');
        }
      });
    }
  };

  Drupal.behaviors.stickySidebar = {
    attach: function () {
      $('#region-sidebar-second-wrapper').each(function() {
        var windowHeight = $(window).outerHeight() - $('#page-header').outerHeight();
        var sidebarHeight = $(this).outerHeight();

        if (sidebarHeight > windowHeight) {
          $(this).removeAttr('data-uk-sticky');
        }
      });
    }
  };

  Drupal.behaviors.docsSVGFallback = {
    attach: function () {
      if (!Modernizr.svg) {
        $('img[src*="svg"]').attr('src', function() {
          return $(this).attr('src').replace('.svg', '.png');
        });
      }
    }
  };

  Drupal.behaviors.selectCode = {
    attach: function () {
      $('pre.code-select').click(function() {
        $(this).select();

        var text = this,
          range, selection;

        if (document.body.createTextRange) {
          range = document.body.createTextRange();
          range.moveToElementText(text);
          range.select();
        } else if (window.getSelection) {
          selection = window.getSelection();
          range = document.createRange();
          range.selectNodeContents(text);
          selection.removeAllRanges();
          selection.addRange(range);
        }
      });
    }
  };

  Drupal.behaviors.emptyParagraphs = {
    attach: function () {
      $('p').filter(function () { return $.trim(this.innerHTML) === '' }).remove();
    }
  }
})(jQuery);
