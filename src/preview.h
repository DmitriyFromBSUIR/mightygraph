#ifndef PREVIEW_H
#define PREVIEW_H

/**
 * @file preview.h
 * @brief Fenêtre d'aperçu
 * @author
 * @date 2008-05-14
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
 * Paul HUYNH <paulytech AT gmail.com>
 */

#include <QtGui>
#include <QDomDocument>
#include <QtSvg/QSvgWidget>

/** @class Preview
 * @brief Fenêtre d'aperçu
 */
class Preview : public QSvgWidget
{
	Q_OBJECT
	public:
	/**
	 * @brief Constructeur
	 *
	 * @param parent : parent de la fenêtre
	 */
	Preview( QWidget * parent = 0);
	
	/**
	 * @brief Charge une image
	 *
	 * @param svgGraph : code SVG de l'image à charger
	 */
	void loadSvg (QByteArray svgGraph);
	
	/**
	 * @brief Actualise la fenêtre
	 */
	void updatePreviewArea ();
	
	/**
	 * @brief Configure la taille de l'image originale
	 *
	 * @param s : taille de l'image originale
	 */
	void setSvgSize(QSize s);

	/**
	 * @param graphType : Type du graphe
	 */
	void setGraphType(QString graphType);
	
	protected:
	/**
	 * @brief Evénement d'appui sur un bouton
	 *
	 * @param e : Evénement 
	 */
	void mousePressEvent(QMouseEvent *e);
	
	/**
	 * @brief Evénement de déplacement de la souris
	 *
	 * @param e : Evénement 
	 */
	void mouseMoveEvent(QMouseEvent *e);
	
	/**
	 * @brief Evénement d'affichage (fenêtre affichée)
	 *
	 * @param e : Evénement 
	 */
	void showEvent ( QShowEvent * e);
	
	/**
	 * @brief Evénement d'affichage (fenêtre cachée)
	 *
	 * @param e : Evénement 
	 */
	void hideEvent ( QHideEvent * e);
	public slots:
	
	/**
	 * @brief Inverse la visibilité de la fenêtre
	 */
	void toggleVisibility ();


	private:
	QSize svgSize;
	QByteArray svgGraph;
	QString graphType;
	QWidget *graphImg;
	int ex;
	int ey;

};

#endif