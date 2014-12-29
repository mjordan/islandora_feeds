# Islandora Feeds Derivs

## Requirements

[Islandora Feeds](https://github.com/mjordan/islandora_feeds)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Overview

This module allows generating a MODS (or other XML) datastream from an OBJ datastream created by the Islandora Feeds module.

Given a OBJ datastream like this:

```xml
<fielddata>
  <title label="Title">Object's witty title</title>
  <field_1 label="Field 1">Object's field 1 value</field_1>
  <field_2 label="Field 2">Object's field 2 value</field_2>
</fielddata>
```
this module creates a MODS datastream like this and adds it to the object:

```xml
<!-- MODS markup that precedes titleInfo goes here -->
<titleInfo>
  <title>Object's witty title</title>
  <subTitle/>
</titleInfo>
<!-- MODS markup that follows titleInfo goes here -->
```

(Only the '<titleInfo>' fragment is provided in this example because that's the only element in the MODS datastream this module populates.)

## Configuration

In addition to configuring some settings using the admin settings form at admin/islandora/tools/feeds/derivs, all you need to do to create XML derivatives for objects you are ingesting via Islandora Feeds is to is write an XSL stylesheet to transform the OBJ datastream created by that solution pack into your desired derivative. You can create multiple datastreams at once if you provide multiple XSL files. The admin settings (which are also linked to from within the admin settings of the Islandora Feeds, if the module is enabled) look like this:

![Islandora Feeds Derivs](https://dl.dropboxusercontent.com/u/1015702/linked_to/islandora_feeds_derivs_admin.png)

The module can not only generate deriviate XML datastreams from the OBJ, it can:

* share objects that are imported by Islandora Feeds with specific collections
* change the objects' content model on the fly
* delete the OBJ datastream

These last three options are useful if your ultimate goal is to import CSV data into MODS datastreams in an arbitrary collection, into objects of an arbitrary content model. In other words, if you have CSV data that describes still images, you can import it using Islandora Feeds, write a stylesheet that transforms the resulting OBJ datastreams into MODS, configure Islandora Feeds Derivs to create the MODS datastreams, and to clean up, delete the OBJ datastream, change the content model to islandora:sp_basic_image, and share the objects with the collection that contains still images.

## Usage

Since Islandora Feeds Derivs can create any XML datastream from the flat XML created by Islandora Feeds, you can use it to import MODS datastreams. The XSL stylesheet provided with the module is a good place to start; it only copies the OBJ's 'title' element into the MODS template, but you can modify it, or copy it and create another stylesheet, to suite your specific needs.

A typical workflow for using Islandora Feeds to import data that will end up in MODS datastreams would be:

1. Create a Drupal content type that has a text field for each element in the MODS records you want to populate.
2. Test the content type by importing some test data from a CSV. Run the resulting OBJ datastreams against a stylesheet (externally, using your favorite XSLT processor) based on the one you are goin to use with the Islandora Feeds Derivs module.
3. When you are satisfied with your offline tests, upload your stylesheet into the Islandora Feeds Derivs' /xml directory and configure Islandora Feeds Derivs to use your stylesheet to create MODS datastreams, to delete the OBJ datastream, and to set the preferred target collection and content models for your objects.

## XSL Stylesheets used by this module

They are standard stylesheets, but they need to have two `<xsl:param>` elements that identify the datastream ID and datastream label of the destination datastream. For example, the foo.xsl stylesheet included with the module uses these two parameters as follows to indicate that the destination datastream's ID is 'FOO' and its label is 'FOO record':

``` xml
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:param name="DSID">FOO</xsl:param>
  <xsl:param name="DSLABEL">FOO record</xsl:param>

  <xsl:template match="/">
	<!-- The title is the only element we grab from the OBJ. -->
	<title><xsl:value-of select="fielddata/title"/></title>
        <someelement>Some value</someelement>
  </xsl:template>
</xsl:stylesheet>
```
If your stylesheet doesn't contain these elements, a default DSID of 'NONEPROVIDED' and a default datastream label of 'None provided' will be used. Also, since the OBJ datastream's XML uses 'fielddata' as its document element, your stylesheet's XPath queries should be relative to that element.

Finally, since your stylesheets need to live inside the Feeds Deriv's 'xml' directory, alway keep backups so they don't get accidently deleted during upgrade.

## Troubleshooting/issues/feedback

Use cases are welcome. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

