<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>
<xsl:param name="content">null</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[name() = 'sommet']">
	<xsl:choose>
		<xsl:when test="@id = $id">
			<xsl:copy>
				<xsl:apply-templates select="*|@*"/>
				<xsl:value-of select="$content" />
			</xsl:copy>
		</xsl:when>
		<xsl:otherwise>
			<xsl:copy>
				<xsl:apply-templates select="text()|*|@*"/>
			</xsl:copy>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

</xsl:stylesheet>