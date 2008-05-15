<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/" priority="1">
	<xsl:processing-instruction name="xml-stylesheet">type="text/css" href="default.css"</xsl:processing-instruction>
	<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:ev="http://www.w3.org/2001/xml-events" version="1.1" baseProfile="full" x="0" y="0" width="800" height="500" id="graphe">
		<!-- Couche 0 - Liaisons -->
		<g id="liaisons">
			<xsl:for-each select="graphe/liaison">
				<line>
					<xsl:variable name="source">
						<xsl:value-of select="@source" />
					</xsl:variable>
					<xsl:variable name="destination">
						<xsl:value-of select="@destination" />
					</xsl:variable>

					<xsl:choose>
						<xsl:when test="@highlighted = '1'">
							<xsl:attribute name="class">selected</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="class">unselected</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>

					<xsl:variable name="sourcePosH"><xsl:value-of select="//sommet[@id=concat($source, '')]/@posh" /></xsl:variable>
					<xsl:variable name="sourcePosV"><xsl:value-of select="//sommet[@id=concat($source, '')]/@posv" /></xsl:variable>
					<xsl:variable name="destPosH"><xsl:value-of select="//sommet[@id=concat($destination, '')]/@posh" /></xsl:variable>
					<xsl:variable name="destPosV"><xsl:value-of select="//sommet[@id=concat($destination, '')]/@posv" /></xsl:variable>


					<xsl:choose>
						<xsl:when test="$sourcePosV &gt; $destPosV">
							<xsl:variable name="x1">
								<xsl:value-of select="$sourcePosH+(string-length(//sommet[@id=concat($source, '')]) * 12 div 2) - (25 div ($sourcePosV -$destPosV) * ($sourcePosH -$destPosH))" />
							</xsl:variable>
							<xsl:choose>
								<xsl:when test="$x1 &gt;= ($sourcePosH+(string-length(//sommet[@id=concat($source, '')]) * 12))">
									<xsl:attribute name="x1"><xsl:value-of select="$sourcePosH +(string-length(//sommet[@id=concat($source, '')]) * 12)" /></xsl:attribute>
								</xsl:when>
								
								<xsl:when test="$x1 &gt;= $sourcePosH">
									<xsl:attribute name="x1"><xsl:value-of select="$x1" /></xsl:attribute>
								</xsl:when>
								
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$sourcePosH" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						
							<xsl:attribute name="y1">
								<xsl:value-of select="$sourcePosV" />
							</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:variable name="x1">
								<xsl:value-of select="$sourcePosH+(string-length(//sommet[@id=concat($source, '')]) * 12 div 2) + (25 div ($sourcePosV -$destPosV) * ($sourcePosH -$destPosH))" />
							</xsl:variable>
							<xsl:choose>
								<xsl:when test="$x1 &gt;= $sourcePosH">
									<xsl:attribute name="x1"><xsl:value-of select="$x1" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$sourcePosH" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
							
							<xsl:attribute name="y1">
								<xsl:value-of select="$sourcePosV +50" />
							</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					
					
					
					<xsl:choose>
						<xsl:when test="$sourcePosV &lt; $destPosV">
							<xsl:variable name="x2">
								<xsl:value-of select="$destPosH+(string-length(//sommet[@id=concat($destination, '')]) * 12 div 2) - (25 div ($sourcePosV -$destPosV) * ($sourcePosH -$destPosH))" />
							</xsl:variable>
							<xsl:choose>
								<xsl:when test="$x2 &gt;= $destPosH">
									<xsl:attribute name="x2"><xsl:value-of select="$x2" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$destPosH" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
							<xsl:attribute name="y2">
								<xsl:value-of select="$destPosV" />
							</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:variable name="x2">
								<xsl:value-of select="$destPosH+(string-length(//sommet[@id=concat($destination, '')]) * 12 div 2) + (25 div ($sourcePosV -$destPosV) * ($sourcePosH -$destPosH))" />
							</xsl:variable>
							<xsl:choose>
								<xsl:when test="$x2 &gt;= ($destPosH+(string-length(//sommet[@id=concat($destination, '')]) * 12))">
									<xsl:attribute name="x2"><xsl:value-of select="$destPosH +(string-length(//sommet[@id=concat($destination, '')]) * 12)" /></xsl:attribute>
								</xsl:when>
								
								<xsl:when test="$x2 &gt;= $destPosH">
									<xsl:attribute name="x2"><xsl:value-of select="$x2" /></xsl:attribute>
								</xsl:when>
								
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$destPosH" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
							
							<xsl:attribute name="y2">
								<xsl:value-of select="$destPosV +50" />
							</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					
					
					
					
					<xsl:attribute name="id">
						<xsl:value-of select="concat('line_', @id)" />
					</xsl:attribute>
				</line>
			</xsl:for-each>
		</g>
		
		<!-- Couche 1 - Rectangles + texte -->
		<g id="sommets">
			<xsl:for-each select="graphe/sommet">
				<rect height="50">
					<!-- Largeur du cadre -->
					<xsl:attribute name="width">
						<xsl:choose>
							<xsl:when test="string-length(.) &gt; 5">
								<xsl:value-of select="string-length(.)*12" />
							</xsl:when>
							<xsl:otherwise>
								<xsl:value-of select="40" />
							</xsl:otherwise>
						</xsl:choose>
					</xsl:attribute>
					
					<!-- Hauteur du cadre -->
					<!--<xsl:attribute name="height">
						<xsl:value-of select="(string-length(.) -string-length(translate(.,'&#xA;','')) +1) * 50" />
					</xsl:attribute>-->
					
					
					<xsl:choose>
						<xsl:when test="@highlighted = '1'">
							<xsl:attribute name="class">selected</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="class">unselected</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:attribute name="x"><xsl:value-of select="@posh" /></xsl:attribute>
					<xsl:attribute name="y"><xsl:value-of select="@posv" /></xsl:attribute>
					<xsl:attribute name="id">
						<xsl:value-of select="concat('rect_', @id)" />
					</xsl:attribute>
				</rect>
				<text>
					<xsl:choose>
						<xsl:when test="@highlighted = '1'">
							<xsl:attribute name="class">selectedText</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="class">unselectedText</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:attribute name="x"><xsl:value-of select="@posh + 15" /></xsl:attribute>
					<xsl:attribute name="y"><xsl:value-of select="@posv + 30" /></xsl:attribute>
					<xsl:value-of select="." />
				</text>
			</xsl:for-each>
		</g>
	</svg>
</xsl:template>
<xsl:template match="/" priority="0">
	<xsl:copy>
		<test/>
		<xsl:apply-templates select="*|@*|node()"/>
	</xsl:copy>
</xsl:template>
</xsl:stylesheet>