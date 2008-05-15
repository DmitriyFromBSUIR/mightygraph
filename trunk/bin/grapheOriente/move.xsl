<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="diffx">1</xsl:param>
<xsl:param name="diffy">1</xsl:param>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[@highlighted = '1' and name() = 'sommet']">
	<xsl:copy>
		<xsl:attribute name="posh">
			<xsl:value-of select="@posh +$diffx" />
		</xsl:attribute>

		<xsl:attribute name="posv">
			<xsl:value-of select="@posv +$diffy" />
		</xsl:attribute>
		<xsl:apply-templates select="text()|*|@*[not(name() = 'posh' or name() = 'posv')]"/>
	</xsl:copy>

</xsl:template>

</xsl:stylesheet>