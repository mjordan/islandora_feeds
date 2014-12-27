<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- Sample XSL stylesheet for creating MODS derivatives from OBJ datastreams created
       by the Islandora Feeds module. -->

  <xsl:template match="/">
    <mods xmlns="http://www.loc.gov/mods/v3" xmlns:mods="http://www.loc.gov/mods/v3" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xlink="http://www.w3.org/1999/xlink">
      <titleInfo>
	<!-- The title is the only element we grab from the OBJ. -->
	<title><xsl:value-of select="fielddata/title"/></title>
	<subTitle/>
      </titleInfo>
      <name type="personal">
	<namePart/>
	<role>
	  <roleTerm authority="marcrelator" type="text"/>
	</role>
      </name>
      <typeOfResource></typeOfResource>
      <genre></genre>
      <originInfo>
	<dateIssued/>
	<publisher/>
	<place>
	  <placeTerm authority="marccountry" type="code"/>
	</place>
	<place>
	  <placeTerm type="text"/>
	</place>
      </originInfo>
      <language>
	<languageTerm authority="iso639-2b" type="code"/>
      </language>
      <abstract/>
      <identifier type="local"></identifier>
      <physicalDescription>
	<form></form>
	<extent/>
      </physicalDescription>
      <note/>
      <subject>
	<topic/>
	<geographic/>
	<temporal/>
	<hierarchicalGeographic>
	  <continent/>
	  <country/>
	  <province/>
	  <region/>
	  <county/>
	  <city/>
	  <citySection/>
	</hierarchicalGeographic>
	<cartographics>
	  <coordinates/>
	</cartographics>
      </subject>
  </mods>
  </xsl:template>
</xsl:stylesheet>

