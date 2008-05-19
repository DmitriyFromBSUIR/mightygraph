<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>

<xsl:template match="/">
	<position>
		<xsl:for-each select="//*[name() = 'rect']">
			<xsl:if test="@id = concat('rect_', $id)">
				<x><xsl:value-of select="@x"/></x>
				<y><xsl:value-of select="@y"/></y>
				<width><xsl:value-of select="@width"/></width>
				<height><xsl:value-of select="@height"/></height>
				<content><xsl:value-of select="//*[name() = 'text' and @id = concat('text_', $id)]"/></content>
			</xsl:if>
		</xsl:for-each>
	</position>
</xsl:template>


</xsl:stylesheet>
