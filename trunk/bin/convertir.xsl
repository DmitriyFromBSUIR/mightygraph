<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:ev="http://www.w3.org/2001/xml-events" version="1.1" baseProfile="full" x="0" y="0" width="500" height="500" id="graphe">
		<!-- Couche 0 - Liaisons -->
		<g id="liaisons">
			<xsl:for-each select="graphe/liaison">
				<line style="stroke:black;stroke-width:2">
					<xsl:variable name="source">
						<xsl:value-of select="@source" />
					</xsl:variable>
					<xsl:variable name="destination">
						<xsl:value-of select="@destination" />
					</xsl:variable>
					
					<xsl:attribute name="x1">
						<xsl:value-of select="//sommet[@id=concat($source, '')]/@posh+25" />
					</xsl:attribute>
					<xsl:attribute name="y1">
						<xsl:value-of select="//sommet[@id=concat($source, '')]/@posv+25" />
					</xsl:attribute>
					
					<xsl:attribute name="x2">
						<xsl:value-of select="//sommet[@id=concat($destination, '')]/@posh+25" />
					</xsl:attribute>
					<xsl:attribute name="y2">
						<xsl:value-of select="//sommet[@id=concat($destination, '')]/@posv+25" />
					</xsl:attribute>
				</line>
			</xsl:for-each>
		</g>
		
		<!-- Couche 1 - Rectangles -->
		<g id="sommets">
			<xsl:for-each select="graphe/sommet">
				<rect width="50" height="50" fill="white" style="stroke:black;stroke-width:2">
					<xsl:attribute name="x"><xsl:value-of select="@posh" /></xsl:attribute>
					<xsl:attribute name="y"><xsl:value-of select="@posv" /></xsl:attribute>
				</rect>
			</xsl:for-each>
		</g>
		
		<!-- Couche 2 - Texte -->
		<g id="texte">
			<xsl:for-each select="graphe/sommet">
				<text>
					<xsl:attribute name="x"><xsl:value-of select="@posh + 15" /></xsl:attribute>
					<xsl:attribute name="y"><xsl:value-of select="@posv + 30" /></xsl:attribute>
					<xsl:value-of select="." />
				</text>
			</xsl:for-each>
		</g>
	</svg>
</xsl:template>

</xsl:stylesheet>