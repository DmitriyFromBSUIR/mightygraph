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
	
	/* Transformer le document selon la feuille de style chargee precedemment */
	xmlDocPtr resPtr = xsltApplyStylesheet(stylesheet, docPtr, NULL);
	xmlFree(docPtr);
	
	xmlChar* outXml; int outLen;
	
	/* Recuperer le document transforme sous la forme d'un char* */
	xmlDocDumpMemory(resPtr, &outXml, &outLen);
	xmlFree(resPtr);
	
	return QByteArray((char*) outXml);

}