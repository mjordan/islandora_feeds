<?php
/**
 * @file
 * Template file for a Form Builder form definition file generated by the
 * Islandora Feeds module.
 *
 * Available variables:
 *   $documentation string
 *     A string describing what software generated the form definition and when.
 *   $content_type string
 *     The content type the schema is based on.
 *   $fields array
 *     An associative array of all the fields in the content type, with the keys
 *     'field_name' and 'field_label'.
 */
?>
<?php print '<?xml version="1.0"?>' . "\n"; ?>
<definition xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" version="3">
  <?php print "<!-- " . trim($documentation) . " -->\n"; ?>
  <properties>
    <root_name>fielddata</root_name>
    <schema_uri/>
    <namespaces/>
  </properties>
  <form>
    <properties>
      <type>form</type>
      <access>TRUE</access>
      <collapsed>FALSE</collapsed>
      <collapsible>FALSE</collapsible>
      <disabled>FALSE</disabled>
      <executes_submit_callback>FALSE</executes_submit_callback>
      <multiple>FALSE</multiple>
      <required>FALSE</required>
      <resizable>FALSE</resizable>
      <tree>TRUE</tree>
      <actions>
        <create>NULL</create>
        <read>
          <path>/fielddata</path>
          <context>document</context>
        </read>
        <update>NULL</update>
        <delete>NULL</delete>
      </actions>
    </properties>
    <children>
      <element name="title">
        <properties>
          <type>textarea</type>
          <access>TRUE</access>
          <collapsed>FALSE</collapsed>
          <collapsible>FALSE</collapsible>
          <description>The title of the object.</description>
          <disabled>FALSE</disabled>
          <executes_submit_callback>FALSE</executes_submit_callback>
          <multiple>FALSE</multiple>
          <required>FALSE</required>
          <resizable>FALSE</resizable>
          <title>Title</title>
          <tree>TRUE</tree>
          <actions>
            <create>
              <path>self::node()</path>
              <context>parent</context>
              <schema/>
              <type>element</type>
              <prefix>NULL</prefix>
              <value>title</value>
            </create>
            <read>
              <path>title</path>
              <context>parent</context>
            </read>
            <update>
              <path>self::node()</path>
              <context>self</context>
            </update>
            <delete>NULL</delete>
          </actions>
        </properties>
        <children/>
      </element>
      <?php foreach($variables['fields'] as $field => $config): ?>
      <?php if($field != 'title'): ?>
      <element name="<?php print $config['field_name']; ?>">
        <properties>
          <type>textarea</type>
          <access>TRUE</access>
          <collapsed>FALSE</collapsed>
          <collapsible>FALSE</collapsible>
          <description></description>
          <disabled>FALSE</disabled>
          <executes_submit_callback>FALSE</executes_submit_callback>
          <multiple>FALSE</multiple>
          <required>FALSE</required>
          <resizable>FALSE</resizable>
          <title><?php print $config['field_label']; ?></title>
          <tree>TRUE</tree>
          <actions>
            <create>
              <path>self::node()</path>
              <context>parent</context>
              <schema/>
              <type>element</type>
              <prefix>NULL</prefix>
              <value><?php print $config['field_name']; ?></value>
            </create>
            <read>
              <path><?php print $config['field_name']; ?></path>
              <context>parent</context>
            </read>
            <update>
              <path>self::node()</path>
              <context>self</context>
            </update>
            <delete>
              <path>self::node()</path>
              <context>self</context>
            </delete>
          </actions>
        </properties>
        <children/>
      </element>
      <?php endif; ?>
      <?php endforeach; ?>
    </children>
  </form>
</definition>
