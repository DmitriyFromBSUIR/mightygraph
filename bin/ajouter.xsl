<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="posh">100</xsl:param>
<xsl:param name="posv">100</xsl:param>
<xsl:param name="value">DEFAULT</xsl:param>

<xsl:template match="/graphe/*[1]" priority="1">
	<sommet id="5">
		<xsl:attribute name="posh">
			<xsl:value-of select="$posh" />
		</xsl:attribute>
		<xsl:attribute name="posv">
			<xsl:value-of select="$posv" />
		</xsl:attribute>
		<xsl:value-of select="$value" />
	</sommet>

	<xsl:copy>
		<xsl:apply-templates select="@*|node()"/>
	</xsl:copy>


</xsl:template>

<xsl:template match="@*|node()" priority="0">
	<xsl:copy>
		<xsl:apply-templates select="@*|node()"/>
	</xsl:copy>
</xsl:template>
</xsl:stylesheet>
