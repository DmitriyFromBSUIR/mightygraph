<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="@posh[.='0']" priority="1">
    <xsl:attribute name="id">5</xsl:attribute>
</xsl:template>


<xsl:template match="@*|node()" priority="0">
	<xsl:copy>
		<xsl:apply-templates select="@*|node()"/>
	</xsl:copy>
</xsl:template>
</xsl:stylesheet>