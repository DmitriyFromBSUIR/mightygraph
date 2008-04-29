/* svggraph.h - Classe d'affichage du graphe
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
 * Samy REVERSAT <reversat AT gmail.com>
 */

#ifndef SVGGRAPH_H
#define SVGGRAPH_H
#include <QDomDocument>
#include <QtSvg/QSvgWidget>

class SvgGraph : public QSvgWidget
{
	Q_OBJECT
	public:
	SvgGraph( QWidget * parent = 0);
	QSize originalSvgSize();
	void setOriginalSvgSize();
	QByteArray toSvg();
	QDomDocument getGraphDom();

	signals:
	void action(QAction *);

	public slots:
	void open();
	void newDoc();
	void save();
	void saveAs();
	void exportGraph();
	void impression();
	void quit();
	void themesMenu();
	void setTheme (QAction *action);
	void xslAction (QAction *action);

	protected:
	QString path;
	bool saved;
	void popupMenu(QPoint pos);
	void select();
	int lastId ();
	void highlight(int id);
	void unhighlight(int id);
	void unhighlightAll();
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);

	private:
	int nbt; // Nombre de transformations
	QWidget *parent;
	QDomDocument graphDom;
	QDomDocument svgGraphDom;
	QString themePath;
	/* lastPosH,lastPosY : position de la souris lors du dernier clic */
	int svgWidth, svgHeight, lastPosH, lastPosV, selectedId;
	void loadFile (QString path);
	void update ();
};
#endif