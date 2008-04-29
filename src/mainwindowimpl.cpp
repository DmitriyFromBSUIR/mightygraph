/* mainwindowimpl.cpp
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
 * Samy REVERSAT <reversat AT gmail.com>
 */

#include <QtGui>
#include "mainwindowimpl.h"
#include "preferencesimpl.h"
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f)
	: QMainWindow(parent, f)
{
	setupUi(this);


	QToolBar *toolBar = new QToolBar("Fichier",this);
	toolBar->addAction (QIcon(":/toolbar/icons/document-new.png"), "Nouveau", graphImg, SLOT(newDoc()));
	toolBar->addAction (QIcon(":/toolbar/icons/document-open.png"), "Ouvrir", graphImg, SLOT(open()));
	toolBar->addAction (QIcon(":/toolbar/icons/document-save.png"), "Enregistrer", graphImg, SLOT(save()));
	toolBar->addAction (QIcon(":/toolbar/icons/image-x-genericL.png"), "Exporter", graphImg, SLOT(exportGraph()));
	toolBar->addAction (QIcon(":/toolbar/icons/imprimL.png"), "Imprimer", graphImg, SLOT(impression()));
	toolBar->addSeparator();
	toolBar->addAction (QIcon(":/toolbar/icons/edit-undoL.png"), "Annuler", graphImg, SLOT(save()));
	toolBar->addAction (QIcon(":/toolbar/icons/edit-redoL.png"), "Rétablir", graphImg, SLOT(save()));
	toolBar->addSeparator();
	toolBar->addAction (QIcon(":/toolbar/icons/zoom-outL.png"), "Zoom arrière", graphImg, SLOT(save()));
	toolBar->addAction (QIcon(":/toolbar/icons/zoom-best-fitL.png"), "Zoom optimal", graphImg, SLOT(save()));
	toolBar->addAction (QIcon(":/toolbar/icons/zoom-inL.png"), "Zoom avant", graphImg, SLOT(save()));
	toolBar->addSeparator();
	toolBar->addAction (QIcon(":/toolbar/icons/applications-graphicsL.png"), QString("Thème"), graphImg, SLOT(themesMenu()));
	toolBar->addAction (QIcon(":/toolbar/icons/document-propertiesL.png"), "Préférences", this, SLOT(preferences()));
	addToolBar(Qt::TopToolBarArea, toolBar);

	/* Menu principal */
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
	graphImg->resize(newSize);
}

void MainWindowImpl::quit() {
	exit(0);
}
//
