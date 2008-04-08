<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="posh">184</xsl:param>
<xsl:param name="posv">165</xsl:param>

<xsl:template match="/">
	<selectedIds>
		<xsl:for-each select="//*">
			<xsl:if test="name() = 'rect'">
				<xsl:if test="$posh &gt;= @x and $posh &lt;= (@x+@width)">
					<xsl:if test="$posv &gt;= @y and $posv &lt;= (@y+@height)">
						<id><xsl:value-of select="substring(@id,6)" /></id>
					</xsl:if>
				</xsl:if>
			</xsl:if>
			<xsl:if test="name() = 'line'">
				<xsl:if test="($posh &gt;= @x1 and $posh &lt;= @x2)">
					<xsl:if test="$posv &gt;= @y1 and $posv &lt;= @y2">
						<xsl:variable name="diff" select="(($posh -@x1)div($posv -@y1)) -((@x2 -@x1)div(@y2 -@y1))" />
						<Xid><xsl:value-of select="substring(@id,6)" /></Xid>
						<diff><xsl:value-of select="$diff" /></diff>
						<xsl:if test="$diff &lt; 0.15 and $diff &gt; -0.15">
							<id><xsl:value-of select="substring(@id,6)" /></id>
						</xsl:if>
					</xsl:if>
				</xsl:if>
			</xsl:if>
		</xsl:for-each>
	</selectedIds>
</xsl:template>
</xsl:stylesheet>