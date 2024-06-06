/**
 * @file todo.h
 * @brief Définition de la classe Todo
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/

#ifndef TODO_H
#define TODO_H

#include "date.h"

/**  
 * @class Classe pour definir un objet de type Todo
 * @param[in] atTodo  Chaine de caractères permettant de stocker un todo
 * @param[in] atDate  Objet de type Date permettant de stocker une date pour un todo
 *
*/
class Todo
{
private:
/**
 * @brief Attributs de la classe
 */
    std::string atTodo;
    Date atDate;
public:
/**
 * @brief Constructeur de la classe Todo ou la date est initialiser avec la date actuelle par défaut
*/
Todo(std::string);


/**
 * @brief Constructeur de la classe Todo en initialisant la date
*/
    Todo(std::string, int j, int m, int a);

/**
 * @brief Destructeur de la classe Todo
*/
    ~Todo();
/**
 * @brief Accesseurs
 */
    std::string getAtTodo();
    Date getAtDate();

/**
 * @brief Mutateurs
 */
    void setAtTodo(std::string);
    void setAtDate(int, int, int);

/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    std::string afficheTodo();

};

#endif // TODO_H
