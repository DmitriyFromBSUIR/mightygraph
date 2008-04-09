/* transform.cpp - Classe qui effectue les transformations XSL
 *
 * This file is part of MightyGraph.
 * MightyGraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * MightyGraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with MightyGraph.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Credits :
 *
 * Radim BADSI <radim.badsi AT polytech.univ-montp2.fr>
 */

#include "transform.h"
#include <QDomDocument>
#include <QFile>
#include <libxslt/transform.h>

Transform::Transform() { }

void Transform::loadDoc (QString docPath) {
	/* Charger le document */
	QFile docFile(docPath);
	if (docFile.open(QIODevice::ReadOnly)) {
		doc = docFile.readAll();
	}
	docFile.close();
}

void Transform::loadXsl (QString xslPath) {
	/* Charger la transformation */
	QFile xslFile(xslPath);
	if (xslFile.open(QIODevice::ReadOnly)) {
		xsl = xslFile.readAll();
	}
	xslFile.close();
}

void Transform::setDoc (QByteArray doc) {
	 this->doc = doc;
}

void Transform::setXsl (QByteArray xsl) {
	 this->xsl = xsl;
}

void Transform::addParam (QString name, QString value) {
	paramList << name << value;
}

void Transform::addParam (QString name, int value) {
	QString valueString;
	valueString.setNum(value);
	addParam(name, valueString);
}

QByteArray Transform::toByteArray () {
	/* Ne rien faire si la source est vide */
	if (doc.isNull()) return QByteArray("");

	/* Initialiser libxml & libxslt */
	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	/* Charger la feuille de style XSL dans libXml (on ne peut pas passer directement par le type Xml de Qt) 
	 * On s'assure que la feuille ne comporte aucun caractere autre que Ascii (les autres caracteres tels
	 * que les caracteres internationaux ont une traduction Ascii en XML...)
	 */
	xmlDocPtr xslPtr = xmlParseMemory (QString(xsl).toAscii(), strlen(QString(xsl).toAscii()) * sizeof(char));
	/* Charger la feuille dans libXslt */
	xsltStylesheetPtr stylesheet = xsltParseStylesheetDoc(xslPtr);
	xmlFree(xslPtr);
	
	/* Charger le document a transformer dans libXml */
	xmlDocPtr docPtr = xmlParseMemory (QString(doc).toAscii(), strlen(QString(doc).toAscii()) * sizeof(char));
	
	/* Charger les parametres de la transformations */
	
	/* Determiner la taille de la liste avec les parametres de la transformation */
	int paramListSize = 1;
	if (paramList.size() != 0) {
		paramListSize += paramList.size();
	}
	char *paramListChar[paramListSize];

	for (int i=0; i<paramList.size(); i++) {
		char *param = new char[ paramList.at(i).size()+1 ]; 
		strcpy(param , paramList.at(i).toStdString().c_str());
		paramListChar[i] = param;
		
	}

	/* xsltApplyStylesheet attend une liste de parametres terminee par NULL */
	paramListChar[paramListSize - 1] = NULL;
	
	/* Transformer le document selon la feuille de style chargee precedemment */
	xmlDocPtr resPtr = xsltApplyStylesheet(stylesheet, docPtr, (const char **)&paramListChar);
	xmlFree(docPtr);
	
	/* Vider la liste temporaire (*char) des parametres */
	for (int i=0; i<paramList.size(); i++) {
		delete[] paramListChar[i];
	}
	xmlChar* outXml; int outLen;
	
	/* Recuperer le document transforme sous la forme d'un char* */
	xmlDocDumpMemory(resPtr, &outXml, &outLen);
	xmlFree(resPtr);
	//qDebug((char*)outXml);
	return QByteArray((char*) outXml);

}