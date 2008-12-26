/**
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
#include "mainwindowimpl.h"
#include "preferencesimpl.h"


MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f)
	: QMainWindow(parent, f)
{
	
	setupUi(this);
	
	QHash<QString, QAction*> hashToolbar;
	
	QToolBar *toolBar = new QToolBar("Fichier",this);
	hashToolbar["nouveau"] = toolBar->addAction (QIcon(":/toolbar/icons/document-new.png"), tr("Nouveau"), graphImg, SLOT(newDoc()));
	hashToolbar["ouvrir"] = toolBar->addAction (QIcon(":/toolbar/icons/document-open.png"), tr("Ouvrir"), graphImg, SLOT(open()));
	hashToolbar["enregistrer"] = toolBar->addAction (QIcon(":/toolbar/icons/document-save.png"), tr("Enregistrer"), graphImg, SLOT(save()));
	hashToolbar["exporter"] = toolBar->addAction (QIcon(":/toolbar/icons/image-x-genericL.png"), tr("Exporter"), graphImg, SLOT(exportGraph()));
	hashToolbar["imprimer"] = toolBar->addAction (QIcon(":/toolbar/icons/document-printL.png"), tr("Imprimer"), graphImg, SLOT(print()));
	toolBar->addSeparator();
	hashToolbar["undo"] = toolBar->addAction (QIcon(":/toolbar/icons/edit-undoL.png"), tr("Annuler"), graphImg, SLOT(undo()));
	hashToolbar["redo"] = toolBar->addAction (QIcon(":/toolbar/icons/edit-redoL.png"), tr("Rétablir"), graphImg, SLOT(redo()));
	toolBar->addSeparator();
	hashToolbar["zoomLess"] = toolBar->addAction (QIcon(":/toolbar/icons/zoom-outL.png"), tr("Zoom arrière"), graphImg, SLOT(zoomLess()));
	hashToolbar["zoomInit"] = toolBar->addAction (QIcon(":/toolbar/icons/zoom-best-fitL.png"), tr("Zoom optimal"), graphImg, SLOT(zoomInit()));
	hashToolbar["zoomMore"] = toolBar->addAction (QIcon(":/toolbar/icons/zoom-inL.png"), tr("Zoom avant"), graphImg, SLOT(zoomMore()));
	toolBar->addSeparator();
	hashToolbar["themes"] = toolBar->addAction (QIcon(":/toolbar/icons/applications-graphicsL.png"), tr("Thème"), graphImg, SLOT(themesMenu()));
	hashToolbar["preferences"] = toolBar->addAction (QIcon(":/toolbar/icons/document-propertiesL.png"), tr("Préférences"), this, SLOT(preferences()));
	toolBar->addSeparator();
	hashToolbar["preview"] = toolBar->addAction (QIcon(":/toolbar/icons/system-searchL.png"), tr("Fenêtre d'aperçu"), graphImg->getPreview(), SLOT(toggleVisibility()));
	addToolBar(Qt::TopToolBarArea, toolBar);
	
	graphImg->setToolbar(hashToolbar);
	graphImg->getPreview()->hide();
	graphImg->newDoc();
	graphImg->getPreview()->show();

	connect( actionOuvrir, SIGNAL( triggered() ), graphImg, SLOT( open() ) );
	connect( actionEnregistrer, SIGNAL( triggered() ), graphImg, SLOT( save() ) );
	connect( actionEnregistrer_sous, SIGNAL( triggered() ), graphImg, SLOT( saveAs() ) );
	connect( actionQuitter, SIGNAL( triggered() ), this, SLOT( quit() ) );
}
void MainWindowImpl::preferences ()
{
	PreferencesImpl *prefWin = new PreferencesImpl;
	prefWin->show();
}

/* Events */
void MainWindowImpl::resizeEvent ( QResizeEvent * event )
{
	if (graphImg->getGraphDom().isNull()) return;

	QSize newSize (graphImg->originalSvgSize());
	/* On respecte le ratio hauteur/largeur de l'image */
	
	newSize.scale(event->size(), Qt::KeepAspectRatio);
	graphImg->resize(newSize * graphImg->getZoomFactor());
	graphImg->setOriginalSvgSize();
	graphImg->getPreview()->updatePreviewArea();
}

void MainWindowImpl::wheelEvent(QWheelEvent *e)
{
	if (e->delta() > 0)
	{
		graphImg->zoomMore();
	} else {
		graphImg->zoomLess();
	}
}

void MainWindowImpl::quit() {
	QSettings settings;

	graphImg->getPreview()->hide();
	exit(0);
}

void MainWindowImpl::showEvent ( QShowEvent * e)
{
	QSettings settings;
	
	/* Position de la fenetre */
	int posx = settings.value("app/windowPosX").toInt();
	int posy = settings.value("app/windowPosY").toInt();

	//if (posx != 0 && posy != 0) move(posx, posy);
	
	/*TODO verifier la taille de l'ecran */
	e->accept();
}

void MainWindowImpl::hideEvent (QHideEvent *e)
{
	QSettings settings;
	settings.setValue("app/windowPosX", pos().x());
	settings.setValue("app/windowPosY", pos().y());
	e->accept();
}
