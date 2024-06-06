/**
 * @file fenetreajoutcontact.h
 * @brief Définition de l'interface graphique qui permet d'ajouter un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#ifndef FENETREAJOUTCONTACT_H
#define FENETREAJOUTCONTACT_H

#include "gestioncontact.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>


/**
 * @class Classe pour definir un objet de type FenetreAjoutContact qui hérite de QDialog
 * @param GestionContact &gestioncontact et un QWidget *parent (donc this)
 *
*/
class FenetreAjoutContact : public QDialog {
    Q_OBJECT

public:

/**
 * @brief Constructeur de la classe FenetreAjoutContact
*/
    FenetreAjoutContact(GestionContact &gestionContact, QWidget *parent = nullptr);

/**
 * @brief Destructeur de la classe FenetreAjoutContact
*/
    ~FenetreAjoutContact();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *photoLayout;
    QFormLayout *formLayout;
    QLabel *photoLabel;
    QPushButton *changePhotoButton;
    QLabel *nomLabel;
    QLineEdit *nomLineEdit;
    QLabel *prenomLabe;
    QLineEdit *prenomLineEdit;
    QLabel *entrepriseLabel;
    QLineEdit *entrepriseLineEdit;
    QLabel *telLabel;
    QLineEdit *telLineEdit;
    QLabel *mailLabel;
    QLineEdit *mailLineEdit;
    QPushButton *enregistrerButton;

    GestionContact &GC;

    QSqlDatabase db;

private slots:
    void changerPhoto();// ne marche pas bien

/**
 * @brief slot de la classe FenetreAjoutContact qui enregistre l'ajout d'un contact,
 * ce slot est déclencher quand on appuie sur le bouton "Enregistrer"
*/
    void enregistrerContact();


signals:

/**
 * @brief signal de la classe FenetreAjoutContact,
 * ce signal est émit quand à la fin du slot enregistrerContact()
*/
    void listeContactMiseaJour();
};

#endif // FENETREAJOUTCONTACT_H
