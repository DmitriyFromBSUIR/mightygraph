#ifndef TRANSFORM_H
#define TRANSFORM_H
/*
 * @file transform.h
 * @brief Wrapper pour le moteur XSLT
 * @author Radim BADSI
 * @date 2008-05-15
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
 */
#include <QDomDocument>
#include <QStringList>
#include <libxslt/transform.h>
using namespace std;

/** @class Transform
 * @brief Wrapper pour le moteur XSLT
 */
class Transform : public QObject {
	Q_OBJECT
	public:

	/**
	 * @brief Constructeur
	 */
	Transform ();

	/**
	 * @brief Compteur de transformations (visible dans le dialogue Préférences)
	 */
	static int transfCounter;

	/**
	 * @brief Charge un document XML à partir du système de fichier
	 *
	 * @param docPath : chemin d'accès (relatif ou absolu) au fichier
	 */
	void loadDoc (QString docPath);
	
	/**
	 * @brief Charge une feuille XSL à partir du système de fichier
	 *
	 * @param docPath : chemin d'accès (relatif ou absolu) à la feuille
	 */
	void loadXsl (QString xslPath);
	
	/**
	 * @brief Charge un document XML à partir de la mémoire
	 *
	 * @param doc : document XML
	 */
	void setDoc (QByteArray doc);
	
	/**
	 * @brief Charge une feuille XSL à partir de la mémoire
	 *
	 * @param xsl : Feuille XSL
	 */
	void setXsl (QByteArray xsl);
	
	/**
	 * @brief Ajoute un paramètre à la transformation
	 *
	 * @param name : Nom du paramètre
	 * @param name : Valeur du paramètre
	 */
	void addParam (QString name, QString value);
	
	/**
	 * @brief Ajoute un paramètre à la transformation
	 *
	 * @param name : Nom du paramètre
	 * @param name : Valeur du paramètre
	 */
	void addParam (QString name, int value);
	
	/**
	 * @brief Effectue la transformation
	 *
	 * @return Document XML résultant
	 */
	QByteArray toByteArray ();

	private:
	
	xmlDocPtr doc;
	xsltStylesheetPtr xsl;
	QStringList paramList;
	

};
#endif
