<!DOCTYPE>
<html lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>">

  <?php print $page_top; ?>

  <nav class="uk-navbar uk-navbar-attached uk-margin-bottom">
    <div class="uk-container uk-container-center uk-text-center">
      <?php if ($title): ?>
        <h1 class="uk-navbar-brand uk-margin-remove"><?php print $title; ?></h1>
      <?php endif; ?>
    </div>
  </nav>

  <div class="uk-container uk-container-center">
    <div class="uk-grid" data-uk-grid-margin>

      <?php if ($sidebar_first): ?>
        <div class="docs-sidebar uk-width-medium-1-4 uk-hidden-small uk-row-first">
          <?php if ($logo): ?>
            <img class="uk-margin-left" src="<?php print $logo ?>" alt="<?php print $site_name ?>" />
          <?php endif; ?>
          <?php print $sidebar_first ?>
        </div>
      <?php endif; ?>

      <div class="docs-main uk-width-medium-3-4">
        <?php if ($messages): ?>
          <div id="console"><?php print $messages; ?></div>
        <?php endif; ?>
        <?php if ($help): ?>
          <div id="help">
            <?php print $help; ?>
          </div>
        <?php endif; ?>
        <?php print $content; ?>
      </div>

    </div>
  </div>

  <?php print $page_bottom; ?>

  </body>
</html>
