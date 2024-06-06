#include "fenetreprincipalecontact.h"
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
/*
    Date d(21, 10, 2023);

    //Tests classe Todo
    Todo t1("Apporter odinateur");
    Todo t2("Apporter cahier", 27,10,2023);

    //Tests classe GestionTodo
    GestionTodo GT;
    GestionTodo GT2;
    GT.ajouterTodo(t1);
    GT.ajouterTodo(t2);
    GT2.ajouterTodo(t1);
    std::cout << GT.afficheListeTodo() << std::endl;
    std::cout << "\n" << std::endl;

    //Tests classe Interaction
    Interaction i1("Rdv mirande", d,GT);
    Interaction i2("Rdv droit-lettres", d, GT2);
    std::cout << i1.afficheInteraction() << std::endl;

    //Tests classe Interaction
    GestionInteraction GI;
    GestionInteraction GI2;
    std::cout << "Tests classe GestionInteraction" << std::endl;
    GI.ajouterInteraction(i1);
    GI.ajouterInteraction(i2);


    //Tests classe Contact
    Contact c1("strainchamps","clothilde","etudiante UB", "Clothilde_Strainchamps@etu.u-bourgogne.fr", "06 34 37 60 45", "photo", GI);
    //Contact c2("cornevin","camille","etudiante UB", "Camille_Cornevin@etu.u-bourgogne.fr", "06 96 50 94 58", "photo", GI2);
    Contact c3("laissus","marie-agnes","infirmiere", "marieagnes.straincamps@gmail.com", "06 74 66 24 58", "photo");

   // c1.setlisteInteractionContact(i1);
   // c1.setlisteInteractionContact(i2);
    std::cout << "nb interaction : " << c1.getlisteInteractionContact().getNbInteraction()<< "liste interaction c1: " << c1.getlisteInteractionContact().afficheListeInteraction() << std::endl;

    //Tests classe GestionContact
    GestionContact GC;
    std::cout << "Tests classe GestionContact" << std::endl;
    GC.ajouterContact(c1);
    GC.ajouterContact(c2);
    GC.ajouterContact(c3);
    GC.afficheListeContact();

    GC.rechercherContactEntreprise("etudiante UB");
    std::cout << "resultat de la recherche de contact par entreprise pour etudiante UB : " << std::endl;
    GC.afficheListeCourante();


    Bdd bdd;
    QString numContact = "1"; // Déclarez une variable pour stocker l'entier
    QString nom = "Cornevin";
    QString prenom = "Camille";
    QString entreprise = "UB";
    QString email = "camille_cornevin@etu.u-bourgogne.fr";
    QString tel = "0123456789";
    QString photo = "NULL";
    QString dateCreation = "07/12/2023";
    int nb = 1;

    bdd.insertContact(numContact, nom, prenom, entreprise, email, tel, photo, dateCreation);
        if (bdd.contactExists(nb)) {
            qDebug() << "Insérée";
        } else {
            qDebug() << "pas insérée";
        }

*/
    QApplication a(argc, argv);
    FenetrePrincipaleContact w;
    w.show();
    return a.exec();

    //QApplication b(argc, argv);
    //FenetreAjoutContact wc;
    //wc.show();
    //return b.exec();

    return 0;
}
