/**
 * @file fenetreprincipalecontact.cpp
 * @brief Implémentation des méthodes de l'interface graphique principale de l'application
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 18/12/2023
*/

#include "fenetreprincipalecontact.h"

FenetrePrincipaleContact::FenetrePrincipaleContact(QWidget *parent)
    : QMainWindow(parent), fenetreAjoutContact(GC, this)/*, fenetreContact(nouveauContact, this)*/
{

    setWindowTitle("Application Contact");    //le titre de la fenêtre

    // Création du widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
/* menu ne s'affiche pas
    //instanciation de la barre de menu
    barreMenu= new QMenuBar(nullptr);
    //ajout à l’instance courante
    setMenuBar(barreMenu);

    QMenu *menuFichier = new QMenu(QString::fromUtf8("&Fichier"), this);
    barreMenu->addMenu(menuFichier);
    QMenu *menuCalcul = new QMenu(QString::fromUtf8("&Calcul"), this);
    barreMenu->addMenu(menuCalcul);

    QAction *actionQuitter = new QAction("Quitter", this);
    connect(actionQuitter, &QAction::triggered, qApp, &QCoreApplication::quit);  // Quitter l'application quand l'action est déclenchée
    menuFichier->addAction(actionQuitter);
*/



    // Création du layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Création du label centré en haut
    QLabel *titleLabel = new QLabel("Contacts", this);
    titleLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);

    //QLineEdit pour la barre de recherche
    QLineEdit *searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Rechercher un contact");
    mainLayout->addWidget(searchLineEdit);

    // Connectez le signal textChanged au slot de recherche
    connect(searchLineEdit, &QLineEdit::textChanged, this, &FenetrePrincipaleContact::rechercherContact);


    // Création de la zone de défilement
    QScrollArea *scrollArea = new QScrollArea(this);
    mainLayout->addWidget(scrollArea);

    // Création d'un widget pour contenir la liste de contacts
    QWidget *contactsWidget = new QWidget(this);
    scrollArea->setWidget(contactsWidget);

    // Création de la liste de contacts
    contactsList = new QListWidget(this);
    QVBoxLayout *contactsLayout = new QVBoxLayout(contactsWidget);
    contactsLayout->addWidget(contactsList);

    // Création du bouton pour ajouter des contacts
    QPushButton *addContactButton = new QPushButton("Ajouter un contact", this);
    addContactButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    contactsLayout->addWidget(addContactButton);

    // Création du bouton pour supprimer des contacts
    QPushButton *supprContactButton = new QPushButton("Supprimer le contact", this);
    supprContactButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    contactsLayout->addWidget(supprContactButton);

    // Création du bouton pour exporter la liste des contact depuis la bdd
    QPushButton *expoterJSON = new QPushButton("Exporter les contacts", this);
    expoterJSON->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    contactsLayout->addWidget(expoterJSON);

    // Création du bouton pour ajouter des contacts
    QPushButton *affContactButton = new QPushButton("Afficher le contact", this);
    affContactButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    contactsLayout->addWidget(affContactButton);

    // Création du bouton pour ajouter des contacts
    QPushButton *addEvenenementButton = new QPushButton("Ajouter un évenement", this);
    addEvenenementButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    contactsLayout->addWidget(addEvenenementButton);

    // Connectez les clics sur les boutons
    connect(addContactButton, &QPushButton::clicked, this, &FenetrePrincipaleContact::afficherFenetreAjoutContact);
    connect(supprContactButton, &QPushButton::clicked, this, &FenetrePrincipaleContact::supprimerContact);
    connect(expoterJSON, &QPushButton::clicked, this, &FenetrePrincipaleContact::exportContactJSON);
    connect(affContactButton, &QPushButton::clicked, this, &FenetrePrincipaleContact::afficherDetailsContact);
    connect(addEvenenementButton, &QPushButton::clicked, this, &FenetrePrincipaleContact::afficherFenetreAjoutEvenement);

    // Configurer la zone de défilement
    scrollArea->setWidgetResizable(true);

    // Redimensionner la fenêtre principale
    //resize(400, 300);

    connect(&fenetreAjoutContact, SIGNAL(listeContactMiseaJour()), this, SLOT(miseAJourListeContacts()));


    //connect(contactsList, &QListWidget::itemClicked, this, &FenetrePrincipaleContact::afficherDetailsContact);

    //on récupère les données depuis la bdd et on recréer nos objet
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/base.sqlite");

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données !";
        return;
    }

   QSqlQuery query("SELECT * FROM CONTACT");

    if (!query.exec()) {
        qDebug() << "Impossible d'exécuter la requête ! Erreur : " << query.lastError().text();
        return;
    }

    while (query.next()) {
        // Ajoutez le contact à la QListWidget
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString entreprise = query.value(3).toString();
        QString mail = query.value(4).toString();
        QString tel = query.value(5).toString();
        //QString uriphoto = query.value(6).toString();
        Contact nouveauC(nom.toStdString(), prenom.toStdString(), entreprise.toStdString(), mail.toStdString(), tel.toStdString(), "", GestionInteraction());
        GC.ajouterContact(nouveauC);
    }
    db.close();

    if (GC.getNbContact() == 0) {
        contactsList->addItem("Aucun contact dans la liste");
    } else {
        for (int i = 0; i < GC.getNbContact(); i++) {
            contactsList->addItem(QString::fromStdString(GC.getContact(i).getNom()) +" "+ QString::fromStdString(GC.getContact(i).getPrenom()));
        }
    }
}

