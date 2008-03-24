#include <stdio.h>
#include <QtGui>
#include <QFile>
#include <QDomDocument>
#include <QtSvg/QSvgWidget>
#include "svggraph.h"
#include "transform.h"

SvgGraph::SvgGraph( QWidget * parent) : QSvgWidget() {
	
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
	
	QByteArray svgGraph = this->toSvg();
	QDomDocument svgGraphDom;
	svgGraphDom.setContent(svgGraph);
	svgWidth = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("width").toInt();
	svgHeight = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("height").toInt();
	
	load(svgGraph);
	setOriginalSvgSize();
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
	Transform *tr = new Transform (graphDom);
	return tr->toByteArray();
}

/**
  * Renvoie le graphe sous la forme DOM (Document Object Model)
  * @return graphe DOM
  */
QDomDocument SvgGraph::getGraphDom() {
	 return graphDom;
}