#include "plan.h"

Plan::Plan(int nbr_jour, const QString & cible,bool avecEmail, bool avecPopup, const QDate & date)
{
    this->nbr_jour=nbr_jour;
    this->cible=cible;
    this->avecEmail = avecEmail;
    this->avecPopup = avecPopup;
    this->date_email=date;
}

Plan::Plan(){}
