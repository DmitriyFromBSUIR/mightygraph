#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QDomDocument>
using namespace std;
class Transform {
	public:
	Transform ();

	void loadDoc (QString docPath);
	void loadXsl (QString xslPath);
	void setDoc (QByteArray doc);
	void setXsl (QByteArray xsl);
	QByteArray toByteArray ();
	QByteArray toByteArray2 ();
	private:
	QByteArray doc;
	QByteArray xsl;

};
#endif
