/**
 * @file gestioninteraction.cpp
 * @brief Définition des méthodes de la classe GestionInteraction
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "gestioninteraction.h"
#include <algorithm>
#include <string.h>

/**
 * @brief Constructeur par défaut de la classe GestionInteraction
*/
GestionInteraction::GestionInteraction()
{

}

/**
 * @brief Destructeur de la classe GestionInteraction
 */
GestionInteraction::~GestionInteraction(){

}

/**
 * @brief Méthode nous renvoyant une Interaction 
 * @param[in] i position dans listeInteraction
 * @return une Interaction de listeInteraction
 * @retval Interaction
 */
Interaction GestionInteraction::getInteraction(int i){
    return listeInteraction[i];
}


/**
 * @brief Méthode nous renvoyant la taille de listeInteraction 
 * @retval int
 */
int GestionInteraction::getNbInteraction(){
    return listeInteraction.size();
}

/**
 * @brief Méthode pour ajouter une Interaction à listeInteraction par ordre croissant des dates
 * @param[in] i qui est l'Interaction que l'on veut ajouter
 */
void GestionInteraction::ajouterInteraction(Interaction i){
    listeInteraction.push_back(i);
    std::sort(listeInteraction.begin(), listeInteraction.end(),
                  []( Interaction a,  Interaction b) {
                      return a.getDate().getJour()+a.getDate().getMois()+ a.getDate().getAnnee() < b.getDate().getJour()+b.getDate().getMois()+ b.getDate().getAnnee();
                  });
}

void GestionInteraction::supprimerInteraction(int ind){
    if (ind < listeInteraction.size()) {
        // Suppression de l'interaction à l'indice indexToRemove
        listeInteraction.erase(listeInteraction.begin() + ind);
    }
}

std::string GestionInteraction::afficheListeInteraction(){
    std::string chaine = "";
    if(getNbInteraction()==0){
        chaine =  "liste interaction vide";
    }
    else{
        for(int i=0; i<getNbInteraction(); i++){
             chaine = chaine + getInteraction(i).afficheInteraction() + "\n";
        }
    }
    return chaine;
}
