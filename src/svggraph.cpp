/* svggraph.cpp - Classe d'affichage du graphe
 *
 * This file is part of MightyGraph.
 * MightyGraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Foobar is distributed in the hope that it will be useful,
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

#include <stdio.h>
#include <QtGui>
#include <QFile>
#include <QDomDocument>
#include <QtSvg/QSvgWidget>
#include "svggraph.h"
#include "transform.h"

SvgGraph::SvgGraph( QWidget * parent) : QSvgWidget() {
	this->parent = parent;
	svgWidth = svgHeight = lastPosH = lastPosV = 0;
}

/**
  * Affiche un dialogue d'ouverture de fichier puis affiche le graphe 
  * sélectionné dans la fenêtre principale
  */
void SvgGraph::open()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, "Ouvrir...", QString::null, "Graphes (*.xml)");
	QFile file(path);
	
	/* Charger le graphe */
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!graphDom.setContent(&file)) {
		file.close();
		return;
	}
	file.close();
	update();
}

/**
 * Renvoie la taille par défaut du graphe
 * @return la taille du graphe
 */
QSize SvgGraph::originalSvgSize() {
	return QSize(svgWidth, svgHeight);
}

/**
  * Modifie la taille du graphe à un multiple de sa taille par défaut
  */
void SvgGraph::setOriginalSvgSize() {
	QSize newSize (originalSvgSize());
	newSize.scale(size(), Qt::KeepAspectRatio);
	resize(newSize);
}

/**
  * Génère la représentation SVG du graphe
  * @return image SVG du graphe
  */
QByteArray SvgGraph::toSvg() {
	Transform *tr = new Transform ();
	QString xslpath("convertir.xsl");
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(xslpath);
	QByteArray res (tr->toByteArray());

	return res;
}

/**
  * Renvoie le graphe sous la forme DOM (Document Object Model)
  * @return graphe DOM
  */
QDomDocument SvgGraph::getGraphDom() {
	 return graphDom;
}

/**
  * Menu popup
  */
void SvgGraph::popupMenu(QPoint pos)
{
	QMenu menu(this);
	connect(&menu, SIGNAL(triggered(QAction *)), this, SLOT(xslAction(QAction *)));

	menu.addAction("Ouvrir", this, SLOT(open()));
	menu.addSeparator();
	
	/* Charger la liste des actions disponibles */
	QFile file("actions.xml");
	QDomDocument actions;
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!actions.setContent(&file)) {
		file.close();
		return;
	}
	file.close();
	
	QDomNodeList actionsNodes = actions.elementsByTagName("action");
	
	for (int i=0; i<actionsNodes.count(); i++)
	{
		QString text, xsl;
		QDomNode act = actionsNodes.at(i);
		text = act.toElement().attribute("text");
		xsl = act.toElement().attribute("path");
		QAction *action = menu.addAction(text);
		action->setData(xsl);
	}
	
	/* Afficher le menu */
	menu.exec(pos);
}

/**
  * Gestion de la souris
  */
void SvgGraph::mousePressEvent(QMouseEvent *e)
{
	/* Enregister la position lors du dernier clic (par rapport a l'image non agrandie) */
	lastPosH = e->x() * originalSvgSize().width() / size().width();
	lastPosV = e->y() * originalSvgSize().height() / size().height();
	if (e->button() == Qt::RightButton)
	{
		popupMenu(e->globalPos());
		e->accept(); return;
	} else {
		e->ignore(); return; 
	}
}

void SvgGraph::update ()
{
	QByteArray svgGraph = this->toSvg();
	QDomDocument svgGraphDom;
	svgGraphDom.setContent(svgGraph);
	svgWidth = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("width").toInt();
	svgHeight = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("height").toInt();
	
	load(svgGraph);
	setOriginalSvgSize();
}

void SvgGraph::xslAction (QAction *action)
{
	/* Pas de transformation associee a l'action : ne rien faire */
	if (action->data().isNull()) return;
	
	QDomDocument xslDom;
	
	/* Charger le fichier de transformation */
	QFile filexsl( action->data().toString() );
	if (filexsl.open(QIODevice::ReadOnly)) {
		xslDom.setContent(&filexsl);
	} else {
		return;
	}
	filexsl.close();

	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->setXsl(xslDom.toByteArray());
	tr->addParam("posv", lastPosV);
	tr->addParam("posh", lastPosH);
	tr->addParam("value", "'XYZ'");
	graphDom.setContent(tr->toByteArray());
	update();
}