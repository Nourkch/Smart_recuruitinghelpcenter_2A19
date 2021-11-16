#include "payment.h"
#include <QDebug>

Payment::Payment()
{

}

Payment::Payment(double prix_brut,bool par_facilite,int nbr_mois,double avance){
    this->prix_brut = prix_brut;
    this->par_facilite = par_facilite;
    this->nbr_mois = nbr_mois;
    this->avance = avance;
}


double Payment::calcInterer() const{
    if(par_facilite)
        return (prix_brut - avance) * (nbr_mois * 0.2);
    else
        return 0;
}


double Payment::calcPrixBrut(const Plan &p){
    double prix = 500;

    if(p.cible == "tous")
        prix += 100;


    prix+= (p.nbr_jour-15) * 10;

    prix+= p.avecEmail * 200;
    prix+= p.avecPopup * 100;


    prix_brut = prix;

    return  prix_brut;
}
