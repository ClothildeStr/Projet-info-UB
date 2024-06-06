/**
 * @file contact.h
 * @brief Définition des méthodes de la classe Contact
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <vector>
#include "gestioninteraction.h"
#include "date.h"
//using namespace std;

/**  
 * @class Classe pour definir un objet de type Contact
 * @param nom chaine de caractères contenant le nom du contact
 * @param prenom chaine de caractères contenant le prenom du contact
 * @param entreprise chaine de caractères contenant le nom de l'entreprise du contact
 * @param mail chaine de caractères contenant le mail du contact
 * @param tel chaine de caractères contenant le numéro de téléphone du contact
 * @param photo chaine de caractères contenant l'URI de la photo du contact
 * @param dateCreation date de création du contact
 * @param dateDerniereModif date de dernière modification du contact
 * @param listeIteractionContact liste d'Interaction du contact de type GestionInteraction
 *
*/
class Contact
{

private:
    std::string nom;
    std::string prenom;
    std::string entreprise;
    std::string mail;
    std::string tel;
    std::string photo;
    Date dateCreation;
    Date dateDerniereModif;
    GestionInteraction listeInteractionContact;

public:

/**
 * @brief Constructeur de la classe Contact
*/
    Contact(std::string ,std::string ,std::string ,std::string ,std::string , std::string , GestionInteraction );

/**
 * @brief Constructeur de la classe Contact
*/
    Contact(std::string ,std::string ,std::string ,std::string ,std::string , std::string );
/**
 * @brief Constructeur de la classe Contact
*/
    Contact();


/**
 *
 * @brief Destructeur de la classe Contact
*/
    ~Contact();

/**
 * @brief Accesseurs
 */
    std::string getNom();
    std::string getPrenom();
    std::string getEntreprise();
    std::string getMail();
    std::string getTel();
    std::string getPhoto();
    Date getDateCreation();
    Date getDateDerniereModif();
    GestionInteraction getlisteInteractionContact();

/**
 * @brief Mutateurs
 */   
    void setNom(std::string);
    void setPrenom(std::string);
    void setEntreprise(std::string);
    void setMail(std::string);
    void setTel(std::string);
    void setPhoto(std::string);
    void setDateCreation(int, int, int);
    void setDateDerniereModif(int, int, int);
    void setlisteInteractionContact(Interaction i);

/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    void afficheContact();
};

#endif // CONTACT_H
