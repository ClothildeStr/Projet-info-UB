/**
 * @file fenetreajoutevenement.h
 * @brief Définition de l'interface graphique qui permet d'ajouter des interactions à un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#ifndef FENETREAJOUTEVENEMENT_H
#define FENETREAJOUTEVENEMENT_H


#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRegularExpression>

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>

#include "contact.h"

/**
 * @class Classe pour definir un objet de type FenetreAjoutEvenement qui hérite de QDialog
 * @param Contact &contac et un QWidget *parent (donc this)
 *
*/
class FenetreAjoutEvenement : public QDialog {
    Q_OBJECT

public:

/**
 * @brief Constructeur de la classe FenetreAjoutEvenement
*/
    FenetreAjoutEvenement(Contact &contact, QWidget *parent = nullptr);

/**
 * @brief Destructeur de la classe FenetreAjoutEvenement
*/
    ~FenetreAjoutEvenement();

private:
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QLineEdit *contenuLineEdit;
    QLineEdit *dateLineEdit;
    QTextEdit *noteTextEdit;
    QPushButton *enregistrerButton;

    Contact &nouveauContact;

    QSqlDatabase db;


private slots:

/**
 * @brief slot de la classe FenetreAjoutEvenement qui enregistre l'ajout d'un évenement,
 * ce slot est déclencher quand on appuie sur le bouton "Ajouter un évenement"
*/
    void enregistrerEvenement();


signals:

/**
 * @brief signal de la classe FenetreAjoutEvenement,
 * ce signal est émit quand à la fin du slot enregistrerEvenement()
*/
    void listeEvenementtMiseaJour();
};

#endif // FENETREAJOUTEVENEMENT_H
