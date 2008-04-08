/* main.cpp
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
 */
 
#include <QtGui>
#include "mainwindowimpl.h"
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	//this->setAttribute(Qt::WA_MacBrushedMetal);
	connect( actionOuvrir, SIGNAL( triggered() ), graphImg, SLOT( open() ) );
	connect( actionQuitter, SIGNAL( triggered() ), this, SLOT( quit() ) );
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
