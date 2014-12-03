<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Select the root element. -->
<xsl:template match="/*">
  <div>
    <table>
      <tr><th>Field</th><th>Value</th></tr>
      <xsl:apply-templates/>
    </table>
  </div>
</xsl:template>

<!-- Select all children of the root node. -->
<xsl:template match="*">
      <tr><td><xsl:value-of select="name()"/></td><td><xsl:value-of select="."/></td></tr>
</xsl:template>

</xsl:stylesheet>

