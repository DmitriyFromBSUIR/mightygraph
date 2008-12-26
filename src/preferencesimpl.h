#ifndef PreferencesIMPL_H
#define PreferencesIMPL_H
/*
 * @file preferencesimpl.h
 * @brief Fenêtre de préférences
 * @author
 * @date 2008-05-15
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
 */
#include <QDialog>
#include "ui_preferences.h"

/** @class PreferencesImpl
 * @brief Fenêtre de préférences
 */
class PreferencesImpl : public QDialog, public Ui::preferencesDialog
{
Q_OBJECT
public:
	/**
	 * @brief Constructeur
	 *
	 * @param parent : Parent de la fenêtre
	 * @param f : Paramètres d'affichage de la fenêtre
	 */
	PreferencesImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
protected:

private slots:
	/**
	 * @brief Demande à l'utilisateur de choisir un nouveau chemin d'accès aux maquettes
	 */
	void changeTemplatesPath();
	
	/**
	 * @brief Demande à l'utilisateur de choisir un nouveau chemin d'accès vers Inkscape
	 */
	void changeInkscapePath();
	
	/**
	 * @brief Remet à 0 le compteur de transformations
	 */
	void resetTransformCounter();
	
	/**
	 * @brief Enregistre les préférences modifiées
	 */
	void save();
private:

};
#endif

