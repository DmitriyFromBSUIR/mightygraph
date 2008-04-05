/* transform.h - Classe qui effectue les transformations XSL
 *
 * This file is part of MightyGraph.
 * MightyGraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Foobar is distributed in the hope that it will be useful,
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
