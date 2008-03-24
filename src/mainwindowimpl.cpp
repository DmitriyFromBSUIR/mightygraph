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
