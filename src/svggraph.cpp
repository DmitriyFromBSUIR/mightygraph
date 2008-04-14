/* svggraph.cpp - Classe d'affichage du graphe
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
#include <QFile>
#include <QDomDocument>
#include <QtSvg/QSvgWidget>
#include "svggraph.h"
#include "transform.h"
#include "preferencesimpl.h"

SvgGraph::SvgGraph( QWidget * parent) : QSvgWidget() {
	this->parent = parent;
	svgWidth = svgHeight = lastPosH = lastPosV = 0;
	selectedId = -1; saved = 1;
	nbt = 0; themePath = "default.css";
	loadFile("default.xml");
}

/**
  * Affiche un dialogue d'ouverture de fichier puis affiche le graphe 
  * s√©lectionn√© dans la fen√™tre principale
  */
void SvgGraph::open()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, "Ouvrir...", QString::null, "Graphes (*.xml)");
	if (!path.isNull()) {
		this->path = path;
		loadFile(path);
	}
		PreferencesImpl prefWin;
	prefWin.show();
}

void SvgGraph::newDoc()
{
	if (!saved)
	{
		int saveDialogRes = QMessageBox::question(this, "Enregistrer",
		"Souhaitez-vous enregistrer les modifications ?", QMessageBox::Save,
		QMessageBox::Cancel, QMessageBox::Discard);
		if (saveDialogRes == QMessageBox::Cancel) return; /* Annuler */
		if (saveDialogRes == QMessageBox::Save) save();   /* Enregistrer */
	}
	loadFile("default.xml");
	path = QString(); /* Reinitialiser le chemin d'acces*/
}

void SvgGraph::save()
{
	if (this->path.isNull()) {
		QString path;
		path = QFileDialog::getSaveFileName(this, "Enregistrer sous...", QString::null, "Graphes (*.xml)");
		if (path.isNull()) return; /* L'utilisateur a appuye sur Annuler -> ne rien faire */
		this->path = path;
	}
	/* Enregistrer le fichier XML */
	QFile filesrc(path);
	if (filesrc.open(QIODevice::WriteOnly)) {
		filesrc.write(graphDom.toByteArray());
		saved = true; /* Le fichier vient d'etre enregistre */
	}
	filesrc.close();
}

void SvgGraph::saveAs()
{
	QString oldPath = path; /* Sauvegarder l'ancien chemin */
	path = QString(); /* Mettre a Null le chemin d'acces (provoquera l'ouverture du dialogue d'enregistrement) */
	save();
	if (path.isNull()) path = oldPath; /* L'utilisateur a appuye sur Annuler, restaurer l'ancien chemin */
}

void SvgGraph::themesMenu()
{
	QMenu cssMenu(this);
	connect(&cssMenu, SIGNAL(triggered(QAction *)), this, SLOT(setTheme(QAction *)));
	
	/* Charger la liste des themes disponibles */
	QFile file("themes.xml");
	QDomDocument themes;
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!themes.setContent(&file)) {
		file.close();
		return;
	}
	file.close();
	
	QDomNodeList themesNodes = themes.elementsByTagName("theme");
	
	for (int i=0; i<themesNodes.count(); i++)
	{
		QString text, path;
		QDomNode thm = themesNodes.at(i);
		text = thm.toElement().attribute("text");
		path = thm.toElement().attribute("path");
		QAction *action = cssMenu.addAction(text);
		action->setData(path);
	}
	
	/* Afficher le menu */
	cssMenu.exec(QCursor::pos ());
}

