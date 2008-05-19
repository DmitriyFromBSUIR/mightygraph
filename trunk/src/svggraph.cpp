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
 * Kevin JEAN <kevin.jean AT polytech.univ-montp2.fr>
 */
#include <QtGui>
#include <QFile>
#include <QDomDocument>
#include <QtSvg/QSvgWidget>
#include "svggraph.h"
#include "transform.h"
#include "preferencesimpl.h"
#include "preview.h"

#define MAX_HISTORY_SIZE 100 /* TODO A mettre dans preferences */
SvgGraph::SvgGraph( QWidget * parent) : QSvgWidget() {

	this->parent = parent;

	svgWidth = svgHeight = lastPosH = lastPosV = 0;
	selectedId = -1; saved = 1;

	history = new QByteArray [MAX_HISTORY_SIZE];
	
	QSettings settings;
	nbt = 0;

	editor = new QTextEdit (this);
	editor->setFrameStyle(0);
	editor->hide();
	
	/* Desactiver la barre de defilement */
	editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	/* Fenetre d'apercu */
	preview = new Preview(this);
	preview->setWindowFlags(Qt::Tool);
	preview->resize(size()/3);
	preview->show();
}

void SvgGraph::open()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, tr("Ouvrir..."), QString::null, tr("Graphes (*.xml)"));
	if (!path.isNull()) {
		this->path = path;
		loadFile(path);
	}
}

void SvgGraph::newDoc()
{
	if (!saved)
	{
		int saveDialogRes = QMessageBox::question(this, tr("Enregistrer"),
		("Souhaitez-vous enregistrer les modifications ?"), QMessageBox::Save,
		QMessageBox::Cancel, QMessageBox::Discard);
		if (saveDialogRes == QMessageBox::Cancel) return; /* Annuler */
		if (saveDialogRes == QMessageBox::Save) save();   /* Enregistrer */
	}
	
	
	/* Charger la liste de types disponibles */
	QStringList types;
	QSettings settings;
	QFile file(settings.value("sys/templatesPath").toString() + "/" + "types.xml");
	QDomDocument typesDom;
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!typesDom.setContent(&file)) {
		file.close();
		return;
	}
	file.close();
	
	QHash<QString, QString> typesHash;
	QDomNodeList typesNodes = typesDom.elementsByTagName("type");
	
	for (int i=0; i<typesNodes.count(); i++)
	{
		QString text, path;
		QDomNode textNode = typesNodes.at(i);
		text = textNode.toElement().attribute("text");
		path = textNode.toElement().attribute("path");
		typesHash.insert(text,path);
		types.append(text);
	}
	bool *ok;
	graphType = typesHash.value(QInputDialog::getItem(this, "MightyGraph", tr("Type :"), types, 0, false, ok));

	loadFile(settings.value("sys/templatesPath").toString() + "/" + graphType + "/default.xml");
	path = QString(); /* Reinitialiser le chemin d'acces */
}

