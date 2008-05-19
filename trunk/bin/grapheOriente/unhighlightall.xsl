<?xml version="1.0" encoding="UTF-8"?>
<!-- Paul HUYNH <paulytech AT gmail.com>
	 Maxime VALIERE <maxime.valiere AT polytech.univ-montp2.fr>
	 Kevin JEAN <kevin.jean AT polytech.univ-montp2.fr>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*[not(name()='highlighted')]"/>
	</xsl:copy>
</xsl:template>

</xsl:stylesheet>