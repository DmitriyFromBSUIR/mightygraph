#include "transform.h"
#include <QDomDocument>
#include <QFile>

Transform::Transform() { }

Transform::Transform(QDomDocument src) { load(src); }

void Transform::load(QDomDocument src) { doc = src; }

QByteArray Transform::toByteArray (QString xsl) {
	/* Ne rien faire si la source est vide */
	if (doc.isNull()) return 0;
	
	QByteArray dest, src = doc.toByteArray();
	
	/* Enregistrer le flux XML dans un fichier temporaire */
	QFile filesrc( "tmpsrc.xml" );
	if (filesrc.open(QIODevice::WriteOnly)) { filesrc.write(src); }
	filesrc.close();
	
	/* Effectuer la transformation */
	system("xsltproc " + xsl.toLatin1() + " tmpsrc.xml > tmpdest.xml");
	
	/* Charger le fichier genere */
	QFile filedest( "tmpdest.xml" );
	if (filedest.open(QIODevice::ReadOnly)) {
		dest = filedest.readAll();
	} else {
		return src;
	}
	filedest.close();

	/* Supprimer les fichiers temporaires */
	//remove(".tmpsvg.svg"); remove(".tmpxml.xml");	
	
	/* Retourner le flux XML transforme */
	return dest;
}

QDomDocument Transform::toDomDocument (QString xsl) {
	QDomDocument doc;
	doc.setContent(toByteArray(xsl));
	return doc;
}