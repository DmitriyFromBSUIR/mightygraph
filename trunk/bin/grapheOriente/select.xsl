<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 Paul HUYNH <paulytech AT gmail.com>
	 Maxime VALIERE <maxime.valiere AT polytech.univ-montp2.fr>
	 Kevin JEAN <kevin.jean AT polytech.univ-montp2.fr>
	 Christophe PACALY <christophe.pacaly AT polytech.univ-montp2.fr>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="posh">184</xsl:param>
<xsl:param name="posv">165</xsl:param>

<xsl:template match="/">
	<selectedIds>
		<xsl:for-each select="//*[name() = 'rect']">
			<xsl:if test="$posh &gt;= @x and $posh &lt;= (@x+@width)">
				<xsl:if test="$posv &gt;= @y and $posv &lt;= (@y+@height)">
					<id><xsl:value-of select="substring(@id,6)" /></id>
				</xsl:if>
			</xsl:if>
		</xsl:for-each>
		<xsl:for-each select="//*[name() = 'line']">
			<xsl:if     test="(@x1 &gt;= @x2 and $posh &gt;= (@x2 -2) and $posh &lt;= (@x1 +2)) or (@x1 &lt; @x2 and $posh &lt;= (@x2 +2) and $posh &gt; (@x1 -2))">
				<xsl:if test="(@y1 &gt;= @y2 and $posv &gt;= (@y2 -2) and $posv &lt;= (@y1 +2)) or (@y1 &lt; @y2 and $posv &lt;= (@y2 +2) and $posv &gt; (@y1 -2))">
					<xsl:variable name="diff" select="(($posh -@x1)div($posv -@y1)) -((@x2 -@x1)div(@y2 -@y1))" />
					<xsl:if test="@y1=@y2 or $diff &lt; 0.20 and $diff &gt; -0.20">
						<id><xsl:value-of select="substring(@id,6)" /></id>
					</xsl:if>
				</xsl:if>
			</xsl:if>
		</xsl:for-each>
	</selectedIds>
</xsl:template>
</xsl:stylesheet>