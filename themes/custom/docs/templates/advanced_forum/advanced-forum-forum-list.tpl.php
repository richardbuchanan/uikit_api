<?php
/**
 * @file
 * Default theme implementation to display a list of forums and containers.
 *
 * Available variables:
 * - $forums: An array of forums and containers to display. It is keyed to the
 *   numeric id's of all child forums and containers.
 * - $forum_id: Forum id for the current forum. Parent to all items within
 *   the $forums array.
 *
 * Each $forum in $forums contains:
 * - $forum->is_container: Is TRUE if the forum can contain other forums. Is
 *   FALSE if the forum can contain only topics.
 * - $forum->depth: How deep the forum is in the current hierarchy.
 * - $forum->zebra: 'even' or 'odd' string used for row class.
 * - $forum->name: The name of the forum.
 * - $forum->link: The URL to link to this forum.
 * - $forum->description: The description of this forum.
 * - $forum->new_topics: True if the forum contains unread posts.
 * - $forum->new_url: A URL to the forum's unread posts.
 * - $forum->new_text: Text for the above URL which tells how many new posts.
 * - $forum->old_topics: A count of posts that have already been read.
 * - $forum->total_posts: The total number of posts in the forum.
 * - $forum->last_reply: Text representing the last time a forum was posted or
 *   commented in.
 * - $forum->forum_image: If used, contains an image to display for the forum.
 *
 * @see template_preprocess_forum_list()
 * @see theme_forum_list()
 */
?>
<?php drupal_add_js('misc/tableheader.js'); ?>
<?php foreach ($tables as $table_id => $table): ?>
  <?php $table_info = $table['table_info']; ?>

  <div>
    <div>
      <?php if ($collapsible): ?>
        <button id="forum-collapsible-<?php print $table_info->tid; ?>" class="forum-collapsible uk-button uk-float-right">
          <i class="uk-icon uk-icon-chevron-up"></i>
        </button>
      <?php endif; ?>

      <?php if ($table_info->description): ?>
        <div class="uk-alert"><?php print $table_info->description; ?></div>
      <?php endif; ?>
    </div>

    <div id="forum-table-<?php print $table_info->tid; ?>">
      <table class="forum-table forum-table-forums uk-table uk-table-striped uk-table-middle sticky-enabled">
        <thead class="forum-header">
          <tr>
            <th class="forum-name"><?php print t('Forum'); ?></th>
            <th class="forum-topics"><?php print t('Topics'); ?></th>
            <th class="forum-posts"><?php print t('Posts'); ?></th>
            <th class="forum-last-post"><?php print t('Last post'); ?></th>
          </tr>
        </thead>

        <tbody id="forum-table-<?php print $table_info->tid; ?>-content">
          <?php foreach ($table['items'] as $item_id => $item): ?>
            <?php if ($item->is_container): ?>
              <tr id="subcontainer-<?php print $item_id; ?>" class="forum-row <?php print $item->zebra; ?> container-<?php print $item_id; ?>-child">
              <?php else: ?>
              <tr id="forum-<?php print $item_id; ?>" class="forum-row <?php print $item->zebra; ?> container-<?php print $item_id; ?>-child">
              <?php endif; ?>

              <?php $colspan = ($item->is_container) ? 4 : 1 ?>
              <td class="forum-details" colspan="<?php print $colspan ?>">
                <?php if (!empty($item->forum_image)): ?>
                  <span class="forum-image forum-image-<?php print $item_id; ?>">
                    <?php print $item->forum_image; ?>
                  </span>
                <?php else: ?>
                  <span class="<?php print $item->badge_classes; ?>">
                    <i class="<?php print $item->icon_classes ?>" title="<?php print $item->icon_text ?>"></i>
                  </span>
                <?php endif; ?>

                <span class="forum-name uk-margin-left uk-vertical-align-middle">
                  <a href="<?php print $item->link; ?>"><?php print $item->name; ?></a>
                </span>
                <?php if (!empty($item->description)): ?>
                  <div class="uk-form-help-block uk-margin-large-left uk-text-muted"><?php print $item->description; ?></div>
                <?php endif; ?>

                <?php if (!empty($item->subcontainers)): ?>
                  <div class="forum-subcontainers">
                    <span><?php print t("Subcontainers") ?>:</span> <?php print $item->subcontainers; ?>
                  </div>
                <?php endif; ?>
              </td>

              <?php if (!$item->is_container): ?>
                <td class="uk-text-top">
                  <span><?php print $item->total_topics ?></span>

                  <?php if ($item->new_topics): ?>
                    <span class="uk-badge uk-badge-notification uk-margin-small-left"><a href="<?php print $item->new_topics_link; ?>" class="uk-text-contrast"><?php print $item->new_topics_text; ?></a></span>
                  <?php endif; ?>
                </td>

                <td class="uk-text-top">
                  <span><?php print $item->total_posts ?></span>
                  <?php if ($item->new_posts): ?>
                    <br />
                    <a href="<?php print $item->new_posts_link; ?>"><?php print $item->new_posts_text; ?></a>
                  <?php endif; ?>
                </td>

                <td class="uk-text-top"><?php print $item->last_post ?></td>
              <?php endif; ?>

            </tr>

            <?php if (!empty($item->subforums)): ?>
              <?php foreach ($item->subforums as $subforum): ?>
                <tr>
                  <?php print $subforum; ?>
                </tr>
              <?php endforeach; ?>
            <?php endif; ?>

          <?php endforeach; ?>
        </tbody>
      </table>
    </div>
  </div>
<?php endforeach; ?>
