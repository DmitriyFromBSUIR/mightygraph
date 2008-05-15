#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H

/**
 * @file mainwindowimpl.h
 * @brief Fenêtre principale
 * @author
 * @date 2008-05-14
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

#include <QMainWindow>
#include "ui_mainwindow.h"

/** @class MainWindowImpl
 * @brief Fenêtre principale
 */
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{

Q_OBJECT
public:
	/**
	 * @brief Constructeur
	 *
	 * @param parent : Parent de la fenêtre
	 * @param f : Paramètres d'affichage de la fenêtre
	 */
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );

public slots:
	/**
	 * @brief Affiche la fenêtre de préférences
	 */
	void preferences ();
protected:
	/**
	 * @brief Evénement de redimensionnement de la fenêtre
	 *
	 * @param event : Evénement 
	 */
	void resizeEvent ( QResizeEvent * event );

	/**
	 * @brief Evénement de déplacement de la molette de la souris
	 *
	 * @param event : Evénement 
	 */
	void wheelEvent(QWheelEvent *e);

	/**
	 * @brief Evénement d'affichage (fenêtre affichée)
	 *
	 * @param event : Evénement 
	 */
	void showEvent ( QShowEvent * e);
	
	/**
	 * @brief Evénement d'affichage (fenêtre cachée)
	 *
	 * @param event : Evénement 
	 */
	void hideEvent ( QHideEvent * e);
private slots:

	/**
	 * @brief Quitte l'application
	 */
	void quit();
};
#endif




