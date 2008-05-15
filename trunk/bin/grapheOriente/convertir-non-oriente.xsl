<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="theme">default.css</xsl:param>

<xsl:template match="/" priority="1">
	<xsl:processing-instruction name="xml-stylesheet">type="text/css" href="<xsl:value-of select="$theme" />"</xsl:processing-instruction>
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
					<xsl:variable name="sourceLongueur"><xsl:value-of select="string-length(//sommet[@id=concat($source, '')])*25" /></xsl:variable>
					<xsl:variable name="sourceLargeur"><xsl:value-of select="50" /></xsl:variable>

					<xsl:variable name="destPosH"><xsl:value-of select="//sommet[@id=concat($destination, '')]/@posh" /></xsl:variable>
					<xsl:variable name="destPosV"><xsl:value-of select="//sommet[@id=concat($destination, '')]/@posv" /></xsl:variable>
					<xsl:variable name="destLongueur"><xsl:value-of select="string-length(//sommet[@id=concat($destination, '')])*25" /></xsl:variable>
					<xsl:variable name="destLargeur"><xsl:value-of select="50" /></xsl:variable>
					
					<xsl:variable name="midX1"><xsl:value-of select="$destPosH + $destLongueur div 2" /></xsl:variable>
					<xsl:variable name="midY1"><xsl:value-of select="$destPosV + $destLargeur div 2" /></xsl:variable>
					<xsl:variable name="midX2"><xsl:value-of select="$sourcePosH + $sourceLongueur div 2" /></xsl:variable>
					<xsl:variable name="midY2"><xsl:value-of select="$sourcePosV + $sourceLargeur div 2" /></xsl:variable>

					<xsl:variable name="sourceDemiLargeur"><xsl:value-of select="$sourceLargeur div 2" /></xsl:variable>
					<xsl:variable name="sourceDemiLongueur"><xsl:value-of select="$sourceLongueur div 2" /></xsl:variable>
					<xsl:variable name="destDemiLargeur"><xsl:value-of select="$destLargeur div 2" /></xsl:variable>
					<xsl:variable name="destDemiLongueur"><xsl:value-of select="$destLongueur div 2" /></xsl:variable>
					
					<xsl:choose>
						<!-- X1 < X2 , Y1 < Y2 -->
						<xsl:when test="($midX1 - $midX2) &lt;= 0 and ($midY1 - $midY2) &lt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$destDemiLargeur * ($midX2 - $midX1) div ($midY2 - $midY1)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$destDemiLongueur div ($midX2 - $midX1) * ($midY2 - $midY1)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $destDemiLongueur">
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 + $destDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 + $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 + $thalesY" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 + $destDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>
						
						<!-- X1 > X2 , Y1 < Y2 -->
						<xsl:when test="($midX1 - $midX2) &gt;= 0 and ($midY1 - $midY2) &lt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$destDemiLargeur * ($midX1 - $midX2) div ($midY2 - $midY1)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$destDemiLongueur div ($midX1 - $midX2) * ($midY2 - $midY1)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $destDemiLongueur">
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 - $destDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 + $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 - $thalesY" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 + $destDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

						<!-- X1 > X2 , Y1 > Y2 -->
						<xsl:when test="($midX1 - $midX2) &gt;= 0 and ($midY1 - $midY2) &gt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$destDemiLargeur * ($midX1 - $midX2) div ($midY1 - $midY2)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$destDemiLongueur div ($midX1 - $midX2) * ($midY1 - $midY2)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $destDemiLongueur">
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 - $destDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 - $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 - $thalesY" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 - $destDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

						<!-- X1 < X2 , Y1 > Y2 -->
						<xsl:when test="($midX1 - $midX2) &lt;= 0 and ($midY1 - $midY2) &gt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$destDemiLargeur * ($midX2 - $midX1) div ($midY1 - $midY2)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$destDemiLongueur div ($midX2 - $midX1) * ($midY1 - $midY2)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $destDemiLongueur">
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 + $destDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 - $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x1"><xsl:value-of select="$midX1 + $thalesY" /></xsl:attribute>
									<xsl:attribute name="y1"><xsl:value-of select="$midY1 - $destDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

					</xsl:choose>
					
					
					
					
					
					<xsl:choose>
						<!-- X1 < X2 , Y1 < Y2 -->
						<xsl:when test="($midX2 - $midX1) &lt;= 0 and ($midY2 - $midY1) &lt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$sourceDemiLargeur * ($midX1 - $midX2) div ($midY1 - $midY2)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$sourceDemiLongueur div ($midX1 - $midX2) * ($midY1 - $midY2)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $sourceDemiLongueur">
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 + $sourceDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 + $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 + $thalesY" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 + $sourceDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>
						
						<!-- X1 > X2 , Y1 < Y2 -->
						<xsl:when test="($midX2 - $midX1) &gt;= 0 and ($midY2 - $midY1) &lt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$sourceDemiLargeur * ($midX2 - $midX1) div ($midY1 - $midY2)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$sourceDemiLongueur div ($midX2 - $midX1) * ($midY1 - $midY2)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $sourceDemiLongueur">
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 - $sourceDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 + $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 - $thalesY" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 + $sourceDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

						<!-- X1 > X2 , Y1 > Y2 -->
						<xsl:when test="($midX2 - $midX1) &gt;= 0 and ($midY2 - $midY1) &gt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$sourceDemiLargeur * ($midX2 - $midX1) div ($midY2 - $midY1)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$sourceDemiLongueur div ($midX2 - $midX1) * ($midY2 - $midY1)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $sourceDemiLongueur">
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 - $sourceDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 - $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 - $thalesY" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 - $sourceDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

						<!-- X1 < X2 , Y1 > Y2 -->
						<xsl:when test="($midX2 - $midX1) &lt;= 0 and ($midY2 - $midY1) &gt;= 0">
							<xsl:variable name="thalesY"><xsl:value-of select="$sourceDemiLargeur * ($midX1 - $midX2) div ($midY2 - $midY1)" /></xsl:variable>
							<xsl:variable name="thalesX"><xsl:value-of select="$sourceDemiLongueur div ($midX1 - $midX2) * ($midY2 - $midY1)" /></xsl:variable>
						
							<xsl:choose>
								<xsl:when test="$thalesY &gt; $sourceDemiLongueur">
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 + $sourceDemiLongueur" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 - $thalesX" /></xsl:attribute>
								</xsl:when>
								<xsl:otherwise>
									<xsl:attribute name="x2"><xsl:value-of select="$midX2 + $thalesY" /></xsl:attribute>
									<xsl:attribute name="y2"><xsl:value-of select="$midY2 - $sourceDemiLargeur" /></xsl:attribute>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:when>

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
						<!--<xsl:choose>
							<xsl:when test="string-length(.) &gt; 5">
							-->
								<xsl:value-of select="string-length(.)*25" />
							<!--
							</xsl:when>
							<xsl:otherwise>
								<xsl:value-of select="40" />
							</xsl:otherwise>
						</xsl:choose>-->
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
					<xsl:attribute name="x"><xsl:value-of select="@posh + 25" /></xsl:attribute>
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