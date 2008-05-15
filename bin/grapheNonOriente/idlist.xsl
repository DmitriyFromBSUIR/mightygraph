<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<idlist>
		<xsl:for-each select="graphe/*">
			<xsl:sort select="@id" order="descending" data-type="number"/>
			<id><xsl:value-of select="@id"/></id>
		</xsl:for-each>
	</idlist>
</xsl:template>
</xsl:stylesheet>
