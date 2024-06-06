/**
 * @file gestioninteraction.h
 * @brief Définition de la classe GestionInteraction
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H
#include <vector>
#include <iostream>
#include "interaction.h"

/**  
 * @class Classe pour definir un objet de type GestionTodo
 * @param listeInteraction liste d'Interaction
 *
*/
class GestionInteraction
{
private:
    std::vector<Interaction> listeInteraction;
public:
/**
 * @brief Constructeur par défaut de la classe GestionInteraction
*/
    GestionInteraction();

/**
 * @brief Destructeur de la classe GestionInteraction
*/
    ~GestionInteraction();

/**
 * @brief Méthode pour accéder à une Interaction dans listeInteraction
*/    
    Interaction getInteraction(int);

/**
 * @brief Méthode qui renvoie la taille de listeInteraction
*/   
    int getNbInteraction();

/**
 * @brief Méthode pour ajouter une Interaction à listeInteraction par ordre croissant des dates
*/
    void ajouterInteraction(Interaction);

/**
 * @brief Méthode pour supprimer une Interaction
*/
    void supprimerInteraction(int);


/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    std::string afficheListeInteraction();

};

#endif // GESTIONINTERACTION_H
