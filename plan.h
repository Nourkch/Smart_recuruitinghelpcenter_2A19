#ifndef PLAN_H
#define PLAN_H


#include <QString>
#include <QDate>

class Plan
{
public:
    int nbr_jour;
    QString cible;
    bool avecEmail;
    bool avecPopup;
    QDate date_email;
    QDate date_creation;
    bool email_envoyee;

public:
    Plan();
    Plan(int nbr_jour, const QString & cible,bool avecEmail, bool avecPopup, const QDate & date);

};
#endif // PLAN_H
