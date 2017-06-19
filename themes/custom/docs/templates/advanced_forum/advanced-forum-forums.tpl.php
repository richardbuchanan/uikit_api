<?php

/**
 * @file
 * Default theme implementation to display a forum which may contain forum
 * containers as well as forum topics.
 *
 * Variables available:
 * - $forum_links: An array of links that allow a user to post new forum topics.
 *   It may also contain a string telling a user they must log in in order
 *   to post. Empty if there are no topics on the page. (ie: forum overview)
 *   This is no longer printed in the template by default because it was moved
 *   to the topic list section. The variable is still available for customizations.
 * - $forums: The forums to display (as processed by forum-list.tpl.php)
 * - $topics: The topics to display (as processed by forum-topic-list.tpl.php)
 * - $forums_defined: A flag to indicate that the forums are configured.
 * - $forum_legend: Legend to go with the forum graphics.
 * - $topic_legend: Legend to go with the topic graphics.
 * - $forum_tools: Drop down menu for various forum actions.
 * - $forum_description: Description that goes with forum term. Not printed by default.
 *
 * @see template_preprocess_forums()
 * @see advanced_forum_preprocess_forums()
 */
?>

<?php if ($forums_defined): ?>
  <div id="forum" class="uk-grid">

    <div id="forums" class="uk-width-large-3-4 uk-push-pull-large uk-width-medium-1-1 uk-push-pull-medium">
      <?php print $forums; ?>

      <?php if (!empty($topics)): ?>
        <div id="forum-topics">
          <?php print $topics; ?>
        </div>
      <?php endif; ?>

      <?php if ($latest_users): ?>
        <div class="uk-alert">
          <?php print t('Welcome to our latest members: !users', array('!users' => $latest_users)); ?>
        </div>
      <?php endif; ?>
    </div>

    <div class="uk-width-large-1-4 uk-width-large-1-4 uk-push-pull-large uk-width-medium-1-1 uk-push-pull-medium">
      <?php if (!empty($forum_legend)): ?>
        <div id="forum-legend" class="docs-legend">
          <?php print $forum_legend; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($topics)): ?>
        <div id="forum-topic-legend" class="docs-legend">
          <?php print $topic_legend; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($forum_statistics)): ?>
        <div id="forum-statistics">
          <?php print $forum_statistics; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($forum_tools)): ?>
        <div id="forum-tools">
          <?php print $forum_tools; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
<?php endif; ?>
