/**
 * @file gestiontodo.h
 * @brief Définition de la classe GestionTodo
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/

#ifndef GESTIONTODO_H
#define GESTIONTODO_H
#include <vector>
#include "todo.h"

/**  
 * @class Classe pour definir un objet de type GestionTodo
 * @param listeTodo liste de Todo
 *
*/
class GestionTodo
{
private:
    std::vector<Todo> listeTodo;
public:
/**
 * @brief Constructeur par défaut de la classe GestionTodo
*/
    GestionTodo();

/**
 * @brief Destructeur de la classe GestionTodo
*/
    ~GestionTodo();

/**
 * @brief Méthode pour accéder à un Todo dans listeTodo
*/
    Todo getTodo(unsigned int);

/**
 * @brief Méthode qui renvoie la taille de listeTodo
*/   
    int getNbTodo();

/**
 * @brief Méthode pour ajouter un Todo à listeTodo par ordre croissant des dates
*/
    void ajouterTodo(Todo);

/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    std::string afficheListeTodo();
};

#endif // GESTIONTODO_H