void SvgGraph::save()
{
	if (this->path.isNull()) {
		QString path;
		path = QFileDialog::getSaveFileName(this, tr("Enregistrer sous..."), QString::null, tr("Graphes (*.xml)"));
		if (path.isNull()) return;
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

void SvgGraph::exportGraph()
{
	bool *ok; QString filter;
	QString format = QInputDialog::getItem(this, tr("Format"), tr("Veuillez sélectionner le format d'export :"),
						QStringList() << tr("Image SVG") << tr("PostScript") << tr("Document PDF"), 0, false, ok);
	QString path;
	
	if (format == tr("Document PDF"))
	{
		path = QFileDialog::getSaveFileName(this, tr("Exporter..."), QString::null, tr("Document PDF (*.pdf)"));
		if (path.isNull()) return; /* L'utilisateur a appuye sur Annuler -> ne rien faire */	
		
		QPrinter prn;
		//if (QPrintDialog(&prn, this).exec() != QDialog::Accepted) return;
		prn.setOutputFormat(QPrinter::PdfFormat);
		//QPageSetupDialog(&prn, this);
		prn.setOutputFileName(path);
		render(&prn);
		QDesktopServices::openUrl(QUrl::fromLocalFile(path));
	} else

	if (format == tr("PostScript"))
	{
		QString path;
		path = QFileDialog::getSaveFileName(this, tr("Exporter..."), QString::null, tr("PostScript (*.ps)"));
		if (path.isNull()) return; /* L'utilisateur a appuye sur Annuler -> ne rien faire */	
		
		QPrinter prn; prn.setOutputFormat(QPrinter::PostScriptFormat);
		prn.setOutputFileName(path);
		render(&prn);
		QDesktopServices::openUrl(QUrl::fromLocalFile(path));
	}
	
	if (format == tr("Image SVG"))
	{
		path = QFileDialog::getSaveFileName(this, tr("Exporter..."), QString::null, tr("Image SVG (*.svg)"));
		if (path.isNull()) return; /* L'utilisateur a appuye sur Annuler -> ne rien faire */	
		
		QFile exportFile(path);
		if (exportFile.open(QIODevice::WriteOnly)) {
			/* Exporte le grqphe sous forme XML avec une indentation de 2 tabulations */
			exportFile.write(svgGraphDom.toByteArray(2));
		}
		exportFile.close();
		
	}
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

/* Samy REVERSAT <reversat AT gmail.com> */
void SvgGraph::print()
{
	QPrinter Printer;
	QPrintDialog *dialog = new QPrintDialog(&Printer);
	if (dialog->exec() == QDialog::Accepted)
	{
		QPainter Painter;
		Painter.begin(&Printer);

		Painter.end();
	}
	return;
}

void SvgGraph::themesMenu()
{
	QMenu cssMenu(this);
	connect(&cssMenu, SIGNAL(triggered(QAction *)), this, SLOT(setTheme(QAction *)));
	
	
	
	/* Charger la liste des themes disponibles */
	QSettings settings;
	QFile file(settings.value("sys/templatesPath").toString() +  "/" + graphType + "/themes.xml");
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

	/* Charger le type du graphe */
	graphType = graphDom.elementsByTagName("graphe").at(0).toElement().attribute("type");

	/* Theme par defaut */
	QSettings settings;
	themePath = settings.value("sys/templatesPath").toString() + "/" + graphType + "/themes/default.css";

	update();
	zoomFactor = 1; /* Reinitialiser le zoom */
	setOriginalSvgSize();
	historyIndex = 0;
	
	history[historyIndex] = graphDom.toByteArray();

	/* Griser le bouton Annuler */
	hashToolbar["undo"]->setDisabled(true);
	hashToolbar["redo"]->setDisabled(true);
	hashToolbar["zoomInit"]->setDisabled(true);
	
}

Preview* SvgGraph::getPreview()
{
	return preview;
}

QSize SvgGraph::originalSvgSize() {
	return QSize(svgWidth, svgHeight);
}

void SvgGraph::setOriginalSvgSize() {
	QSize newSize (originalSvgSize());
	newSize.scale(parent->size(), Qt::KeepAspectRatio);
	resize(newSize * zoomFactor);
	
}


QByteArray SvgGraph::toSvg() {
	QSettings settings;
	Transform *tr = new Transform (); // <-- a deplacer en attribut de classe pour eviter de recharger tout a chaque fois
	QString xslpath("convertir.xsl");
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/" + xslpath);
	tr->addParam("theme","'" + themePath + "'");
	QByteArray res (tr->toByteArray());
	
	/*if (true) TODO Verifier si le post-traitement de l'image est actif
	{*/
		tr->setDoc(res);
		tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/" + "postSvg.xsl");
		res = tr->toByteArray();
	/*}*/
	
	nbt++; delete tr;
	return res;
}


QDomDocument SvgGraph::getGraphDom() {
	 return graphDom;
}

void SvgGraph::setToolbar(QHash<QString, QAction*> hashToolbar) {
	this->hashToolbar = hashToolbar;
}

void SvgGraph::popupMenu(QPoint pos)
{
	QMenu menu(this);
	connect(&menu, SIGNAL(triggered(QAction *)), this, SLOT(xslAction(QAction *)));
	
	/* Un element est selectionne */
	if (selectedId != -1) {
		/* TODO a modifier */
		QString idString; idString.setNum(selectedId);
		QString menuTitleString = tr("Element") + " " + idString;
		QAction *menuTitle = menu.addAction(menuTitleString);
		menuTitle->setDisabled(1); /* Griser le titre du menu */
		menu.addSeparator();
	}
	QString nbtString; nbtString.setNum(nbt);
	//menu.addAction(nbtString);
	/*menu.addAction("Ouvrir", this, SLOT(open()));
	menu.addSeparator();
	*/
	
	/* Calculer le nombre d'elements selectionnes */
	Transform *tr = new Transform;

	tr->setDoc(graphDom.toByteArray());
	QSettings settings;
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/counter.xsl");
	QDomDocument highlightedElements;
	highlightedElements.setContent(tr->toByteArray());

	tr->loadDoc(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/actions.xml");
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/actions.xsl");

	QDomNodeList actionNodes = highlightedElements.elementsByTagName("selected").at(0).childNodes ();

	/* Verifier si le type de tous les elements est identique */
	QString type = "multiple";
	if (actionNodes.count() > 0)
	{
		type = actionNodes.at(0).toElement().tagName();
		if (actionNodes.count() > 1)
		{
			for (int j=1; j<actionNodes.count(); j++)
			{
				if (actionNodes.at(j).toElement().tagName() != type)
				{
					type = "multiple";
				}
			}
		}
	}

	tr->addParam("counter", highlightedElements.elementsByTagName("selected").at(0).childNodes ().count());
	tr->addParam("type", "'" + type + "'");
	
	QDomDocument actions; actions.setContent(tr->toByteArray());
	delete tr;
	
	/* Charger la liste des actions disponibles */
	QDomNodeList actionsNodes = actions.elementsByTagName("action");
	
	for (int i=0; i<actionsNodes.count(); i++)
	{
		QString text, xsl, unary;
		QDomNode act = actionsNodes.at(i);
		text = act.toElement().attribute("text");
		xsl = act.toElement().attribute("path");
		unary = act.toElement().attribute("unary");

		QAction *action = menu.addAction(text);
		action->setData(unary + xsl);
	}
	
	/* Afficher le menu */
	menu.exec(pos);
}

void SvgGraph::select()
{
	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(svgGraphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/select.xsl");
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

int SvgGraph::lastId ()
{
	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/idlist.xsl");
	QByteArray idListXml(tr->toByteArray());
	QDomDocument idListDom; idListDom.setContent(idListXml);
	int id = idListDom.elementsByTagName("id").at(0).toElement().text().toInt();
	nbt++; delete tr;
	return id;
}


void SvgGraph::highlight (int id)
{
	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/highlight.xsl");
	tr->addParam("id", id);
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}

void SvgGraph::unhighlight (int id)
{
	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/unhighlight.xsl");
	tr->addParam("id", id);
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}

void SvgGraph::unhighlightAll ()
{
	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(graphDom.toByteArray());
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/unhighlightall.xsl");
	graphDom.setContent(tr->toByteArray());
	update();
	nbt++; delete tr;
}


void SvgGraph::mouseMoveEvent(QMouseEvent *e)
{
	/* Cacher l'editeur */
	if (!editor->isHidden())
	{
		editor->hide();
	}

	if (selectedId == -1) {
		e->accept(); return;
	}
	if (lastPosH != e->x() || lastPosV != e->y())
		{
			int diffX = (e->x() * originalSvgSize().width() / size().width()) - lastPosH;
			int diffY = (e->y() * originalSvgSize().height() / size().height()) - lastPosV;
			
			QSettings settings;
			Transform *tr = new Transform;
			tr->setDoc(graphDom.toByteArray());
			tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/move.xsl");
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
		
		/* L'utilisateur a termine la modification d'un champ */
		if (!editor->isHidden())
		{	QSettings settings;
			Transform *tr = new Transform;
			tr->setDoc(graphDom.toByteArray());
			tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/modify.xsl");
			tr->addParam("id", editId);
			tr->addParam("content", "'" + editor->toPlainText() + "'");
			graphDom.setContent(tr->toByteArray());
			update();

			delete tr;
			editor->hide();
		}
		
		e->accept(); return;
	}
	
	/* Autres boutons : ne rien faire */
	e->ignore(); return; 
}

void SvgGraph::mouseReleaseEvent(QMouseEvent *e) {

	if (graphDom.toByteArray() != history[historyIndex])
	{
		updateHistory();
	}
	e->accept();
}

void SvgGraph::mouseDoubleClickEvent(QMouseEvent *e)
{	QSettings settings;
	if (selectedId != -1)
	{
		editId = selectedId;
		Transform *tr = new Transform;
		tr->setDoc(svgGraphDom.toByteArray());
		tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/load.xsl");
		tr->addParam("id", selectedId);
		QDomDocument position; position.setContent(tr->toByteArray());
		int x = position.elementsByTagName("x").at(0).toElement().text().toInt();
		x = x * size().width() / originalSvgSize().width() + 2;
		int y = position.elementsByTagName("y").at(0).toElement().text().toInt();
		y = y * size().height() / originalSvgSize().height() + 2;
		int w = position.elementsByTagName("width").at(0).toElement().text().toInt();
		w = w * size().width() / originalSvgSize().width() - 4;
		int h = position.elementsByTagName("height").at(0).toElement().text().toInt();
		h = h * size().height() / originalSvgSize().height() - 4;
	
		QString content = position.elementsByTagName("content").at(0).toElement().text();
		
		delete tr;
		editor->setGeometry(x, y, w, h);
		editor->setText(content);
		editor->show();
	}
	e->accept();
}

void SvgGraph::update ()
{
	QByteArray svgGraph = this->toSvg();
	svgGraphDom.setContent(svgGraph);
	svgWidth = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("width").toInt();
	svgHeight = svgGraphDom.elementsByTagName("svg").at(0).toElement().attribute("height").toInt();
	load(svgGraph);

	preview->setSvgSize(originalSvgSize());
	preview->setGraphType(graphType);
	preview->loadSvg(svgGraphDom.toByteArray());
	preview->updatePreviewArea();
	

}

void SvgGraph::setTheme (QAction *action)
{	
	if (action->data().isNull()) return;
	QSettings settings;
	themePath = settings.value("sys/templatesPath").toString()  + "/" + graphType + "/themes/" + action->data().toString();
	update();
}

void SvgGraph::xslAction (QAction *action)
{	QSettings settings;
	/* Pas de transformation associee a l'action : ne rien faire */
	if (action->data().isNull()) return;

	QString data = action->data().toString();
	QString unary = data.left(1);
	QString path = data.right(data.length() - 1);

	if (unary == "0")
	{	QSettings settings;
		Transform *tr = new Transform;
		tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/" + path);
		tr->setDoc(graphDom.toByteArray());
		/* Action n-aire */
		tr->addParam("id", selectedId);
		tr->addParam("newId", lastId()+1);
		tr->addParam("posv", lastPosV);
		tr->addParam("posh", lastPosH);
		tr->addParam("value", "'XYZ'");
		graphDom.setContent(tr->toByteArray());
		delete tr;
	} else {
		/* Action unaire */
		Transform *tr2 = new Transform;
		tr2->setDoc(graphDom.toByteArray());
		tr2->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/counter.xsl");
		QDomDocument highlightedElements;
		highlightedElements.setContent(tr2->toByteArray());

		
		QDomNodeList unaryActions = highlightedElements.elementsByTagName("selected").at(0).childNodes ();
		for (int i=0; i<unaryActions.count(); i++)
		{
			Transform *tr = new Transform;
			tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/" + path);
			tr->setDoc(graphDom.toByteArray());
			int id = unaryActions.at(i).toElement().attributeNode("id").value().toInt();
			tr->addParam("id", id);
			tr->addParam("newId", lastId()+1);
			tr->addParam("posv", lastPosV);
			tr->addParam("posh", lastPosH);
			tr->addParam("value", "'XYZ'");
			graphDom.setContent(tr->toByteArray());
			delete tr;
		}
		delete tr2;
	}
	
	update();


	
	/* Deselectionner tous les elements selectionnes */
	//unhighlightAll();
	
	/* Signaler que le graphe a ete modifie */
	saved = 0;
	
	updateHistory();
}

void SvgGraph::updateHistory()
{
	if (historyLastIndex == MAX_HISTORY_SIZE - 1)
	{
		for (int i=1; i<MAX_HISTORY_SIZE; i++) history[i-1] = history[i];
		historyIndex--; historyLastIndex--;
	}
	
	/* Actualiser l'historique */
	historyIndex++;
	historyLastIndex++;
	if (historyIndex != historyLastIndex)
	{
		historyLastIndex = historyIndex;
	}
	history[historyIndex] = graphDom.toByteArray();
	hashToolbar["redo"]->setDisabled(true);
	hashToolbar["undo"]->setDisabled(false);
}

void SvgGraph::zoomLess ()
{
	hashToolbar["zoomMore"]->setDisabled(false);
	hashToolbar["zoomInit"]->setDisabled(false);
	if (zoomFactor < 0.1)
	{
		hashToolbar["zoomLess"]->setDisabled(true);
	} else {
		zoomFactor *= 0.9;
		setOriginalSvgSize();
	}
	update();
}

void SvgGraph::zoomMore ()
{
	hashToolbar["zoomLess"]->setDisabled(false);
	hashToolbar["zoomInit"]->setDisabled(false);
	if (zoomFactor > 20)
	{
		hashToolbar["zoomMore"]->setDisabled(true);
	} else {
		zoomFactor *= 1.1;
		setOriginalSvgSize();
	}
	update();
}

void SvgGraph::zoomInit ()
{
	hashToolbar["zoomInit"]->setDisabled(true);
	zoomFactor = 1;
	setOriginalSvgSize();
	move(0,0);
	update();
}

float SvgGraph::getZoomFactor ()
{
	return zoomFactor;
}

void SvgGraph::undo ()
{	historyIndex--;
	graphDom.setContent(history[historyIndex]);
	update();
	if (!historyIndex)
	{
		hashToolbar["undo"]->setDisabled(true);
	}
	hashToolbar["redo"]->setDisabled(false);
}

void SvgGraph::redo ()
{
	historyIndex++;
	graphDom.setContent(history[historyIndex]);
	update();
	if (historyIndex == historyLastIndex)
	{
		hashToolbar["redo"]->setDisabled(true);
	}
	hashToolbar["undo"]->setDisabled(false);
}