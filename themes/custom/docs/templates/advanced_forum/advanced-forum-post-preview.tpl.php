<?php

/**
 * @file
 * Theme implementation: Template the preview version of a post.
 *
 * All variables available in node.tpl.php and comment.tpl.php for your theme
 * are available here. In addition, Advanced Forum makes available the following
 * variables:
 *
 * - $top_post: TRUE if we are formatting the main post (ie, not a comment)
 * - $reply_link: Text link / button to reply to topic.
 * - $total_posts: Number of posts in topic (not counting first post).
 * - $new_posts: Number of new posts in topic, and link to first new.
 * - $links_array: Unformatted array of links.
 * - $account: User object of the post author.
 * - $name: User name of post author.
 * - $author_pane: Entire contents of advanced_forum-author-pane.tpl.php.
 */
?>
<article id="<?php print $post_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($top_post): ?>
    <a id="forum-topic-top"></a>
  <?php else: ?>
    <a id="forum-reply-preview"></a>
  <?php endif; ?>

  <header class="uk-comment-header">
    <div class="uk-float-right">
      <?php if (!$top_post && !empty($comment_link) && !empty($page_link)): ?>
        <?php print $comment_link . ' | ' . $page_link; ?>
      <?php endif; ?>
    </div>

    <?php if (!empty($author_pane)): ?>
      <?php print $author_pane; ?>
    <?php endif; ?>

    <?php if (!empty($title)): ?>
      <h4 class="uk-comment-title"><?php print $title ?></h4>
    <?php endif; ?>

    <div class="uk-comment-meta">
      <?php print $date ?> | <?php print $author_link; ?>
    </div>

    <?php if (!$top_post): ?>
      <?php if (!empty($first_new)): ?>
        <?php print $first_new; ?>
      <?php endif; ?>

      <?php if (!empty($new_output)): ?>
        <?php print $new_output; ?>
      <?php endif; ?>
    <?php endif; ?>
  </header>

  <div class="uk-comment-body">
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['taxonomy_forums']);
      hide($content['comments']);
      if (!$top_post)
        hide($content['body']);
      hide($content['links']);
      print render($content);
    ?>

    <?php if (!empty($signature)): ?>
      <?php print $signature ?>
    <?php endif; ?>
  </div>
</article>
