/**
 * @file gestiontodo.cpp
 * @brief Définition des méthodes de la classe GestionTodo
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "gestiontodo.h"
#include <algorithm>
#include <string.h>

/**
 * @brief Constructeur par défaut de la classe GestionTodo
 */
GestionTodo::GestionTodo()
{
    std::vector<Todo> listeTodo;
}

/**
 * @brief Destructeur de la classe GestionTodo
 */
GestionTodo::~GestionTodo()
{

}
/**
 * @brief Méthode nous renvoyant un Todo 
 * @param[in] i position dans listeTodo
 * @return un Todo de listeTodo
 * @retval Todo
 */

Todo GestionTodo::getTodo(unsigned int i){
    return listeTodo[i];
}

/**
 * @brief Méthode nous renvoyant la taille de listeTodo 
 * @retval int
 */
int GestionTodo::getNbTodo(){
    return listeTodo.size();
}

/**
 * @brief Méthode pour ajouter un Todo à listeTodo par ordre croissant des dates
 * @param[in] t qui est le Todo que l'on veut ajouter
 */
void GestionTodo::ajouterTodo(Todo t){
    listeTodo.push_back(t);
    std::sort(listeTodo.begin(), listeTodo.end(),
                  []( Todo a,  Todo b) {
                      return a.getAtDate().getJour()+a.getAtDate().getMois()+ a.getAtDate().getAnnee() < b.getAtDate().getJour()+b.getAtDate().getMois()+ b.getAtDate().getAnnee();
                  });
}

std::string GestionTodo::afficheListeTodo(){
    std::string chaine = "";
    if(getNbTodo()==0){
        chaine = "Aucun todo dans la liste";
    }
    else{
        for(int i=0; i<getNbTodo(); i++){
             chaine = chaine + getTodo(i).afficheTodo() + "\n";
        }
    }
    return chaine;
}
