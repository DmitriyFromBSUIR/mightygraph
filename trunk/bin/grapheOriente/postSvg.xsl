<?xml version="1.0" encoding="UTF-8"?>
<!-- Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
	 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Definition de la racine carree -->
<xsl:template name="sqrt">
  <!-- The number you want to find the square root of -->
  <xsl:param name="number" select="0" />  
  <!-- The current 'try'.  This is used internally. -->
  <xsl:param name="try" select="1" />
  <!-- The current iteration, checked against maxiter to limit loop count -->  
  <xsl:param name="iter" select="1" />
  <!-- Set this up to ensure against infinite loops -->
  <xsl:param name="maxiter" select="10" />

  <!-- This template was written by Nate Austin using Sir Isaac Newton's
       method of finding roots -->

  <xsl:choose>
    <xsl:when test="$try * $try = $number or $iter > $maxiter">
      <xsl:value-of select="$try"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="sqrt">
        <xsl:with-param name="number" select="$number"/>

        <xsl:with-param name="try" 
                        select="$try - (($try * $try - $number) div (2 * $try))"/>
        <xsl:with-param name="iter" select="$iter + 1"/>
        <xsl:with-param name="maxiter" select="$maxiter"/>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>
<!-- Fin definition racine carree -->


<xsl:template match="*|@*|processing-instruction()">
	<xsl:copy>
		<xsl:apply-templates select="text()|*|@*"/>
	</xsl:copy>
</xsl:template>

<xsl:template match="*[name() = 'line']">
	<xsl:copy>
		<xsl:apply-templates select="@*|node()"/>
	</xsl:copy>
	
	<xsl:variable name="diffX" select="(@x1 - @x2)" />
	<xsl:variable name="diffY" select="(@y1 - @y2)" />
	
	<xsl:variable name="h">
		<xsl:call-template name="sqrt">
			<xsl:with-param name="number" select="($diffX * $diffX) + ($diffY * $diffY)" />
		</xsl:call-template>
	</xsl:variable>
	
	<xsl:variable name="cosa" select="$diffX div $h" />
	<xsl:variable name="sina" select="$diffY div $h" />
	<path d="M20,15 L0,0 20,-15 "  class="unselectedArrow" transform="matrix({$cosa}, {$sina}, {-$sina}, {$cosa}, {@x2}, {@y2})"/>
	<!--
	<path d="M0,0 L20,15 20,-15 z"  style="fill:white;stroke:black;stroke-width:2" transform="matrix({$cosa}, {$sina}, {-$sina}, {$cosa}, {@x2}, {@y2})"/>
	-->
</xsl:template>

</xsl:stylesheet>
