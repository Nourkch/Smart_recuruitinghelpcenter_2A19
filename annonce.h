#ifndef ANNONCE_H
#define ANNONCE_H

#include "./design.h"
#include "./payment.h"
#include "./plan.h"



class Annonce
{
public:
    Design design;
    Payment payment;
    Plan plan;
    int m_id_emp,id;

public:
    Annonce();
    Annonce(const Payment &pa, const Plan &pl, int id_emp);

    static bool sortByTitre(const Annonce &a1, const Annonce &a2);
    static bool asc_sortByDate(const Annonce &a1, const Annonce &a2);
    static bool desc_sortByDate(const Annonce &a1, const Annonce &a2);
    static bool asc_sortByDuree(const Annonce &a1, const Annonce &a2);
    static bool desc_sortByDuree(const Annonce &a1, const Annonce &a2);


};

#endif // ANNONCE_H
