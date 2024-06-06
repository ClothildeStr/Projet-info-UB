/**
 * @file date.cpp
 * @brief Définition de la classe Date
 * @author Camille CORNEVIN, Clothilde STRAINCHAMPS
 * @version 1.0
 * @date 27/10/2023
*/
#include "date.h"
#include <time.h>
#include <iostream>

/**
 * @brief Constructeur par défaut de la classe Date et l'initialise au 1/1/2000 
 */
Date::Date()
{
    jour = 1;
    mois = 1;
    annee = 2000;
}

/**
 * @brief Constructeur de la classe Date
 * @param[in] j valeur initiale de l'attribut jour
 * @param[in] m valeur initiale de l'attribut mois 
 * @param[in] a valeur initiale de l'attribut annee
 */
Date::Date(int j, int m, int a)
{
    jour = j;
    mois = m;
    annee = a;
}

Date::~Date(){

}

/**
 * @brief Accesseur de l'attribut jour
 * @return jour la valeur de l'attribut jour
 * @retval int le type de l'attribut jour
 */
int Date::getJour(){
    return jour;
}

/**
 * @brief Modificateur de l'attribut jour
 * @param[in] j nouvelle valeur de l'attribut jour
 */
void Date::setJour(int j){
    jour = j;
}

int Date::getMois(){
    return mois;
}
void Date::setMois(int m){
    mois = m;
}

int Date::getAnnee(){
    return annee;
}
void Date::setAnnee(int a){
    annee = a;
}


/**
 * @brief Méthode qui vérifiera si l'utilisateur entrera une date réaliste
 * @return 0 la date est invalide, 1 la date est valide
 * @retval int
 */
int Date::dateValide(){
        if (annee < 0 || mois < 1 || mois > 12 || jour < 1) {
            return 0; // année négative, mois ou jour hors limites -> date invalide
        }

        // nombre de jours par mois (sans tenir compte des années bissextiles)
        const int jour_dans_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // vérification du nombre de jours pour le mois et l'année donnés
        unsigned int max_jours = jour_dans_mois[jour - 1];
        if (mois == 2 && ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0)) {
            max_jours = 29; // année bissextile -> février a 29 jours
        }
        if (jour > max_jours) {
            return 0; // jour invalide pour le mois et l'année donnés -> date invalide
        }

        struct tm date = {0};
        date.tm_year = annee - 1900; // l'année doit être exprimée en nombre d'années depuis 1900
        date.tm_mon = mois - 1; // le mois doit être exprimé entre 0 et 11
        date.tm_mday = jour;

        time_t time = mktime(&date);
        if (time == -1) {
            return 0; // conversion en temps calendrier impossible -> date invalide
        }
        struct tm *result = localtime(&time);
        if (result->tm_year != date.tm_year || result->tm_mon != date.tm_mon || result->tm_mday != date.tm_mday) {
            return 0; // date modifiée pendant la conversion -> date invalide
        }

        return 1; // date valide
    }

/**
 * @brief Méthode qui donne la date d'aujourd'hui

 */
void Date::donneDateActuelle(){
    // Obtenir la date et l'heure actuelles
        time_t now = time(0);
        tm *ltm = localtime(&now);

    // Avoir la date d'aujourd'hui
    annee = 1900 + ltm->tm_year;
    mois = 1 + ltm->tm_mon;
    jour = ltm->tm_mday;

}

std::string Date::afficheDate(){
    std::string chaine = std::to_string(getJour()) + "/" + std::to_string(getMois()) + "/" + std::to_string(getAnnee());
    return chaine;

}
