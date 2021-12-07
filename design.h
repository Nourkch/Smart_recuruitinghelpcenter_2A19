#ifndef DESIGN_H
#define DESIGN_H


#include <QFont>

class Design
{
public:
    QString titre;
    QString description;
    QString lien;
    QFont font;

public:
    Design();
    Design(const QString &titre,const QString &description,const QString &lien,const QFont &font);
};

#endif // DESIGN_H
