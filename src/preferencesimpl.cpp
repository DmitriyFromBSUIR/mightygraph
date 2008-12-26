/* mainwindowimpl.cpp
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
 * Paul HUYNH <paulytech AT gmail.com>
 * Christophe PACALY <christophe.pacaly AT polytech.univ-montp2.fr>
 */
 
#include <QtGui>
#include "preferencesimpl.h"
#include "transform.h"
//
PreferencesImpl::PreferencesImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	connect( templatesPathButton, SIGNAL( clicked() ), this, SLOT( changeTemplatesPath() ) );
	connect( inkscapePathButton, SIGNAL( clicked() ), this, SLOT( changeInkscapePath() ) );
	connect( resetTransformCounterButton, SIGNAL( clicked() ), this, SLOT( resetTransformCounter() ) );
	connect( buttonBox, SIGNAL( accepted() ), this, SLOT (save()) );
	
	QSettings settings;
	templatesPathEdit->setText(settings.value("sys/templatesPath").toString());
	inkscapePathEdit->setText(settings.value("sys/inkscapePath").toString());
	
	/* Afficher le compteur de transformations XSL */
	QString transfCounterString; transfCounterString.setNum(Transform::transfCounter);
	transformCounter->setText(transfCounterString);
}

void PreferencesImpl::save()
{
	QSettings settings;
	
	settings.setValue("sys/templatesPath", templatesPathEdit->text());
	settings.setValue("sys/inkscapePath", inkscapePathEdit->text());
}


void PreferencesImpl::changeTemplatesPath()
{
	QString path;
	path = QFileDialog::getExistingDirectory(this, tr("Ouvrir..."), QString::null);
	if (!path.isNull()) {
		templatesPathEdit->setText(path);
	}
}

void PreferencesImpl::changeInkscapePath()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, tr("Ouvrir..."), QString::null);
	if (!path.isNull()) {
		inkscapePathEdit->setText(path);
	}
}

void PreferencesImpl::resetTransformCounter()
{
	Transform::transfCounter = 0;
	transformCounter->setText("0"); /* Afficher '0' */
}