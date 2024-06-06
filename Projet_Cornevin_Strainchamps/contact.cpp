/**
 * @file contact.cpp
 * @brief Définition des méthodes de la classe Contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "contact.h"

/**
 * @brief Constructeur de la classe Contact, la date de création et de modification actuelle sont remplies automatiquement
 * @param[in] n valeur initiale de l'attribut nom
 * @param[in] p valeur initiale de l'attribut prenom
 * @param[in] e valeur initiale de l'attribut entrprise
 * @param[in] m valeur initiale de l'attribut mail
 * @param[in] t valeur initiale de l'attribut tel
 * @param[in] ph valeur initiale de l'attribut photo
 * @param[in] GI valeur initiale de l'attribut listeInteractionContact 
 */
Contact::Contact(std::string n, std::string p, std::string e, std::string m, std::string t, std::string ph, GestionInteraction GI)
    : nom(n), prenom(p), entreprise(e), mail(m), tel(t), photo(ph), dateDerniereModif(0, 0, 0), listeInteractionContact(GI){
    dateCreation.donneDateActuelle();

}

Contact::Contact(std::string n, std::string p, std::string e, std::string m, std::string t, std::string ph)
    : nom(n), prenom(p), entreprise(e), mail(m), tel(t), photo(ph), dateDerniereModif(0, 0, 0){
    dateCreation.donneDateActuelle();

}
Contact::Contact(){
    /*
    nom = "";
    prenom = "";
    entreprise = "";
    mail = "";
    tel = "";
    photo = "";
    dateDerniereModif.donneDateActuelle();
    dateCreation.donneDateActuelle();
*/
}
/**
 * @brief Destructeur de la classe Contact
*/
Contact::~Contact(){

}

/**
 * @brief Accesseur de l'attribut nom
 * @return nom la valeur de l'attribut nom
 * @retval std::string le type de l'attribut nom
 */
std::string Contact::getNom(){
    return nom;
}

/**
 * @brief Mutateur de l'attribut nom
 * @param[in]n nouvelle valeur de l'attribut nom
 * @retval std::string le type de l'attribut nom
 */
void Contact::setNom(std::string n){
    nom = n;
}

std::string Contact::getPrenom(){
    return prenom;
}
void Contact::setPrenom(std::string p){
    prenom = p;
}

std::string Contact::getEntreprise(){
    return entreprise;
}
void Contact::setEntreprise(std::string e){
    entreprise = e;
}

std::string Contact::getMail(){
    return mail;
}
void Contact::setMail(std::string m){
    mail = m;
}

std::string Contact::getTel(){
    return tel;
}
void Contact::setTel(std::string t){
    tel = t;
}

std::string Contact::getPhoto(){
    return photo;
}
void Contact::setPhoto(std::string ph){
    photo = ph;
}

/**
 * @brief Accesseur de l'attribut dateCreation
 * @return date la valeur de l'attribut dateCreation
 * @retval Date le type de l'attribut dateCreation
 */
Date Contact::getDateCreation(){
    return dateCreation;
}

/**
 * @brief Mutateur de l'attribut date
 * @param[in] j nouvelle valeur pour le jour de l'attribut dateCreation
 * @param[in] m nouvelle valeur pour le mois de l'attribut dateCreation
 * @param[in] a nouvelle valeur pour l'année de l'attribut dateCreation
 */
void Contact::setDateCreation(int j, int m, int a){
    dateCreation.setJour(j);
    dateCreation.setMois(m);
    dateCreation.setAnnee(a);
}

Date Contact::getDateDerniereModif(){
    return dateDerniereModif;
}
void Contact::setDateDerniereModif(int j, int m, int a){
    dateDerniereModif.setJour(j);
    dateDerniereModif.setMois(m);
    dateDerniereModif.setAnnee(a);
}

GestionInteraction Contact::getlisteInteractionContact(){
    return listeInteractionContact;
}

void Contact::setlisteInteractionContact(Interaction i){
    listeInteractionContact.ajouterInteraction(i);
}


void Contact::afficheContact(){
    std::cout<<"Nom: " << nom << "\n" <<
               "Prenom: " << prenom <<"\n" <<
               "Entreprise: " << entreprise <<"\n" <<
               "Mail: " << mail <<"\n" <<
               "Tel: " << tel <<"\n" <<
               "Date création: " ;
                dateCreation.afficheDate();
                std::cout << "Date de dernière modification: ";
                dateDerniereModif.afficheDate();
                listeInteractionContact.afficheListeInteraction();
                std::cout << "\n";
}
