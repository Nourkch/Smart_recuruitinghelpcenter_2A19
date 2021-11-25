#include "annonce.h"

Annonce::Annonce(){}
Annonce::Annonce(const Payment &pa, const Plan &pl, int id_emp)
    :payment(pa),
     plan(pl),
     m_id_emp(id_emp)
{

}


bool Annonce::sortByTitre(const Annonce &a1, const Annonce &a2){
    return a1.design.titre < a2.design.titre;
}

bool Annonce::asc_sortByDate(const Annonce &a1, const Annonce &a2){
    return  a1.plan.date_creation.daysTo(a2.plan.date_creation) < 0;
}

bool Annonce::desc_sortByDate(const Annonce &a1, const Annonce &a2){
    return  a1.plan.date_creation.daysTo(a2.plan.date_creation) > 0;
}

bool Annonce::asc_sortByDuree(const Annonce &a1, const Annonce &a2){
    return  a1.plan.nbr_jour < a2.plan.nbr_jour;
}

bool Annonce::desc_sortByDuree(const Annonce &a1, const Annonce &a2){
    return  a1.plan.nbr_jour > a2.plan.nbr_jour;
}
