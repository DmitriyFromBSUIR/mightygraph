#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QDomDocument>
class Transform {
	public:
	Transform ();
	Transform (QDomDocument src);
	void load (QDomDocument src);
	QByteArray toByteArray (QString xsl = "");
	QDomDocument toDomDocument (QString xsl = "");
	
	private:
	QDomDocument doc;

};
#endif
