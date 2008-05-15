<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="newId">-2</xsl:param>
<xsl:param name="posh">100</xsl:param>
<xsl:param name="posv">100</xsl:param>
<xsl:param name="value">DEFAULT</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[name() = 'graphe']">
	<xsl:copy>
		<!-- Recopier les elements existants -->
		<xsl:apply-templates select="@*|node()"/>
		
		<!-- Ajouter le nouveau sommet -->
		<sommet>
			<xsl:attribute name="id">
				<xsl:value-of select="$newId" />
			</xsl:attribute>
			<xsl:attribute name="posh">
				<xsl:value-of select="$posh" />
			</xsl:attribute>
			<xsl:attribute name="posv">
				<xsl:value-of select="$posv" />
			</xsl:attribute>
			<xsl:value-of select="$value" />
		</sommet>
	</xsl:copy>

</xsl:template>

</xsl:stylesheet>
