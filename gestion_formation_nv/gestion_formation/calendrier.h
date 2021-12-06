#ifndef CALENDRIER_H
#define CALENDRIER_H
#include<QDate>
#include<QSqlQueryModel>

class calendrier
{
public:
    calendrier();
    calendrier(int,QDate,QString);
            int getide();
            QDate getdate_exam();
            QString gettemps();


            void setide(int);
            void setdate_exam(QDate);
            void settemps(QString);


            bool ajouter();
          QSqlQueryModel* afficher();
          bool update(int , QDate ,QString );
          bool supprimer(int);

        private:
            int ide;
            QDate date_exam;
            QString temps;
};

#endif // CALENDRIER_H
