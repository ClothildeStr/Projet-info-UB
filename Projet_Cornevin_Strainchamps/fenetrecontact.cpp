/**
 * @file fenetrecontact.cpp
 * @brief Implémentation des méthodes de l'interface graphique qui permet de visualiser les informations d'un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

// fenetrecontact.cpp
#include "fenetrecontact.h"

FenetreContact::FenetreContact(Contact &contact, QWidget *parent)
    : QDialog(parent), nouveauContact(contact)
{


    setWindowTitle("Détails du Contact");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    nomLabel = new QLabel(this);
    prenomLabel = new QLabel(this);
    entrepriseLabel = new QLabel(this);
    emailLabel = new QLabel(this);
    telLabel = new QLabel(this);

    nomLabel->setText("Nom: " + QString::fromStdString(nouveauContact.getNom()));
    prenomLabel->setText("Prénom: " + QString::fromStdString(nouveauContact.getPrenom()));
    entrepriseLabel->setText("Entreprise: " + QString::fromStdString(nouveauContact.getEntreprise()));
    emailLabel->setText("Email: " + QString::fromStdString(nouveauContact.getMail()));
    telLabel->setText("Téléphone: " + QString::fromStdString(nouveauContact.getTel()));

    mainLayout->addWidget(nomLabel);
    mainLayout->addWidget(prenomLabel);
    mainLayout->addWidget(entrepriseLabel);
    mainLayout->addWidget(emailLabel);
    mainLayout->addWidget(telLabel);

    // Création d'un widget pour contenir la liste de contacts
    QWidget *interactionsWidget = new QWidget(this);
    mainLayout->addWidget(interactionsWidget);

    // Création de la liste de contacts
    interactionsList = new QListWidget(this);
    QVBoxLayout *interactionsLayout = new QVBoxLayout(interactionsWidget);
    interactionsLayout->addWidget(interactionsList);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/base.sqlite");

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données !";
        return;
    } else {
        // Recherche de l'ID du contact
        QSqlQuery queryIdContact;
        queryIdContact.prepare("SELECT idcontact FROM CONTACT WHERE nom = :nom AND prenom = :prenom");
        queryIdContact.bindValue(":nom", QString::fromStdString(nouveauContact.getNom()));
        queryIdContact.bindValue(":prenom", QString::fromStdString(nouveauContact.getPrenom()));

        if (queryIdContact.exec() && queryIdContact.next()) {
            // L'ID du contact a été trouvé
            int idContact = queryIdContact.value(0).toInt();

            QSqlQuery queryInteraction;
            queryInteraction.prepare("SELECT * FROM INTERACTION WHERE idcontact = :idcontact");
            queryInteraction.bindValue(":idcontact", idContact);

            if (queryInteraction.exec()) {
                while (queryInteraction.next()) {
                    // L'ID de l'interaction
                    int idInteraction = queryInteraction.value(0).toInt();

                    GestionTodo GT;

                    // Recherche des TODOS pour cette INTERACTION
                    QSqlQuery queryTodo;
                    queryTodo.prepare("SELECT * FROM TODO WHERE idinteraction = :idinteraction");
                    queryTodo.bindValue(":idinteraction", idInteraction);

                    if (queryTodo.exec()) {
                        while (queryTodo.next()) {
                            //on doit recuperer le int de la date pour le todo
                            QRegularExpression dateRegex("(\\d+)/(\\d+)/(\\d+)");
                            QRegularExpressionMatch dateMatch = dateRegex.match(queryTodo.value(4).toString());

                            if (dateMatch.hasMatch()) {
                                QString jour = dateMatch.captured(1);
                                QString mois = dateMatch.captured(2);
                                QString annee = dateMatch.captured(3);

                                Todo nouveauTodo(queryTodo.value(3).toString().toStdString(), jour.toInt(), mois.toInt(), annee.toInt());
                                GT.ajouterTodo(nouveauTodo);
                            }
                           // GT.ajouterTodo(nouveauTodo);
                        }
                    }

                    // Recherche des informations d'INTERACTION
                    QRegularExpression dateRegex("(\\d+)/(\\d+)/(\\d+)");
                    QRegularExpressionMatch dateMatch = dateRegex.match(queryInteraction.value(3).toString());

                    if (dateMatch.hasMatch()) {
                        QString jour = dateMatch.captured(1);
                        QString mois = dateMatch.captured(2);
                        QString annee = dateMatch.captured(3);

                        Date dateInteraction(jour.toInt(), mois.toInt(), annee.toInt());

                        Interaction nouvelleInteraction(queryInteraction.value(2).toString().toStdString(), dateInteraction, GT);
                        GI.ajouterInteraction(nouvelleInteraction);
                        nouveauContact.setlisteInteractionContact(nouvelleInteraction);
                    }
                }
            }
        }
        db.close();
    }

    if (GI.getNbInteraction() == 0) {
        interactionsList->addItem("Aucunne interaction pour ce contact");
        qDebug() << "Aucunne interaction pour ce contact";
    } else {
        for (int i = 0; i < GI.getNbInteraction(); i++) {
            // Ajoutez le contact à la QListWidget
            interactionsList->addItem(QString::fromStdString(GI.getInteraction(i).afficheInteraction()));
        }
    }


    // Ajouter de l'espace
    mainLayout->addSpacing(20);


    // Création du bouton pour supprimer des contacts
    QPushButton *supprEvenementButton = new QPushButton("Supprimer l'évenement", this);
    supprEvenementButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    mainLayout->addWidget(supprEvenementButton);

    connect(supprEvenementButton, &QPushButton::clicked, this, &FenetreContact::supprimerEvenement);

}

FenetreContact::~FenetreContact() {
}

void FenetreContact::supprimerEvenement(){
    QListWidgetItem *selectedItem = interactionsList->currentItem();
    if (selectedItem) {
        int index = interactionsList->row(selectedItem);
        if (index >= 0 && index < GI.getNbInteraction()) {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("/tmp/base.sqlite");

            if (!db.open()) {
                qDebug() << "Impossible de se connecter à la base de données !";
                return;
            }

            QSqlQuery querySupprInteraction;
            querySupprInteraction.prepare("DELETE FROM INTERACTION WHERE idinteraction = :idinteraction");
            querySupprInteraction.bindValue(":idinteraction", index);

            if (!querySupprInteraction.exec()) {
                qDebug() << "Impossible d'exécuter la requête de suppression ! Erreur : " << querySupprInteraction.lastError().text();
                return;
            }
            else{
                GI.supprimerInteraction(index);

                interactionsList->clear();
                qDebug() << "miseAJourListeInteraction";

                if (GI.getNbInteraction() == 0) {
                    interactionsList->addItem("Aucune interaction pour ce contact");
                    qDebug() << "Aucune interaction pour ce contact";
                } else {
                    for (int i = 0; i < GI.getNbInteraction(); i++) {
                        // Ajout le contact à la QListWidget
                        interactionsList->addItem(QString::fromStdString(GI.getInteraction(i).afficheInteraction()));
                    }
                }

                db.commit();
            }
            db.close();
        }
    }




}



