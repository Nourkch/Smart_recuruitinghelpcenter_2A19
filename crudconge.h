#ifndef CRUDCONGE_H
#define CRUDCONGE_H
#include "employe.h"

class CRUDconge
{
private :
    unsigned long long idConge;
    QString typeConge;
    QString loginEmploye;
    QString commentaireResponsable;
    QString commentaireEmploye;
    QString dateDebutConge;
    QString dateFinConge;
public:
    bool AjoutConge();
    bool ModifierConge();
    bool SupprimerConge();
    QSqlQueryModel *AfficherConge();
    bool RechercherConge(QString);
    CRUDconge();
    CRUDconge(QString, QString, QString, QString, QString,QString);
    void setIdConge(unsigned long long idConge)
    {
        this->idConge= idConge;
    }

    unsigned long long getIdConge()
    {
        return idConge;
    }

    void setTypeConge(QString typeConge)
    {
        this->typeConge = typeConge;
    }
    QString getTypeConge()
    {
        return typeConge;
    }

    void setLoginEmploye(QString loginEmploye)
    {
        this->loginEmploye=loginEmploye;;
    }
    QString getLoginEmploye()
    {
        return loginEmploye;
    }

    void setCommentaireResponsable
    (QString commentaireResponsable)
    {
        this->commentaireResponsable = commentaireResponsable;
    }
    QString getCommentaireResponsable()
    {
        return commentaireResponsable;
    }
    void setCommentaireEmploye
    (QString commentaireEmploye)
    {
        this->commentaireEmploye = commentaireEmploye;
    }
    QString getCommentaireEmploye()
    {
        return commentaireEmploye;
    }
    void setDateDebutConge(QString dateDebutConge)
    {
        this->dateDebutConge = dateDebutConge;
    }
    QString getDateDebutConge()
    {
        return dateDebutConge;
    }
    void setDateFinConge(QString dateFinConge)
    {
      this-> dateFinConge = dateFinConge;
    }
    QString getDateFinConge()
    {
        return dateFinConge;
    }
};

#endif // CRUDCONGE_H
