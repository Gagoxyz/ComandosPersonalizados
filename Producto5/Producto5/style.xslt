<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">
<xsl:template match ="/">
<html>
<head>
<title>Información del Adaptador</title>
</head>
<body>
<h1 style="font-family: Arial; color: #1a5276; text-align: center; font-style: italic;">Producto 5 - Transformación de un archivo XML mediante una hoja de estilo XSLT.</h1>
<h2 style="font-family: Arial; color: #2e86c1; text-align: center;">Información del adaptador</h2>
<table border="1" style="width: 80%; margin: 0 auto; border-collapse: collapse; font-family: Arial;">
<tr style="background-color: #f8c471; text-align: left;">
<th>Elemento</th>
<th>Parámetro</th>
</tr>
<tr>
<td>Nombre</td>
<td><xsl:value-of select="adaptador/nombre" /></td>
</tr>
<tr>
<td>IP</td>
<td><xsl:value-of select="adaptador/ip" /></td>
</tr>
<tr>
<td>Máscara de red</td>
<td><xsl:value-of select="adaptador/mascara" /></td>
</tr>
<tr>
<td>Puerta de enlace</td>
<td><xsl:value-of select="adaptador/puerta" /></td>
</tr>
<tr>
<td>DNS primaria</td>
<td><xsl:value-of select="adaptador/dns" /></td>
</tr>
<tr>
<td>Media de respuesta</td>
<td><xsl:value-of select="adaptador/media" /></td>
</tr>
<tr>
<td>Cantidad de saltos</td>
<td><xsl:value-of select="adaptador/saltos" /></td>
</tr>
</table>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
