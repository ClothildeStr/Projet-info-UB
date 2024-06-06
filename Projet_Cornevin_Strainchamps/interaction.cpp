/**
 * @file interaction.cpp
 * @brief Définition des méthodes de la classe Interaction
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/

#include "interaction.h"

/**
 * @brief Constructeur de la classe Interaction, la date actuelle est remplie automatiquement
 * @param[in] c valeur initiale de l'attribut contenu
 * @param[in] GT valeur initiale de l'attribut noteTodo 
 */
Interaction::Interaction(std::string c, Date d, GestionTodo GT)
    :contenu(c), date(d),noteTodo(GT){
}

Interaction::~Interaction(){

}

/**
 * @brief Accesseur de l'attribut contenu
 * @return contenu la valeur de l'attribut contenu
 * @retval std::string le type de l'attribut contenu
 */
std::string Interaction::getContenu(){
    return contenu;
}

/**
 * @brief Accesseur de l'attribut date
 * @return date la valeur de l'attribut date
 * @retval Date le type de l'attribut date
 */
Date Interaction::getDate(){
    return date;
}

/**
 * @brief Mutateur de l'attribut contenu
 * @param[in] c nouvelle valeur de l'attribut contenu
 * @retval std::string le type de l'attribut contenu
 */
void Interaction::setContenu(std::string c){
    contenu = c;
}

/**
 * @brief Mutateur de l'attribut date
 * @param[in] j nouvelle valeur pour le jour de l'attribut date
 * @param[in] m nouvelle valeur pour le mois de l'attribut date
 * @param[in] a nouvelle valeur pour l'année de l'attribut date
 */
void Interaction::setDate(int j, int m, int a){
    date.setJour(j);
    date.setMois(m);
    date.setAnnee(a);
}


std::string Interaction::afficheInteraction(){
    std::string chaine = "";
    chaine = contenu + "\n" +
            "Date création: " +
            date.afficheDate()+"\n" +
                noteTodo.afficheListeTodo() + "\n";
    return chaine;
}