FenetrePrincipaleContact::~FenetrePrincipaleContact()
{
}

void FenetrePrincipaleContact::afficherFenetreAjoutContact() {

    fenetreAjoutContact.exec();
}

void FenetrePrincipaleContact::miseAJourListeContacts() {
    // Effacez la liste actuelle des contacts dans l'interface graphique
    contactsList->clear();
    qDebug() << "miseAJourListeContacts";

    if (GC.getNbContact() == 0) {
        contactsList->addItem("Aucun contact dans la liste");
    } else {
        for (int i = 0; i < GC.getNbContact(); i++) {
            // Ajoutez le contact à la QListWidget
            contactsList->addItem(QString::fromStdString(GC.getContact(i).getNom()) +" "+ QString::fromStdString(GC.getContact(i).getPrenom()));
        }
    }
}

void FenetrePrincipaleContact::afficherDetailsContact(){
    QListWidgetItem *selectedItem = contactsList->currentItem();
    if (selectedItem) {
        int index = contactsList->row(selectedItem);
        if (index >= 0 && index < GC.getNbContact()) {
            nouveauContact = GC.getContact(index);
            FenetreContact fenetreContact(nouveauContact, this);
            fenetreContact.exec();
        }
    }

}

void FenetrePrincipaleContact::afficherFenetreAjoutEvenement(){
    QListWidgetItem *selectedItem = contactsList->currentItem();
    if (selectedItem) {
        int index = contactsList->row(selectedItem);
        if (index >= 0 && index < GC.getNbContact()) {
            nouveauContact = GC.getContact(index);
            FenetreAjoutEvenement fenetreAjoutEvenement(nouveauContact, this);
            fenetreAjoutEvenement.exec();
            connect(&fenetreAjoutEvenement, SIGNAL(listeEvenementMiseaJour()), this, SLOT(miseAJourListeContacts()));
        }
    }

}


void FenetrePrincipaleContact::supprimerContact(){
    QListWidgetItem *selectedItem = contactsList->currentItem();
    if (selectedItem) {
        int index = contactsList->row(selectedItem);
        if (index >= 0 && index < GC.getNbContact()) {
            nouveauContact = GC.getContact(index);
        }
    }


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/base.sqlite");

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données !";
        return;
    }

    QSqlQuery querySupprContact;
    querySupprContact.prepare("DELETE FROM CONTACT WHERE nom = :nom AND prenom = :prenom");
    querySupprContact.bindValue(":nom", QString::fromStdString(nouveauContact.getNom()));
    querySupprContact.bindValue(":prenom", QString::fromStdString(nouveauContact.getPrenom()));

    if (!querySupprContact.exec()) {
        qDebug() << "Impossible d'exécuter la requête de suppression ! Erreur : " << querySupprContact.lastError().text();
        return;
    }
    else{
        GC.supprimerContact(nouveauContact);
        miseAJourListeContacts();
        db.commit();
    }
    db.close();

}


void FenetrePrincipaleContact::rechercherContact(const QString &text)
{
    // Effacez la liste actuelle des contacts dans l'interface graphique
    contactsList->clear();

    // Affichez uniquement les contacts correspondant à la recherche
    for (int i = 0; i < GC.getNbContact(); i++) {
        std::string nomPrenom = GC.getContact(i).getNom() + " " + GC.getContact(i).getPrenom();
        QString nomPrenomQString = QString::fromStdString(nomPrenom);

        if (nomPrenomQString.contains(text, Qt::CaseInsensitive)) {
            contactsList->addItem(nomPrenomQString);
        }
    }
}

void FenetrePrincipaleContact::exportContactJSON() {
    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/base.sqlite");

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données !";
        return;
    }

    // Requête pour récupérer toutes les données
    QSqlQuery query("SELECT * FROM CONTACT");

    // Création d'un objet JSON
    QJsonObject json;
    QJsonArray contactsArray;

    while (query.next()) {
        QJsonObject contact;
        contact["nom"] = query.value(1).toString();
        contact["prenom"] = query.value(2).toString();

        // Ajouter le contact à l'objet JSON
        contactsArray.append(contact);
    }
    // Ajoutez l'array JSON à l'objet principal avec la clé "contacts"
    json["contacts"] = contactsArray;

    // Fermer la base de données
    db.close();

    // Convertir l'objet JSON en document JSON
    QJsonDocument jsonDocument(json);

    // Écrire le document JSON dans un fichier
    QFile file("export.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDocument.toJson());
        file.close();
    } else {
        qDebug() << "Impossible d'ouvrir le fichier d'export JSON.";
    }
}

