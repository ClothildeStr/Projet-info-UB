/**
 * @file fenetreajoutcontact.cpp
 * @brief Implémentation des méthodes de l'interface graphique qui permet d'ajouter un contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#include "fenetreajoutcontact.h"
#include <QFileDialog>
#include <QPixmap>


FenetreAjoutContact::FenetreAjoutContact(GestionContact &gestionContact, QWidget *parent)
    : QDialog(parent), GC(gestionContact){

    // Initialiser les widgets membres
    nomLineEdit = new QLineEdit(this);
    prenomLineEdit = new QLineEdit(this);
    entrepriseLineEdit = new QLineEdit(this);
    mailLineEdit = new QLineEdit(this);
    telLineEdit = new QLineEdit(this);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Créez un QHBoxLayout pour la rangée de photo et le QFormLayout
    QHBoxLayout *photoLayout = new QHBoxLayout();


    // Créez un QLabel pour afficher la photo
    QLabel *photoLabel = new QLabel(this);
    photoLabel->setPixmap(QPixmap("photo.jpg")); // Image par défaut
    photoLayout->addWidget(photoLabel, 0, Qt::AlignTop); // Alignez en haut

    // Ajoutez le bouton "Changer la photo" en dessous de l'image
    QPushButton *changePhotoButton = new QPushButton("Changer la photo", this);
    connect(changePhotoButton, &QPushButton::clicked, this, &FenetreAjoutContact::changerPhoto);
    photoLayout->addWidget(changePhotoButton, 0, Qt::AlignBottom); // Alignez en bas

    // Ajoutez le QFormLayout à droite du QLabel de la photo
    QFormLayout *formLayout = new QFormLayout();

    // Utilisez QFormLayout pour ajouter des paires QLabel-QWidget (étiquette, champ de saisie)

    QLabel *nomLabel = new QLabel("Nom:", this);
        //QLineEdit *nomLineEdit = new QLineEdit(this);
    formLayout->addRow(nomLabel, nomLineEdit);

    QLabel *prenomLabel = new QLabel("Prénom:", this);
                          //QLineEdit *prenomLineEdit = new QLineEdit(this);
                          formLayout->addRow(prenomLabel, prenomLineEdit);

    QLabel *entrepriseLabel = new QLabel("Entreprise:", this);
        //QLineEdit *entrepriseLineEdit = new QLineEdit(this);
    formLayout->addRow(entrepriseLabel, entrepriseLineEdit);

    QLabel *mailLabel = new QLabel("EMail:", this);
        //QLineEdit *telLineEdit = new QLineEdit(this);
    formLayout->addRow(mailLabel, mailLineEdit);

    QLabel *telLabel = new QLabel("Tel:", this);
        //QLineEdit *telLineEdit = new QLineEdit(this);
    formLayout->addRow(telLabel, telLineEdit);



    // Ajoutez le QFormLayout à droite du QLabel de la photo
    photoLayout->addLayout(formLayout);

    // Ajoutez le QHBoxLayout au layout principal
    mainLayout->addLayout(photoLayout);

    // Ajoutez un espace extensible pour pousser le bouton vers le bas
    mainLayout->addStretch();

    // Ajoutez le bouton "Enregistrer" en bas de la fenêtre
    QPushButton *enregistrerButton = new QPushButton("Enregistrer", this);
    mainLayout->addWidget(enregistrerButton, 0, Qt::AlignBottom); // Alignez en bas

    // Connectez le signal clicked du bouton "Enregistrer" à une fonction
    connect(enregistrerButton, &QPushButton::clicked, this, &FenetreAjoutContact::enregistrerContact);

}



FenetreAjoutContact::~FenetreAjoutContact() {
}



void FenetreAjoutContact::changerPhoto() {
    // Utilisez QFileDialog pour sélectionner une nouvelle photo
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir une photo", "", "Images (*.png *.jpg *.jpeg)");

    if (!fileName.isEmpty()) {
        // Chargez et affichez la nouvelle photo dans le QLabel
        QLabel *photoLabel = findChild<QLabel*>(QString("photoLabel"));
        if (photoLabel) {
            QPixmap newPixmap(fileName);
            photoLabel->setPixmap(newPixmap.scaledToWidth(photoLabel->width(), Qt::SmoothTransformation));
        }
    }
}

// Fonction appelée lorsque le bouton "Enregistrer" est pressé
void FenetreAjoutContact::enregistrerContact() {
    // Récupérez les données des widgets
    QString nom = nomLineEdit->text();
    QString prenom = prenomLineEdit->text();
    QString entreprise = entrepriseLineEdit->text();
    QString mail = mailLineEdit->text();
    QString tel = telLineEdit->text();
    //QString photo = telLineEdit->text();

    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Entreprise:" << entreprise;
    qDebug() << "EMail:" << mail;
    qDebug() << "Téléphone:" << tel;

    // Expression régulière pour les noms et prénoms (lettres majuscules ou minuscules)
    QRegularExpression nomPrenomEntrepriseRegex("^[a-zA-ZÀ-ÖØ-öø-ÿ-]+$");

    // Expression régulière pour les adresses e-mail
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    // Expression régulière pour les numéros de téléphone (chiffres uniquement)
    QRegularExpression telRegex("^[0-9]+$");

    if (!nomPrenomEntrepriseRegex.match(nom).hasMatch() || !nomPrenomEntrepriseRegex.match(prenom).hasMatch()
        || !nomPrenomEntrepriseRegex.match(entreprise).hasMatch() || !emailRegex.match(mail).hasMatch()
        || !telRegex.match(tel).hasMatch()) {
        qDebug() << "mauvais format";
    }
    else{
        // Créez un objet Contact avec les données récupérées
        Contact nouveauContact(nom.toStdString(), prenom.toStdString(), entreprise.toStdString(), mail.toStdString(), tel.toStdString(), "", GestionInteraction());
        nouveauContact.afficheContact();
        //Contact c1("strainchamps","clothilde","etudiante UB", "Clothilde_Strainchamps@etu.u-bourgogne.fr", "06 34 37 60 45", "photo", GI);
        // Ajoutez le contact à l'objet GestionContact
        GC.ajouterContact(nouveauContact);

        //ajout du contact à la BDD
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/tmp/base.sqlite");

        if (!db.open())
        {
            qDebug() << "Pas de connexion BDD !";
        }
        else
        {
            qDebug() << "Connexion BDD ok";

            // Création de la table contact si elle n'existe pas
            QSqlQuery createTableQuery("CREATE TABLE IF NOT EXISTS CONTACT ("
                       "idcontact INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "nom TEXT NOT NULL,"
                       "prenom TEXT NOT NULL,"
                       "entreprise TEXT,"
                       "mail TEXT,"
                       "tel TEXT NOT NULL,"
                       "uriphoto TEXT,"
                       "datecreation DATETIME DEFAULT CURRENT_TIMESTAMP,"
                       "CONSTRAINT uc_nom_prenom UNIQUE (nom, prenom)"
                       ");");

            if (!createTableQuery.exec()) {
                qDebug() << "Erreur lors de la création de la table CONTACT ! Erreur : " << createTableQuery.lastError().text();
            } else {

                qDebug() << "Table 'Contact' créé avec succès";

                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO CONTACT (nom, prenom, entreprise, mail, tel, uriphoto) "
                                            "VALUES (:nom, :prenom, :entreprise, :mail, :tel, :uriphoto)");

                insertQuery.bindValue(":nom", nom);
                insertQuery.bindValue(":prenom", prenom);
                insertQuery.bindValue(":entreprise", entreprise);  // Correction de la faute de frappe dans le nom de la colonne
                insertQuery.bindValue(":mail", mail);
                insertQuery.bindValue(":tel", tel);
                insertQuery.bindValue(":uriphoto", " ");
                insertQuery.exec();
                db.commit();
            }
        }

        db.close();
    }

            nomLineEdit->clear();
            prenomLineEdit->clear();
            entrepriseLineEdit->clear();
            mailLineEdit->clear();
            telLineEdit->clear();

        // Mise à jour fenetrecontactprincipale
        emit listeContactMiseaJour();
        close();

}
