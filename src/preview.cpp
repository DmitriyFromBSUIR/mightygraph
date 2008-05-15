/* preview.cpp - Apercu
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
#include <QtSvg/QSvgWidget>
#include "preview.h"
#include "transform.h"

Preview::Preview( QWidget * parent) : QSvgWidget() {
	setParent(parent);
	graphImg = parent;
	
	/* Position du clic */
	ex = 0; ey = 0;
}

void Preview::loadSvg (QByteArray svgGraph)
{
	this->svgGraph = svgGraph;
}

void Preview::updatePreviewArea()
{	QSettings settings;
	Transform *tr = new Transform;
	tr->setDoc(svgGraph);
	tr->loadXsl(settings.value("sys/templatesPath").toString()  + "/" + graphType + "/" + "preview.xsl");
	
	QRect visibleArea = graphImg->visibleRegion ().boundingRect ();

	tr->addParam("x", visibleArea.x() * svgSize.width() / graphImg->size().width());
	tr->addParam("y", visibleArea.y() * svgSize.height() / graphImg->size().height());
	tr->addParam("w", visibleArea.width() * svgSize.width() / graphImg->size().width());
	tr->addParam("h", visibleArea.height() * svgSize.height() / graphImg->size().height());

	load(tr->toByteArray());
	delete tr;
}

void Preview::setSvgSize(QSize s)
{
	svgSize = s;
}

void Preview::setGraphType(QString graphType)
{
	this->graphType = graphType;
}

void Preview::mousePressEvent(QMouseEvent *e)
{
	mouseMoveEvent(e);
}

void Preview::mouseMoveEvent(QMouseEvent *e)
{
	QRect visibleArea = graphImg->visibleRegion ().boundingRect ();
	ex = e->x() - 0.5 * (visibleArea.width() * size().width() / graphImg->size().width());
	ey= e->y() - 0.5 * (visibleArea.height() * size().height() / graphImg->size().height());
	int deltaX = - (ex * graphImg->size().width()) / size().width();
	int deltaY = - (ey * graphImg->size().height()) / size().height();
	graphImg->move(deltaX,deltaY);
	updatePreviewArea();
}

void Preview::toggleVisibility()
{
	if (isHidden())
	{
		show ();
	} else {
		hide();
	}
}

void Preview::showEvent ( QShowEvent * e)
{
	QSettings settings;
	
	/* Position de la fenetre */
	int posx = settings.value("app/previewPosX").toInt();
	int posy = settings.value("app/previewPosY").toInt();

	if (posx != 0 && posy != 0) move(posx, posy);
	
	/*TODO verifier la taille de l'ecran */
	e->accept();
}

void Preview::hideEvent (QHideEvent *e)
{
	QSettings settings;
	settings.setValue("app/previewPosX", pos().x());
	settings.setValue("app/previewPosY", pos().y());
	e->accept();
}