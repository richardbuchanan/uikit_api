<?php

/**
 * @file
 * Theme implementation: Template for each forum post whether node or comment.
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
 * - $author_pane: Entire contents of the Author Pane template.
 */
?>
<?php if ($top_post): ?>
  <?php print $topic_header ?>
<?php endif; ?>

<article id="<?php print $post_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a id="forum-topic-top"></a>

  <header class="uk-comment-header">
    <div class="uk-float-right">
      <?php print $permalink; ?>
      <?php if (!empty($new)): ?>
        <a id="new"><span class="new"> (<?php print $new ?>)</span></a>
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
    <?php if (!$node->status): ?>
      <div class="uk-float-right"><?php print t("Unpublished post") ?></div>
    <?php endif; ?>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['taxonomy_forums']);
      hide($content['comments']);
      hide($content['links']);
      if (!$top_post)
        hide($content['body']);
      print render($content);
    ?>

    <?php if (!empty($post_edited) || !empty($author_signature)): ?>
      <div class="uk-display-inline-block uk-margin-top uk-margin-bottom uk-width-1-1">
        <?php if (!empty($post_edited)): ?>
          <div class="uk-float-left">
            <?php print $post_edited ?>
          </div>
        <?php endif; ?>

        <?php if (!empty($author_signature)): ?>
          <div class="uk-float-right">
            <blockquote><?php print $author_signature; ?></blockquote>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <div class="uk-margin-bottom">
      <a href="#forum-topic-top" title="<?php print t('Jump to top of page'); ?>" class="af-button-small">
        <span><?php print t("Top"); ?></span>
      </a>

      <div class="uk-float-right">
        <?php print render($content['links']); ?>
      </div>
    </div>

  </div>
</article>

<hr class="uk-article-divider">
<?php print render($content['comments']); ?>
