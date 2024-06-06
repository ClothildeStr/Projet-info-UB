/**
 * @file todo.cpp
 * @brief Définition des méthodes de la classe Todo
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "todo.h"

/**
 * @brief Constructeur de la classe Todo
 * @param[in] atT la valeur initiale de l'attribut atTodo
 */
Todo::Todo(std::string atT)
    :atTodo(atT){
    atDate.donneDateActuelle();
}


/**
 * @brief Constructeur de la classe Todo.
 * @param[in] atT valeur de l'attribut atTodo
 * @param[in] j valeur pour le jour de l'attribut atDate
 * @param[in] m valeur pour le mois de l'attribut atDate
 * @param[in] a valeur pour l'année de l'attribut atDate
 */
Todo::Todo(std::string atT, int j, int m, int a)
    :atTodo(atT), atDate(j, m, a){
}

Todo::~Todo(){

}

/**
 * @brief Accesseur de l'attribut atTodo
 * @return atTodo la valeur de l'attribut atTodo
 * @retval std::string le type de l'attribut atTodo
 */
std::string Todo::getAtTodo(){
    return atTodo;
}

/**
 * @brief Accesseur de l'attribut atDate
 * @return atDate la valeur de l'attribut atDate
 * @retval Date le type de l'attribut atDate
 */
Date Todo::getAtDate(){
    return atDate;
}

/**
 * @brief Mutateur de l'attribut atTodo
 * @param[in] atT nouvelle valeur de l'attribut atTodo
 * @retval std::string le type de l'attribut atTodo
 */
void Todo::setAtTodo(std::string atT){
    atTodo = atT;
}

/**
 * @brief Mutateur de l'attribut atDate
 * @param[in] j nouvelle valeur pour le jour de l'attribut atDate
 * @param[in] m nouvelle valeur pour le mois de l'attribut atDate
 * @param[in] a nouvelle valeur pour l'année de l'attribut atDate
 */
void Todo::setAtDate(int j, int m, int a){
    atDate.setJour(j);
    atDate.setMois(m);
    atDate.setAnnee(a);
}

std::string Todo::afficheTodo(){
    std::string chaine = "@todo " + atTodo + " " + "@date " + atDate.afficheDate();
    return chaine;

}
