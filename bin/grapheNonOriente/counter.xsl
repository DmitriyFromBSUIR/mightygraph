<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>

<xsl:template match="/">
	<selected>
		<xsl:for-each select="//*[@highlighted = '1']">
			<xsl:copy>
				<xsl:attribute name="id">
					<xsl:value-of select="@id" />
				</xsl:attribute>
				
				<xsl:apply-templates select="*"/>
			</xsl:copy>
		</xsl:for-each>
	</selected>
</xsl:template>


</xsl:stylesheet>
