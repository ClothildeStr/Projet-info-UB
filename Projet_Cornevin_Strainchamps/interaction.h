/**
 * @file interaction.h
 * @brief Définition de la classe Interaction
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#ifndef INTERACTION_H
#define INTERACTION_H

#include "date.h"
#include "gestiontodo.h"

/**  
 * @class Classe pour definir un objet de type GestionTodo
 * @param contenu chaine de caractères contenant des informations
 * @param date date de création de l'interaction
 * @param noteTodo liste de todo lié à l'interaction
 *
*/
class Interaction
{
private:
    std::string contenu;
    Date date;
    GestionTodo noteTodo;

public:
/**
 * @brief Constructeur de la classe Interaction
*/
    Interaction(std::string, Date,GestionTodo);

/**
 * @brief Destructeur de la classe Interaction
*/
    ~Interaction();

/**
 * @brief Accesseurs
 */
    std::string getContenu();
    Date getDate();

/**
 * @brief Mutateurs
 */
    void setContenu(std::string);
    void setDate(int, int, int);

/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    std::string afficheInteraction();

};

#endif // INTERACTION_H
