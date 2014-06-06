<?php

/**
 * Query the resource index to get a list of collections or content
 * models.
 *
 * @param $type string
 *  Either 'collections' or 'cmodels'.
 *
 * @return array
 *   List of PIDs corresponding to the collections or content models.
 */
function islandora_feeds_get_collections_or_content_models($type) {
  $types = array(
    'collections' => 'islandora:collectionCModel',
    'cmodels' => 'fedora-system:ContentModel-3.0'
  );
  $type_for_query = '<info:fedora/' . $types[$type] . '>';
  // Query the rindex to get all collections.
  $tuque = islandora_get_tuque_connection();
  $ri_query = "select \$object \$label from <#ri>
     where \$object <fedora-model:hasModel> $type_for_query
      and \$object <fedora-model:label> \$label";
  $results = $tuque->repository->ri->itqlQuery($ri_query, 'unlimited');
  $ret = array();
  foreach ($results as $member) {
    $pid = preg_replace('/info:fedora\//', '', $member['object']['value']);
    $label = $member['label']['value'];
    // We don't want the root collection.
    if ($pid == 'islandora:root') {
      $label = 'Islandora Root Collection';
    }
    $ret[$pid] = $label;
  }
  return $ret;
}

function islandora_feeds_create_xml_datastream($item, $entity) {
  $xml = new XMLWriter();
  $xml->openMemory();
  $xml->setIndent(TRUE);
  $xml->startDocument('1.0', 'utf-8', NULL);
  $xml->startElement('custom');
  foreach ($item as $field => $value) {
    $clean_field = str_replace(' ', '_', $field);
    $xml->writeElement($clean_field, $value);
  }
  $xml->endElement();
  return $xml->outputMemory();
}

