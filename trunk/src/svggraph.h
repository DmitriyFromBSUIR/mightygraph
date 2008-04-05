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
	void xslAction (QAction *action);
	
	protected:
	void popupMenu(QPoint pos);
	void mousePressEvent(QMouseEvent *e);
	
	private:
	QWidget *parent;
	QDomDocument graphDom;
	/* lastPosH,lastPosY : position de la souris lors du dernier clic */
	int svgWidth, svgHeight, lastPosH, lastPosV;

	void update ();
};
#endif