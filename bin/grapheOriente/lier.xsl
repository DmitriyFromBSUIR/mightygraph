<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="newId">-2</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[@highlighted = '1'][1]">
		<!-- Ajouter le nouveau sommet -->
		<liaison>
			<xsl:attribute name="id">
				<xsl:value-of select="$newId" />
			</xsl:attribute>
			<xsl:attribute name="source">
				<xsl:value-of select="@id" />
			</xsl:attribute>
			<xsl:attribute name="destination">
				<xsl:value-of select="//*[@highlighted = '1'][2]/@id" />
			</xsl:attribute>
		</liaison>
	
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
	

</xsl:template>


</xsl:stylesheet>
