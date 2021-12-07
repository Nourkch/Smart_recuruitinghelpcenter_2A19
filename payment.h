#ifndef PAYMENT_H
#define PAYMENT_H

#include "plan.h"

class Payment
{
public:
    double prix_brut;
    bool par_facilite;
    int nbr_mois;
    double avance;

public:
    Payment();
    Payment(double prix_brut,bool par_facilite,int nbr_mois,double avance);
    double calcPrixBrut(const Plan &p);
    double calcInterer() const;
};
#endif // PAYMENT_H
