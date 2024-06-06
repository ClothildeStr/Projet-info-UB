/**
 * @file fenetrecontact.h
 * @brief Définition de l'interface graphique qui permet de visualiser les informations d'un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

// fenetrecontact.h
#ifndef FENETRECONTACT_H
#define FENETRECONTACT_H

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "contact.h"  // Assurez-vous d'inclure votre classe Contact

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>


class FenetreContact : public QDialog {
    Q_OBJECT

public:
/**
 * @class Classe pour definir un objet de type FenetreContact qui hérite de QDialog
 * @param Contact &contac et un QWidget *parent (donc this)
 *
*/
    FenetreContact(Contact &contact, QWidget *parent = nullptr);

/**
 * @brief Destructeur de la classe FenetreContact
*/
    ~FenetreContact();

private:

    QLabel *nomLabel;
    QLabel *prenomLabel;
    QLabel *entrepriseLabel;
    QLabel *emailLabel;
    QLabel *telLabel;
    QLabel *evenementLabel;
    QWidget *interactionsWidget;
    QListWidget *interactionsList;
    QPushButton *supprEvenementButton;

    QVBoxLayout *mainLayout;
    QVBoxLayout *interactionsLayout;

    Contact &nouveauContact;
    GestionInteraction GI;

    QSqlDatabase db;

private slots:

/**
 * @brief slot de la classe FenetreContact qui permet quand on à sélectionner un évenement dans la liste,
 * de supprimer l'évenement d'un contact en appuyant sur le bouton "supprimer l'evenement"
*/
    void supprimerEvenement();

};

#endif // FENETRECONTACT_H
