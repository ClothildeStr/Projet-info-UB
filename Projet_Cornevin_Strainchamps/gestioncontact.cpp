/**
 * @file gestioncontact.cpp
 * @brief Définition de la classe GestionContact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "gestioncontact.h"

#include <algorithm>
#include <string.h>

/**
 * @brief Constructeur par défaut de la classe GestionContact
*/
GestionContact::GestionContact()
{
    std::vector<Contact> listeContact;
    std::vector<Contact> listeCourante;
}

/**
 * @brief Destructeur par défaut de la classe GestionContact
*/
GestionContact::~GestionContact(){

}

/**
 * @brief Méthode nous renvoyant un Contact
 * @param[in] i position dans listeContact
 * @return un Contact de listeContact
 * @retval Contact
 */
Contact GestionContact::getContact(int i){
    return listeContact[i];
}

/**
 * @brief Méthode nous renvoyant la taille de listeContact 
 * @retval int
 */
int GestionContact::getNbContact(){
    return listeContact.size();
}

/**
 * @brief Méthode nous renvoyant un Contact
 * @param[in] i position dans listeContactCourant
 * @return un Contact de listeContactCourant
 * @retval Contact
 */
Contact GestionContact::getContactCourant(int i){
    return listeCourante[i];
}

/**
 * @brief Méthode nous renvoyant la taille de listeContactCourant 
 * @retval int
 */
int GestionContact::getNbContactCourant(){
    return listeCourante.size();
}


void GestionContact::ajouterContact(const Contact& c){
    listeContact.push_back(c);
    std::sort(listeContact.begin(), listeContact.end(),
                  []( Contact a,  Contact b) {
                      return a.getNom() < b.getNom();
                  });
}

/**
 * @brief Méthode pour supprimer un Contact
 * @param[in] c qui est le Contact que l'on veut supprimer
 */
void GestionContact::supprimerContact(Contact c){
    // Supprimer un contact spécifique par nom.
        std::string nomASupprimer = c.getNom();
        auto it = std::remove_if(listeContact.begin(), listeContact.end(),
                                [nomASupprimer](Contact contact) {
                                    return contact.getNom() == nomASupprimer;
                                });
        listeContact.erase(it, listeContact.end());
}

/**
 * @brief Méthode qui permet de rechercher un Contact grâce à son nom
 * @param[in] nc qui est le nom du contact que l'on recherche
 * @attention cette méthode renvoie une liste de Contact car plusieurs Contacts peuvent avoir le même nom de famille
*/
void GestionContact::rechercherContactNom(std::string nc){
    if(nc.size()!=0){
        listeCourante.clear();
        for(int i=0; i<getNbContact(); i++){//on parcourt la liste
            if(getContact(i).getNom().compare(nc)==0){//si nos deux chaine de caractère sont égales (pseudo)
                listeCourante.push_back(getContact(i));
            }
        }
    }
}

/**
 * @brief Méthode qui permet de rechercher un Contact grâce au nom de son entreprise
 * @param[in] nc qui est le nom de l'entreprise du contact que l'on recherche
 * @attention cette méthode renvoie une liste de Contact car plusieurs Contacts peuvent traviller dans la même entreprise
*/
void GestionContact::rechercherContactEntreprise(std::string ec){
    if(ec.size()!=0){
        listeCourante.clear();
        for(int i=0; i<getNbContact(); i++){//on parcourt la liste
            if(getContact(i).getEntreprise().compare(ec)==0){ //si nos deux chaine de caractère sont égales (pseudo)
                listeCourante.push_back(getContact(i));
            }
        }

    }
}

void GestionContact::afficheListeContact(){
    if(getNbContact()==0){
        std::cout << "Aucun contact dans la liste" << std::endl;
    }
    else{
        for(int i=0; i<getNbContact(); i++){
             getContact(i).afficheContact();
        }
    }
}

void GestionContact::afficheListeCourante(){
    if(getNbContactCourant()==0){
        std::cout << "liste courante vide" << std::endl;
    }
    else{
        for(int i=0; i<getNbContactCourant(); i++){
             getContactCourant(i).afficheContact();
        }
    }
}
