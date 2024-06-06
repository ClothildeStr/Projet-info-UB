/**
 * @file fenetreprincipalecontact.h
 * @brief Définition de l'interface graphique principale de l'application
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#ifndef FENETREPRINCIPALECONTACT_H
#define FENETREPRINCIPALECONTACT_H

#include <QWidget>
#include <QMainWindow>

//#include "gestioncontact.h"
#include "fenetreajoutcontact.h"
#include "fenetrecontact.h"
#include "fenetreajoutevenement.h"

//pour les widgets
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

/**
 * @class Classe pour definir un objet de type FenetrePrincipaleContact qui hérite de QMainWindow
 * @param QWidget *parent, donc this
 *
*/

class FenetrePrincipaleContact : public QMainWindow
{
    Q_OBJECT
public:
/**
 * @brief Constructeur de la classe FenetrePrincipaleContact
*/
    FenetrePrincipaleContact(QWidget *parent = nullptr);

/**
 * @brief Destructeur de la classe FenetrePrincipaleContact
*/
    ~FenetrePrincipaleContact();

private:
    FenetreAjoutContact fenetreAjoutContact;

    //nos widgets, par pointeurs

    //QMenuBar *barreMenu;
    /*QMenu *contactMenu;
    QAction *ajouterContactAction;
    QAction *modifierContactAction;
    QAction *supprimerContactAction;*/

    QLabel *titleLabel;
    QScrollArea *scrollArea;
    QWidget *contactsWidget;
    QListWidget *contactsList;
    QPushButton *addContactButton;
    QPushButton *affContactButton;
    QPushButton *addEvenementButton;
    QPushButton *expoterJSON;

    //struture de données c++
    GestionContact GC;
    Contact nouveauContact;

    QSqlDatabase db;

private slots:


/**
 * @brief slot de la classe FenetrePrincipaleContact qui nous affiche la fenetre d'ajout d'un contact,
 * ce slot est déclencher quand on appuie sur le bouton "Ajouter un contact"
*/
    void afficherFenetreAjoutContact();

/**
 * @brief slot de la classe FenetrePrincipaleContact qui une fois que la fenetre d'ajout d'un contact a émis un signal s'exécute,
 * le signal reçu est : listeContactMiseaJour()
*/
    void miseAJourListeContacts();

/**
 * @brief slot de la classe FenetrePrincipaleContact qui une fois que l'on a sélectionner un contact dans notre liste de contact,
 * et que l'on appuie sur le bouton "afficher le contact", la fenetre de visualisation d'un contact s'ouvre.
*/
    void afficherDetailsContact();

/**
 * @brief slot de la classe FenetrePrincipaleContact qui une fois que l'on a sélectionner un contact dans notre liste de contact,
 * et que l'on appuie sur le bouton "Ajouter un évenement", la fenetre d'ajout d'un evenement s'ouvre.
*/
    void afficherFenetreAjoutEvenement();

/**
 * @brief slot de la classe FenetrePrincipaleContact qui une fois que l'on a sélectionner un contact dans notre liste de contact,
 * et que l'on appuie sur le bouton "Supprimer le contact", supprime notre contact.
*/
    void supprimerContact();

/**
 * @brief slot de la classe FenetrePrincipaleContact qui vide notre widget de la liste de contact,
 * et au fur et a mesure que l'on écrit notre recherche, les résultats de notre recherche apparaissent
 * @param[in] une chaine de caractère qui est notre recherche.
*/
    void rechercherContact(const QString &text);

    void exportContactJSON();

};

#endif // FENETREPRINCIPALECONTACT_H
