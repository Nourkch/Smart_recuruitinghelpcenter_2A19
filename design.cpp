#include "design.h"

Design::Design()
{

}

Design::Design(const QString &titre,const QString &description,const QString &lien,const QFont &font){
    this->titre=titre;
    this->description=description;
    this->lien=lien;
    this->font=font;
}
