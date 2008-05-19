<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 Paul HUYNH <paulytech AT gmail.com>
	 -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="id">0</xsl:param>

<xsl:template match="*|@*">
	<xsl:if test="not(@id = $id or @source = $id or @destination = $id)">
		<xsl:copy>
			<xsl:apply-templates select="text()|*|@*"/>
		</xsl:copy>
	</xsl:if>
</xsl:template>

</xsl:stylesheet>