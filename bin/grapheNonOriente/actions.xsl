<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="counter">1</xsl:param>
<xsl:param name="type">multiple</xsl:param>

<xsl:template match="*[name() = 'action']">
	<xsl:choose>
		<xsl:when test="(@min = 1 and @max = 1 and $counter &gt; 0 and (@type = $type or @type = 'multiple'))">
			<xsl:copy>
				<xsl:attribute name="unary">1</xsl:attribute>
				<xsl:apply-templates select="text()|*|@*"/>
			</xsl:copy>
		</xsl:when>
		<xsl:otherwise>
			<xsl:if test="($counter &gt;= @min and $counter &lt;= @max and (@type = $type or @type = 'multiple'))">
				<xsl:copy>
					<xsl:attribute name="unary">0</xsl:attribute>
					<xsl:apply-templates select="text()|*|@*"/>
				</xsl:copy>
			</xsl:if>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="*|@*">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

</xsl:stylesheet>
