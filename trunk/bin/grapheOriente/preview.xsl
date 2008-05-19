<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 Paul HUYNH <paulytech AT gmail.com>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="x">5</xsl:param>
<xsl:param name="y">5</xsl:param>
<xsl:param name="w">50</xsl:param>
<xsl:param name="h">40</xsl:param>

<xsl:template match="*|@*|processing-instruction()">
	<xsl:copy>
		<xsl:apply-templates select="processing-instruction()|text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[name() = 'svg']">
	<xsl:copy>
		<!-- Recopier les elements existants -->
		<xsl:apply-templates select="@*|node()|processing-instruction()"/>
		
		<!-- Ajouter le rectangle d'apercu -->
		<rect class="previewArea">
			<xsl:attribute name="x"><xsl:value-of select="$x" /></xsl:attribute>
			<xsl:attribute name="y"><xsl:value-of select="$y" /></xsl:attribute>
			<xsl:attribute name="width"><xsl:value-of select="$w" /></xsl:attribute>
			<xsl:attribute name="height"><xsl:value-of select="$h" /></xsl:attribute>
		</rect>
	</xsl:copy>

</xsl:template>

</xsl:stylesheet>
