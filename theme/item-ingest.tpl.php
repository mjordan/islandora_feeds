<?php
/**
 * @file
 * This is the ingest template file for the default Islandora Feeds object page.
 */
?>

<fielddata>
 <title label="Title"><?php print $title; ?></title>
 <?php foreach($variables['field_data'] as $field_data): ?>
     <<?php print $field_data['field_name']; ?> label="<?php print $field_data['field_label']; ?>"><?php print $field_data['field_value']; ?></<?php print $field_data['field_name'];?>>
 <?php endforeach; ?>
</fielddata>

