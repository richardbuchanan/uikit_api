<?php

/**
 * @file
 * Theme implementation: Template for forum topic header.
 *
 * - $node: Node object.
 * - $search: Search box to search this topic (Requires Node Comments)
 * - $reply_link: Text link / button to reply to topic.
 * - $total_posts_count: Number of posts in topic.
 * - $new_posts_count: Number of new posts in topic.
 * - $first_new_post_link: Link to first unread post.
 * - $last_post_link: Link to last post.
 * - $pager: Topic pager.
 */
?>

<div id="forum-topic-header" class="uk-grid">
  <?php if (!empty($search)): ?>
    <?php print $search; ?>
  <?php endif; ?>

  <div class="uk-width-1-1 uk-margin-bottom">
    <?php if (!empty($reply_link)): ?>
      <div class="uk-float-left">
        <?php print $reply_link; ?>
      </div>
    <?php endif; ?>

    <div class="uk-float-right">
      <?php print $total_posts_count; ?> / <?php print t('!new new', array('!new' => $new_posts_count)); ?>
    </div>
  </div>

  <?php if (!empty($first_new_post_link) || !empty($last_post_link)): ?>
    <div class="uk-width-1-1 uk-margin-bottom">
      <ul class="uk-subnav uk-subnav-line">
        <?php if (!empty($first_new_post_link)): ?>
          <li><?php print $first_new_post_link; ?></li>
        <?php endif; ?>

        <?php if (!empty($last_post_link)): ?>
          <li><?php print $last_post_link; ?></li>
        <?php endif; ?>
      </ul>
    </div>
  <?php endif; ?>
</div>
