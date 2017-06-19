<?php
/**
 * @file
 * Theme implementation: Template for each forum forum statistics section.
 *
 * Available variables:
 * - $current_total: Total number of users currently online.
 * - $current_users: Number of logged in users.
 * - $current_guests: Number of anonymous users.
 * - $online_users: List of logged in users.
 * - $topics: Total number of nodes (threads / topics).
 * - $posts: Total number of nodes + comments.
 * - $users: Total number of registered active users.
 * - $latest_users: Linked user names of latest active users.
 */
?>
<ul class="uk-list uk-list-striped">
  <li><?php print t('Currently active users: !current_total', array('!current_total' => $current_total)); ?></li>
  <?php if (!empty($online_users)) : ?>
    <li><?php print t('Online users: !currently_online', array('!currently_online' => $online_users)); ?></li>
  <?php endif; ?>
  <li><?php print t('Topics: !topics', array('!topics' => $topics)); ?></li>
  <li><?php print t('Posts: !posts', array('!posts' => $posts)); ?></li>
  <li><?php print t('Users: !users', array('!users' => $users)); ?></li>
</ul>
