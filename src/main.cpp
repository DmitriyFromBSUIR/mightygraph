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

#include <QApplication>
#include "mainwindowimpl.h"
#include "transform.h"
//
int main(int argc, char ** argv)
{
	QApplication app( argc, argv );

	/* Paramètres de stockage des préférences */
	QCoreApplication::setOrganizationName("MightyGraph");
	QCoreApplication::setOrganizationDomain("mightygraph.googlecode.com");
	QCoreApplication::setApplicationName("MightyGraph");

	/* Installer le support de la localisation */
	QTranslator translator;
	
	/* Langue par defaut = langue du système */
	/*QString locale = QLocale::system().name();
	translator.load("mightygraph_" + locale);
	qDebug("System language : " + locale.toLatin1());
	app.installTranslator(&translator);*/
	
	translator.load("mightygraph_fr_FR");
	app.installTranslator(&translator);

	/* Initialiser le compteur de transformations XSL */
	Transform::transfCounter = 0;

	MainWindowImpl win;
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &win, SLOT( quit() ) );
	return app.exec();
}
