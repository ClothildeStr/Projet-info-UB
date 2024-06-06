/**
 * @file gestioncontact.h
 * @brief Définition de la classe GestionContact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H
#include <vector>
#include <iostream>
#include "contact.h"

/**  
 * @class Classe pour definir un objet de type GestionContact
 * @param listeContact liste de Contact
 * @param listeContactCourante liste de Contact qui correspond au résultat d'une recherche dans la liste de Contact listeContact
 *
*/
class GestionContact
{
private:
    std::vector<Contact> listeContact;
    std::vector<Contact> listeCourante;

public:
/**
 * @brief Constructeur par défaut de la classe GestionContact
*/
    GestionContact();

/**
 * @brief Destructeur de la classe GestionContact
*/   
    ~GestionContact();

/**
 * @brief Méthode pour accéder à un Contact dans listeContact
*/   
    Contact getContact(int);

/**
 * @brief Méthode qui renvoie la taille de listeContact
*/ 
    int getNbContact();

/**
 * @brief Méthode pour accéder à un Contact dans listeContactCourante
*/
    Contact getContactCourant(int);

/**
 * @brief Méthode qui renvoie la taille de listeContactCourante
*/    
    int getNbContactCourant();

/**
 * @brief Méthode pour ajouter un Contact à listeContact par ordre alphabétique en fonction du nom de famille
*/
    void ajouterContact(const Contact& contact);
/**
 * @brief Méthode pour supprimer un Contact à listeContact
*/   
    void supprimerContact(Contact);

/**
 * @brief Méthode qui permet de rechercher un Contact grâce à son nom
*/ 
    void rechercherContactNom(std::string);

/**
 * @brief Méthode qui permet de rechercher un Contact grâce à son entreprise
*/
    void rechercherContactEntreprise(std::string);

/**
 * @brief Méthodes pour afficher la classe dans le terminal
 */
    void afficheListeContact();
    void afficheListeCourante();
    
};

#endif // GESTIONCONTACT_H
