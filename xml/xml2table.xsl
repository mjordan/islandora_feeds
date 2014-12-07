<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!-- Select the root element. -->
<xsl:template match="/*">
  <div>
    <table>
      <xsl:apply-templates/>
    </table>
  </div>
</xsl:template>

<!-- Select all children of the root node. -->
<xsl:template match="*">
      <tr><th><xsl:value-of select="@label"/></th><td><xsl:value-of select="."/></td></tr>
</xsl:template>

</xsl:stylesheet>

