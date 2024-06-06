/**
 * @file date.h
 * @brief Définition de la classe Date
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#ifndef DATE_H
#define DATE_H
#include <iostream>
/**  
 * @class Classe pour definir un objet de type Date
 * @param jour qui est un entier
 * @param mois qui est un entier
 * @param annee qui est un entier
 *
*/
class Date
{
private:
    int  jour;
    int mois;
    int annee;
public:
/**
 * @brief Constructeur par défaut de la classe Date
*/
    Date();

/**
 * @brief Constructeur de la classe Date
*/
    Date(int, int, int);

/**
 * @brief Destructeur de la classe Date
*/
    ~Date();

/**
 * @brief Accesseurs
 */
    int getJour();
    int getMois();
    int getAnnee();

/**
 * @brief Mutateurs
 */
    void setJour(int);
    void setMois(int);
    void setAnnee(int);

/**
 * @brief Méthode qui vérifiera si l'utilisateur entrera une date réaliste
 */
    int dateValide();

/**
 * @brief Méthode qui donne la date d'aujourd'hui
 */
    void donneDateActuelle();

/**
 * @brief Méthode pour afficher la classe dans le terminal
 */
    std::string afficheDate();
};

#endif // DATE_H
