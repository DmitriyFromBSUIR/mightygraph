#ifndef SVGGRAPH_H
#define SVGGRAPH_H
/**
 * @file svggraph.h
 * @brief Affichage du graphe
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
#include "preview.h"

/** @class SvgGraph
 * @brief Affichage du graphe
 */
class SvgGraph : public QSvgWidget
{
	Q_OBJECT
	public:
	/**
	 * @brief Constructeur
	 *
	 * @param parent : Fenêtre mère
	 */
	SvgGraph( QWidget * parent = 0);

	/**
	 * @return la taille SVG du graphe
	 */
	QSize originalSvgSize();
	
	/**
	 * @brief Redimensionne le graphe à sa taille SVG originale
	 */
	void setOriginalSvgSize();
	
	/**
	 * @brief Converti le graphe en SVG
	 *
	 * @return le code SVG du graphe
	 */
	QByteArray toSvg();
	
	/**
	 * @return l'arbre DOM du graphe
	 */
	QDomDocument getGraphDom();
	
	/**
	 * @param hashToolbar Référence de la barre d'outils de la fenêtre principale
	 */
	void setToolbar(QHash<QString, QAction*> hashToolbar);
	
	/**
	 * @brief Charge un fichier
	 *
	 * @param path : chemin d'accès vers le fichier
	 */
	void loadFile (QString path);
	
	/**
	 * @return une référence vers la fenêtre d'aperçu
	 */
	Preview* getPreview();

	public slots:
	/**
	 * @brief Ouvre le dialogue d'ouverture d'un fichier
	 */
	void open();
	
	/**
	 * @brief Ouvre un nouveau fichier
	 */
	void newDoc();
	
	/**
	 * @brief Ouvre le dialogue d'enregistrement d'un fichier
	 */
	void save();
	
	/**
	 * @brief Ouvre le dialogue Enregistrer sous...
	 */
	void saveAs();
	
	/**
	 * @brief Ouvre le dialogue Exporter...
	 */
	void exportGraph();
	
	/**
	 * @brief Ouvre le menu Thèmes
	 */
	void themesMenu();
	
	/**
	 * @brief Configure un thème
	 * @param action Action qui contient le chemin d'accès vers le thème
	 */
	void setTheme (QAction *action);
	
	/**
	 * @brief Effectue une action XSL
	 * @param action Action qui contient le chemin d'accès vers la feuille XSL
	 */
	void xslAction (QAction *action);
	
	/**
	 * @brief Réduire l'agrandissement du graphe
	 */
	void zoomLess ();
	
	/**
	 * @brief Augmente l'agrandissement du graphe
	 */
	void zoomMore ();
	
	/**
	 * @brief Optimise l'agrandissement du graphe
	 */
	void zoomInit ();
	
	/**
	 * @return le coefficient d'agrandissement du graphe
	 */
	float getZoomFactor ();
	
	/**
	 * @brief Annule la dernière action
	 */
	void undo ();
	
	/**
	 * @brief Rétabli la dernière action
	 */
	void redo ();
	
	protected:
	/**
	 * @brief Affiche le menu contextuel
	 * @param pos : coordonnées du point où le menu sera affiché (la position de la souris)
	 */
	void popupMenu(QPoint pos);
	
	/**
	 * @brief Actualise la liste des éléments sélectionnés
	 */
	void select();
	
	/**
	 * @return le numéro du dernier ID
	 */
	int lastId ();
	
	/**
	 * @brief Accentue un élément
	 * @param id : ID de l'élément à accentuer
	 */
	void highlight(int id);
	
	/**
	 * @brief Désaccentue un élément
	 * @param id : ID de l'élément à désaccentuer
	 */
	void unhighlight(int id);
	
	/**
	 * @brief Désaccentue tous les éléments
	 */
	void unhighlightAll();

	/**
	 * @brief Evénement de déplacement de la souris
	 *
	 * @param e : Evénement 
	 */
	void mouseMoveEvent(QMouseEvent *e);
	
	/**
	 * @brief Evénement d'appui sur un bouton
	 *
	 * @param e : Evénement 
	 */
	void mousePressEvent(QMouseEvent *e);
	
	/**
	 * @brief Evénement de relâchement d'un bouton
	 *
	 * @param e : Evénement 
	 */
	void mouseReleaseEvent(QMouseEvent *e);
	
	/**
	 * @brief Evénement de double-clic
	 *
	 * @param e : Evénement 
	 */
	void mouseDoubleClickEvent(QMouseEvent *e);

	
	private:
	Preview *preview;
	QGraphicsRectItem *visibleRect;
	QString path;
	bool saved;
	QTextEdit *editor;
	QByteArray *history;
	QHash<QString, QAction*> hashToolbar;
	int historyIndex;
	int historyLastIndex;
	int editId; // L'ID de l'element en cours de modification */
	int nbt; // Nombre de transformations
	float zoomFactor; /* Coefficient du zoom */
	QWidget *parent;
	QDomDocument graphDom;
	QDomDocument svgGraphDom;
	QString themePath;
	QString graphType;
	/* lastPosH,lastPosY : position de la souris lors du dernier clic */
	int svgWidth;
	int svgHeight;
	int lastPosH;
	int lastPosV;
	int selectedId;
	
	/**
	 * @brief Actualise l'historique
	 */
	void updateHistory();
	
	/**
	 * @brief Actualise l'affichage du graphe
	 */
	void update ();
};
#endif