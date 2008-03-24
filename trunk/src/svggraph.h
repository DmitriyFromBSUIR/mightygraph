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
	public slots:
	void open();
	
	private:
	QDomDocument graphDom;
	int svgWidth, svgHeight;
	
};
#endif