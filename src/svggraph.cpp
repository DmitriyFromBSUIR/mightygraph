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
	QString posvSt; posvSt.setNum(lastPosV);
	QString poshSt; poshSt.setNum(lastPosH);
	
	QDomElement posh = xslDom.createElement("posh");
	posh.appendChild(xslDom.createTextNode(poshSt));
	QDomElement posv = xslDom.createElement("posv");
	posv.appendChild(xslDom.createTextNode(posvSt));
	
	xslDom.elementsByTagName("sommet").at(0).appendChild(posh);
	xslDom.elementsByTagName("sommet").at(0).appendChild(posv);
	QString deb(xslDom.elementsByTagName("posv").at(0).toElement().text());

	/* Enregistrer le flux XML dans un fichier temporaire */
	QFile fileNewXsl( "tmpxsl.xsl" );
	if (fileNewXsl.open(QIODevice::WriteOnly)) { fileNewXsl.write(xslDom.toByteArray()); }
	fileNewXsl.close();
	
	Transform *tr = new Transform (graphDom);
	
	graphDom = tr->toDomDocument("tmpxsl.xsl");
	update();
}