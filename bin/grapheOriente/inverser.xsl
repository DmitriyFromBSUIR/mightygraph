<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:choose>
			<xsl:when test="@id = $id">
				<xsl:attribute name="source"><xsl:value-of select="@destination" /></xsl:attribute>
				<xsl:attribute name="destination"><xsl:value-of select="@source" /></xsl:attribute>
				<xsl:apply-templates select="text()|*|@*[not(name() = 'source' or name() = 'destination')]"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:apply-templates select="text()|*|@*"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:copy>
</xsl:template>
</xsl:stylesheet>