void SvgGraph::loadFile(QString path)
{
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
 * Renvoie la taille par d√©faut du graphe
 * @return la taille du graphe
 */
QSize SvgGraph::originalSvgSize() {
	return QSize(svgWidth, svgHeight);
}

/**
  * Modifie la taille du graphe √  un multiple de sa taille par d√©faut
  */
void SvgGraph::setOriginalSvgSize() {
	QSize newSize (originalSvgSize());
	newSize.scale(parent->size(), Qt::KeepAspectRatio);
	resize(newSize);
}

/**
  * G√©n√®re la repr√©sentation SVG du graphe
  * @return image SVG du graphe
  */
QByteArray SvgGraph::toSvg() {
	Transform *tr = new Transform (); // <-- a deplacer en attribut de classe pour eviter de recharger tout a chaque fois
	QString xslpath("convertir.xsl");
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(xslpath);
	tr->addParam("theme","'" + themePath + "'");
	QByteArray res (tr->toByteArray());
	nbt++; delete tr;
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
  * Affiche le menu contextuel
  * @param pos Position o˘ le menu doit Ítre affichÈ
  */
void SvgGraph::popupMenu(QPoint pos)
{
	QMenu menu(this);
	connect(&menu, SIGNAL(triggered(QAction *)), this, SLOT(xslAction(QAction *)));
	
	/* Un element est selectionne */
	if (selectedId != -1) {
		/* TODO a modifier */
		QString idString; idString.setNum(selectedId);
		QString menuTitleString = "Element " + idString;
		QAction *menuTitle = menu.addAction(menuTitleString);
		menuTitle->setDisabled(1); /* Griser le titre du menu */
		menu.addSeparator();
	}
	QString nbtString; nbtString.setNum(nbt);
	//menu.addAction(nbtString);
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
  * Recalcule la liste des ÈlÈments sÈlectionnÈs
  */
void SvgGraph::select()
{
	Transform *tr = new Transform;
	tr->setDoc(svgGraphDom.toByteArray());
	tr->loadXsl("select.xsl");
	tr->addParam("posv", lastPosV);
	tr->addParam("posh", lastPosH);
	QByteArray idXml(tr->toByteArray());
	QDomDocument idDom; idDom.setContent(idXml);

	if (idDom.elementsByTagName("id").count() > 0)
	{
		selectedId = idDom.elementsByTagName("id").at(0).toElement().text().toInt();
	} else {
		selectedId = -1;
	}
	nbt++; delete tr;
}
/**
  * Retourne l'ID du dernier ÈlÈment
  * @return ID du dernier ÈlÈment
  */
int SvgGraph::lastId ()
{
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl("idlist.xsl");
	QByteArray idListXml(tr->toByteArray());
	QDomDocument idListDom; idListDom.setContent(idListXml);
	int id = idListDom.elementsByTagName("id").at(0).toElement().text().toInt();
	nbt++; delete tr;
	return id;
}

/**
  * SÈlectionne un ÈlÈment
  * @param id L'id de l'ÈlÈment
  * @see unhighlight()
  */
void SvgGraph::highlight (int id)
{
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl("highlight.xsl");
	tr->addParam("id", id);
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}

/**
  * DÈselectionne un ÈlÈment
  * @param id L'id de l'ÈlÈment
  * @see highlight()
  */
void SvgGraph::unhighlight (int id)
{
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl("unhighlight.xsl");
	tr->addParam("id", id);
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}

/**
  * DÈselectionne tous les ÈlÈments
  * @see unhighlight() highlight()
  */
void SvgGraph::unhighlightAll ()
{
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl("unhighlightall.xsl");
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}

/**
  * EvÈnement de gestion du mouvement de la souris
  * Cet ÈvÈnement correspond ‡ un mouvent de la souris.
  * Il incorpore notamment la gestion du dÈplacement
  * de la souris.
  * @param e EvÈnement
  */
void SvgGraph::mouseMoveEvent(QMouseEvent *e)
{
	if (selectedId == -1) {
		e->accept(); return;
	}
	if (lastPosH != e->x() || lastPosV != e->y())
		{
			int diffX = (e->x() * originalSvgSize().width() / size().width()) - lastPosH;
			int diffY = (e->y() * originalSvgSize().height() / size().height()) - lastPosV;
			
			Transform *tr = new Transform;
			tr->setDoc(graphDom.toByteArray());
			tr->loadXsl("move.xsl");
			tr->addParam("diffx", diffX);
			tr->addParam("diffy", diffY);
			graphDom.setContent(tr->toByteArray());
			update();
			nbt++; delete tr;
		}
	lastPosH = e->x() * originalSvgSize().width() / size().width();
	lastPosV = e->y() * originalSvgSize().height() / size().height();
	
	/* Signaler que le graphe a ete modifie */
	saved = 0;
	
	e->accept(); return;
}

/**
  * EvÈnement de gestion des boutons de la souris
  * Cet ÈvÈnement correspond ‡ un appui sur un bouton de la souris.
  * Il incorpore notamment la gestion du menu contextuel.
  * @param e EvÈnement
  */
void SvgGraph::mousePressEvent(QMouseEvent *e)
{
	/* Enregister la position lors du dernier clic (par rapport a l'image non agrandie) */
	lastPosH = e->x() * originalSvgSize().width() / size().width();
	lastPosV = e->y() * originalSvgSize().height() / size().height();
	select();
	/* Bouton droit : invoquer le menu contextuel */
	if (e->button() == Qt::RightButton)
	{
		if (selectedId != -1) {
			//unhighlightAll();
			highlight(selectedId); /* Surbriller l'element */	
		}
		popupMenu(e->globalPos());
		e->accept(); return;
	}
	
	/* Bouton gauche : selectionner l'element */
	if (e->button() == Qt::LeftButton)
	{
		if (!(e->modifiers() & Qt::ShiftModifier)) unhighlightAll();
		if (selectedId != -1) {
			highlight(selectedId);
		}

		e->accept(); return;
	}
	
	/* Autres boutons : ne rien faire */
	e->ignore(); return; 
}

void SvgGraph::update ()
{
	QByteArray svgGraph = this->toSvg();
	svgGraphDom.setContent(svgGraph);
	svgWidth = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("width").toInt();
	svgHeight = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("height").toInt();
	
	load(svgGraph);
}

void SvgGraph::setTheme (QAction *action)
{	
	if (action->data().isNull()) return;
	themePath = action->data().toString();
	update();
}

void SvgGraph::xslAction (QAction *action)
{	
	/* Pas de transformation associee a l'action : ne rien faire */
	if (action->data().isNull()) return;

	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(action->data().toString());
	tr->addParam("id", selectedId);
	tr->addParam("newId", lastId()+1);
	tr->addParam("posv", lastPosV);
	tr->addParam("posh", lastPosH);
	tr->addParam("value", "'XYZ'");
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
	
	/* Deselectionner tous les elements selectionnes */
	unhighlightAll();
	
	/* Signaler que le graphe a ete modifie */
	saved = 0;
}