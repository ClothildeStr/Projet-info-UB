/**
 * @file fenetreajoutevenement.cpp
 * @brief Implémentation des méthodes de l'interface graphique qui permet d'ajouter des interactions à un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#include "fenetreajoutevenement.h"


FenetreAjoutEvenement::FenetreAjoutEvenement(Contact &contact, QWidget *parent)
    : QDialog(parent), nouveauContact(contact) {
    setWindowTitle("Ajouter un événement");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    contenuLineEdit = new QLineEdit(this);
    dateLineEdit = new QLineEdit(this);
    noteTextEdit = new QTextEdit(this);

    formLayout->addRow("Contenu:", contenuLineEdit);
    formLayout->addRow("Date:", dateLineEdit);
    formLayout->addRow("Note:", noteTextEdit);

    mainLayout->addLayout(formLayout);

    // Ajoutez le bouton "Enregistrer" en bas de la fenêtre
    QPushButton *enregistrerButton = new QPushButton("Enregistrer", this);
    mainLayout->addWidget(enregistrerButton);

    connect(enregistrerButton, &QPushButton::clicked, this, &FenetreAjoutEvenement::enregistrerEvenement);
}

FenetreAjoutEvenement::~FenetreAjoutEvenement() {}


void FenetreAjoutEvenement::enregistrerEvenement() {

    GestionTodo GT;
    // Récupérez les données du formulaire
    QString contenu = contenuLineEdit->text();
    QString date = dateLineEdit->text();
    QString note = noteTextEdit->toPlainText();


    // Utilisez une deuxième expression régulière pour extraire les chiffres entre les barres obliques
    QRegularExpression dateRegex("(\\d+)/(\\d+)/(\\d+)");
    QRegularExpressionMatch dateMatch = dateRegex.match(date);

    if (dateMatch.hasMatch()) {
        QString jour = dateMatch.captured(1);
        QString mois = dateMatch.captured(2);
        QString annee = dateMatch.captured(3);

        Date nouvelleDateInteraction(jour.toInt(), mois.toInt(), annee.toInt());

        if(nouvelleDateInteraction.dateValide()== 1){

            //on ouvre la bdd
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("/tmp/base.sqlite");

            if (!db.open())
            {
                qDebug() << "Pas de connexion BDD !";
            }
            else
            {
                qDebug() << "Connexion BDD ok";
                // Création des tables Todo et Interaction si elle n'existe pas
                QSqlQuery createTableQuery("CREATE TABLE IF NOT EXISTS INTERACTION ("
                                           "idinteraction INTEGER PRIMARY KEY AUTOINCREMENT, "
                                           "idcontact INTEGER NOT NULL, "
                                           "contenu TEXT, "
                                           "date TEXT, "
                                           "CONSTRAINT fk_CONTACT FOREIGN KEY (idcontact) REFERENCES CONTACT(idcontact) ON DELETE CASCADE,"
                                           "CONSTRAINT uc_idinteraction_idcontact UNIQUE (idinteraction, idcontact)"
                                           ");");

                if (!createTableQuery.exec()) {
                    qDebug() << "Erreur lors de la création de la table INTERACTION ! Erreur : " << createTableQuery.lastError().text();
                }
                else{
                    qDebug() << "Table INTERACTION créée avec succès";
                    // on créer maintenant la table des todo
                    QSqlQuery createTable2Query("CREATE TABLE IF NOT EXISTS TODO ("
                                                "idtodo INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                "idcontact INTEGER NOT NULL, "
                                                "idinteraction INTEGER NOT NULL, "
                                                "attodo TEXT, "
                                                "atdate TEXT, "
                                                "CONSTRAINT fk_CONTACT FOREIGN KEY (idcontact) REFERENCES CONTACT(idcontact) ON DELETE CASCADE,"
                                                "CONSTRAINT fk_INTERACTION FOREIGN KEY (idinteraction) REFERENCES INTERACTION(idinteraction) ON DELETE CASCADE,"
                                                "CONSTRAINT uc_idtodo_idcontact_idinteraction UNIQUE (idtodo, idcontact, idinteraction)"
                                                ");");
                    if (!createTable2Query.exec()) {
                        qDebug() << "Erreur lors de la création de la table TODO ! Erreur : " << createTable2Query.lastError().text();
                    }
                    else{
                        qDebug() << "Table TODO créée avec succès";

                        //on insere les données, en premier dans Interaction avec le bon id de contact
                        // Recherche de l'ID du contact
                        QSqlQuery queryIdContact;
                        queryIdContact.prepare("SELECT idcontact FROM CONTACT WHERE nom = :nom AND prenom = :prenom");
                        queryIdContact.bindValue(":nom", QString::fromStdString(nouveauContact.getNom()));
                        queryIdContact.bindValue(":prenom", QString::fromStdString(nouveauContact.getPrenom()));

                        if (queryIdContact.exec() && queryIdContact.next()) {
                            // L'ID du contact a été trouvé
                            int idContact = queryIdContact.value(0).toInt();

                            QSqlQuery queryInsertInteraction;
                            queryInsertInteraction.prepare("INSERT INTO INTERACTION (idcontact, contenu, date) VALUES (:idcontact, :contenu, :date)");
                            queryInsertInteraction.bindValue(":idcontact", idContact);
                            queryInsertInteraction.bindValue(":contenu", contenu);
                            queryInsertInteraction.bindValue(":date", date);

                            if (queryInsertInteraction.exec()) {
                                // L'insertion a réussi
                                qDebug() << "Insertion réussie dans la table INTERACTION.";

                                // expression régulière pour rechercher les occurrences de @todo
                                QRegularExpression todoRegex("@todo\\s+(.*?)\\s+@date\\s+(\\S+)");
                                QRegularExpressionMatchIterator todoMatches = todoRegex.globalMatch(note);

                                while (todoMatches.hasNext()) {
                                    QRegularExpressionMatch match = todoMatches.next();
                                    if (match.hasMatch()) {
                                        QString todoText = match.captured(1);
                                        QString todoDate = match.captured(2);

                                        // deuxième expression régulière pour extraire les chiffres entre les barres obliques
                                        QRegularExpression dateRegex("(\\d+)/(\\d+)/(\\d+)");
                                        QRegularExpressionMatch dateMatch = dateRegex.match(todoDate);

                                        if (dateMatch.hasMatch()) {
                                            QString jour = dateMatch.captured(1);
                                            QString mois = dateMatch.captured(2);
                                            QString annee = dateMatch.captured(3);


                                            Date nouvelleDate(jour.toInt(), mois.toInt(), annee.toInt());
                                            if(nouvelleDate.dateValide()== 1){
                                                // Créez un objet Todo avec les résultats
                                                Todo nouveauTodo(todoText.toStdString(), jour.toInt(), mois.toInt(), annee.toInt());
                                                GT.ajouterTodo(nouveauTodo);

                                                // ne pas récupérez l'ID de l'interaction que l'on vient d'insérer
                                                int idInteraction = queryInsertInteraction.lastInsertId().toInt();

                                                //on insère les todo dans la bdd
                                                QSqlQuery queryInsertTodo;
                                                queryInsertTodo.prepare("INSERT INTO TODO (idcontact, idinteraction, attodo, atdate) VALUES (:idcontact, :idinteraction, :attodo, :atdate)");
                                                queryInsertTodo.bindValue(":idcontact", idContact);
                                                queryInsertTodo.bindValue(":idinteraction", idInteraction);
                                                queryInsertTodo.bindValue(":attodo", todoText);
                                                queryInsertTodo.bindValue(":atdate", todoDate);

                                                if (queryInsertTodo.exec()) {
                                                    // L'insertion dans TODO a réussi
                                                    qDebug() << "Insertion réussie dans la table TODO.";
                                                }
                                                else {
                                                    // L'insertion dans TODO a échoué
                                                    qDebug() << "Erreur lors de l'insertion dans la table TODO :" << queryInsertTodo.lastError().text();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                // L'insertion dans INTERACTION a échoué
                                qDebug() << "Erreur lors de l'insertion dans la table INTERACTION :" << queryInsertInteraction.lastError().text();
                            }
                        }
                        else {
                            // L'ID du contact n'a pas été trouvé
                                qDebug() << "Erreur : Contact non trouvé.";
                        }
                    }
                }
            db.commit();

            // on verifie si tout est bien inséré

            QSqlQuery selectAllQuery("SELECT DISTINCT * FROM INTERACTION");

            if (!selectAllQuery.exec()) {
                qDebug() << "Impossible d'exécuter la requête SELECT ! Erreur : " << selectAllQuery.lastError().text();
            } else {
                while (selectAllQuery.next()) {
                    qDebug() << "ID interaction : " << selectAllQuery.value(0).toInt();
                    qDebug() << "ID contact: " << selectAllQuery.value(1).toInt();
                    qDebug() << "contenu : " << selectAllQuery.value(2).toString();
                    qDebug() << "date : " << selectAllQuery.value(3).toString();

                    qDebug() << "---------------"; // Séparation entre les enregistrements
                }
        }
            db.close();
            }
        }

        Interaction nouvelleInteraction(contenu.toStdString(), nouvelleDateInteraction, GT);
        nouveauContact.setlisteInteractionContact(nouvelleInteraction);
    }
    qDebug()<<"affichelist : " + QString::fromStdString(nouveauContact.getlisteInteractionContact().afficheListeInteraction());






    contenuLineEdit->clear();
    dateLineEdit->clear();
    noteTextEdit->clear();

    emit listeEvenementtMiseaJour();
    // Fermez la fenêtre
    close();
}

