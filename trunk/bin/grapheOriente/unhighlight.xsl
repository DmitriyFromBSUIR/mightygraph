<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:if test="@id = $id">
			<xsl:attribute name="highlighted">0</xsl:attribute>
		</xsl:if>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

</xsl:stylesheet>