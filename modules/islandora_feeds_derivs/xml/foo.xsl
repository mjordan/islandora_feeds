<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Sample XSL stylesheet for creating a FOO derivative from OBJ datastreams created
       by the Islandora Feeds module. -->

  <xsl:param name="DSID">FOO</xsl:param>
  <xsl:param name="DSLABEL">FOO record</xsl:param>

  <xsl:template match="/">
        <foo>
	<!-- The title is the only element we grab from the OBJ. -->
	<title label = "Title"><xsl:value-of select="fielddata/title"/></title>
        <someOtherElement label = "Some other element">Some value</someOtherElement>
        </foo>
  </xsl:template>
</xsl:stylesheet>

