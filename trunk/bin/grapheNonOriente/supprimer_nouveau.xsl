<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="*[not(@highlighted = '1')]|@*">
	<xsl:copy>
	<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[@highlighted = '1']">
	<xsl:apply-templates select="*"/>
</xsl:template>

</xsl:stylesheet>