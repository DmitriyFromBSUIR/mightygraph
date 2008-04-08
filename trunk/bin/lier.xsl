<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="newId">-2</xsl:param>
<xsl:param name="id">0</xsl:param>
<xsl:param name="id2">1</xsl:param>

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
		<liaison>
			<xsl:attribute name="id">
				<xsl:value-of select="$newId" />
			</xsl:attribute>
			<xsl:attribute name="source">
				<xsl:value-of select="$id" />
			</xsl:attribute>
			<xsl:attribute name="destination">
				<xsl:value-of select="$id2" />
			</xsl:attribute>
		</liaison>
	</xsl:copy>

</xsl:template>

</xsl:stylesheet>
