<?php
/**
 * @file
 * This is the template file for the default Islandora Feeds object page.
 */
$islandora_content = $islandora_object['DATA']->content;
?>

<div class="islandora-feeds-object islandora">
  <div class ="feeds_thumb">
    <?php print $variables['islandora_thumbnail_img'] ?>
  </div>
  <div class="islandora-basic-image-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-feeds-content">
        <?php print $islandora_content; ?>
      </div>
    <?php endif; ?>
  </div>

