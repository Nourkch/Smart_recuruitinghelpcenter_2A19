#include "app.h"
#include "ui_app.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include "candidats.h"
#include "mainwindow.h"
#include <QMessageBox>

app::app(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::app)
{
    ui->setupUi(this);

    QPixmap background("C:/Users/Raider/Desktop/INTEGRATION/Atelier_Connexion/resources/back12.jpg");
    ui->label_background_app->setPixmap(background);


/*
    QPixmap pic("C:/Users/Raider/Desktop/INTEGRATION/Atelier_Connexion/resources/pic1.jpg");
    ui->label_picAcceuilApp->setPixmap(pic); */

}

app::~app()
{
    delete ui;
}



void app::on_pushbutton_browser_clicked()
{
        QString link = "http://www.google.com";
        QDesktopServices::openUrl(QUrl(link));
}


void app::on_pushButton_listeCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void app::on_pushButton_ajoutCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void app::on_pushButton_cancelAjoutCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void app::on_pushButton_validerAjoutCandidat_clicked()
{

    QString prenom = ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();

    QDate date_naissance=ui->dateEdit_datenaissance->date();

    QString rue=ui->lineEdit_rue->text();
    int codepostal=ui->lineEdit_codePostal->text().toInt();
    int cin = ui->lineEdit_cin->text().toInt();

    QString sexe=ui->comboBox_genre->currentText();

    QString email=ui->lineEdit_email->text();

  QString ville = ui->comboBox_ville->currentText();

 candidats c (cin,nom,prenom,email,sexe,rue,codepostal,date_naissance,ville);

  bool index ;


index = c.ajouter_candidat();

// mSystemTrayIcon->showMessage(tr("notification"),tr("ajout avec succes"));


  /*if (index==true)
     {

      QMessageBox::information(nullptr, QObject::tr("Ajouter un candidat"),
                  QObject::tr("Candidat ajouté avec succès.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

      ui->stackedWidget->setCurrentIndex(1);

} */

ui->stackedWidget->setCurrentIndex(1);

}

void app::on_pushButton_precedent_ajoutCandidat_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void app::on_pushButton_supprimerCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_CANDIDAT from CANDIDAT ");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_id_supprimerCandidat->setModel(modal);
}


void app::on_pushButton_2_clicked()   // valider la suppression d'un candidat
{
    QMessageBox::StandardButton reply;

     reply = QMessageBox::question(this, "Supprimer un candidat ", "Etes-vous sur de la suppression?",
                                   QMessageBox::Yes|QMessageBox::No);

     if (reply == QMessageBox::Yes) {
       qDebug() << "Yes was clicked";

       int id = ui->comboBox_id_supprimerCandidat->currentText().toInt();

     bool test=tabCandidat.supprimer_candidat(id);

    // mSystemTrayIcon->showMessage(tr("notification"),tr("suppression faite avec succes"));

     /*if (test)
     {
         QMessageBox::information(nullptr, QObject::tr("Supprimer un candidat"),
                     QObject::tr("Candidat supprimé avec succès .\n"
                                 "Click Ok to exit."), QMessageBox::Ok);
       }
       */

ui->stackedWidget->setCurrentIndex(1);
  }
}


void app::on_pushButton_precedentCandidatSupprimer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void app::on_pushButton_precedent_Candidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void app::on_pushButton_annuler_suppCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void app::on_pushButton_modifierCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_CANDIDAT from CANDIDAT ");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_id_modifierCandidat->setModel(modal);
}



void app::on_pushButton_valider_modifCandidat_clicked()
{
    int id=ui->comboBox_id_modifierCandidat->currentText().toInt();

     QString nom = ui->lineEdit_modif_nom->text();

     QString prenom = ui->_modif_prenom->text();

     QDate date_naissance=ui->dateEdit_modif_dateNaissance->date();

     QString rue=ui->lineEdit_modif_rue->text();

     int codepostal=ui->lineEdit_modif_codePostal->text().toInt();

     int cin = ui->lineEdit_modif_cin->text().toInt();

     QString sexe=ui->comboBox_genre_modif->currentText();

     QString email=ui->lineEdit_modif_email->text();

   QString ville = ui->comboBox_modif_ville->currentText();


      candidats c (id,cin,nom,prenom,email,sexe,rue,codepostal,date_naissance,ville);

            QMessageBox::StandardButton reply;

             reply = QMessageBox::question(this, "CANDIDAT ", "modifier?",
                                           QMessageBox::Yes|QMessageBox::No);

 if (reply == QMessageBox::Yes)
             {

            bool test=c.modifier_candidat();

             // mSystemTrayIcon->showMessage(tr("notification"),tr("modification faite avec succes"));

            qDebug()<<id;
/*
            if (test)
            {

                QMessageBox::information(nullptr, QObject::tr("Modifier un candidat"),
                            QObject::tr("Candidat modifié avec succès.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

                ui->stackedWidget->setCurrentIndex(0);

            } */


             ui->stackedWidget->setCurrentIndex(1);

             }
}

void app::on_pushButton_precendent_modifCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void app::on_pushButton_precedentajoutCandidat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void app::on_pushButton_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ");  //  * : everything
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);

    //mSystemTrayIcon->showMessage(tr("notification"),tr("affichage fait avec succes")); // notification sys // zid l cruds lokhrin
}

void app::on_pushButton_chercherCandidat_clicked()
{
    QString chercher = ui->lineEdit_chercherCandidat->text();

   QString prenom;

              if((chercher !=  ""))
              {
                  QSqlQuery q;
                  QSqlQueryModel *modal=new QSqlQueryModel();

                  if(chercher != "")
                  {
                  q.prepare("select * from CANDIDAT where prenom like '%"+chercher+"%' ");
                  q.bindValue(":prenom",chercher);
                  q.exec();
                  modal->setQuery(q);

                  ui->tabCandidat->setModel(modal);

              }
              else
              {
                  QMessageBox::warning(this,"Erreur", "recherche invalide ");
              }
}
}

void app::on_pushButton_triASC_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ORDER BY prenom ASC ");
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);
}



void app::on_pushButton_triDESC_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select * from CANDIDAT ORDER BY prenom DESC ");
    q.exec();
    modal->setQuery(q);
    ui->tabCandidat->setModel(modal);
}

////////////////////////////////////////////////////////: ARMEN

void app::on_pushButton_Sponsoring_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void app::on_pushButton_precedentAnnonces_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void app::on_logo_khadamni_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void app::on_pushButton_creerAnnonce_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void app::creerDesign(){
    QString titre= ui->input_titre_annonce->text();
    QString description = ui->input_description_annonce->text();
    QFont font = ui->comboBox_font_annonce->currentFont();
    QString lien="";

    if(a.design.lien!="")
        lien=a.design.lien;

    Design d(titre, description, lien, font);

    a.design = d;

}



void app::on_suiv_creer_annonce_clicked()
{
    ui->tabAnnonces->setCurrentIndex(1);
}



void app::creerPlan(){
    QString cible;
    int nbr_jour;
    bool avecEmail=false;
    bool avecPopup=false;
    QDate date_email;

    if(ui->tout_les_candidat_annonce->isChecked())
        cible="tous";
    else
        cible=ui->comboBox_competance_annonce->currentText();

    nbr_jour=ui->comboBox_nbrJour_annonce->currentText().toInt();

    if(ui->email_oui_annonce->isChecked())
    {
        date_email = ui->date_email_annonce->date();
        avecEmail=true;
    }

    if(ui->popup_oui_annonce->isChecked())
        avecPopup=true;

    a.plan = Plan(nbr_jour, cible, avecEmail, avecPopup, date_email);
}



void app::on_prec_creer_annoncePlan_clicked()
{
    ui->tabAnnonces->setCurrentIndex(0);
}


void app::on_suiv_creer_annoncePlan_clicked()
{
    ui->tabAnnonces->setCurrentIndex(2);
}


void app::on_pushButton_prec_payment_clicked()
{
    ui->tabAnnonces->setCurrentIndex(1);
}



void app::on_pushButton_suiv_payement_clicked()
{
    ui->tabAnnonces->setCurrentIndex(3);
}


void app::creerPayment(){

    double prix_brut = 0;
    bool par_facilite = ui->facilite_oui_annonce->isChecked();
    int nbr_mois = ui->comboBox_nbrMois_annonce->currentText().toInt();
    double avance = ui->avance_annonce->text().toDouble();


    Payment pa(prix_brut,par_facilite,nbr_mois,avance);

    pa.calcPrixBrut(a.plan);

    a.payment = pa;
}



void app::on_pushButton_selectionner_image_annonce_clicked()
{
    QString  fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    a.design.lien=fileName;

    ui->label_image_path_annonce->setText(fileName);

    QPixmap image(fileName);

    ui->background_annonce->setPixmap(image);
    ui->background_annonce->setScaledContents(true);
    ui->background_annonce->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->background_annonce->setMinimumSize(500, 160);
    ui->background_annonce->resize(500, 320);
    ui->background_annonce->setAlignment(Qt::AlignCenter);
}



void app::on_pushButton_trouver_image_annonce_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.canva.com/announcements/templates/job-vacancy/"));
}




void app::on_Confirmer_annonce_clicked()
{
    QSqlQuery q;

    /////////////////// AUTH ///////////////////
    QString email = ui->input_email_annonce->text();
    QString mdp = ui->input_mdp_annonce->text();


    if(email.isEmpty())
        QMessageBox::critical(nullptr,
                              QObject::tr("Failed to Authenticate"),
                              QObject::tr("Email est vide"),
                              QMessageBox::Ok);
    else if(mdp.isEmpty())
        QMessageBox::critical(nullptr,
                              QObject::tr("Failed to Authenticate"),
                              QObject::tr("Mot de pass est vide"),
                              QMessageBox::Ok);

    q.prepare("select * from EMPLOYERS where (adresse_mail = :email AND mot_de_passe = :mdp);");

    q.bindValue(":email", email);
    q.bindValue(":mdp", mdp);

    q.exec();


    if (q.next()) {
        a.m_id_emp = q.value(0).toInt();
    }
    else{
        QMessageBox::critical(nullptr,
                              QObject::tr("Failed to Authenticate"),
                              QObject::tr("Email ou mot de passe incorrecte"),
                              QMessageBox::Ok);
    }
    /////////////////////////////////////////////////////////////////

    ///////////////////////// INSERT ///////////////////////////
    creerDesign();
    creerPlan();
    creerPayment();

    q.prepare("INSERT INTO annonces (DUREE, PRIX_BRUT, FACILITE, NBR_MOIS, AVANCE, CIBLE, MAIL_DATE, TITRE, DESCRIP,LIEN_DESIGN,ID_EMPLOYER)"
              "VALUES (:duree,:prix_brut,:facilite,:nbr_mois,:avance,:cible,TO_Date(:date,'DD/MM/YYYY'),:titre,:description,:lien,:id_emp);");

    q.bindValue(":duree", a.plan.nbr_jour);
    q.bindValue(":prix_brut", a.payment.prix_brut);
    q.bindValue(":facilite", (int)a.payment.par_facilite);
    q.bindValue(":nbr_mois", a.payment.nbr_mois);
    q.bindValue(":avance", a.payment.avance);
    q.bindValue(":cible", a.plan.cible);
    q.bindValue(":titre", a.design.titre);
    q.bindValue(":description", a.design.description);
    q.bindValue(":lien", a.design.lien);
    q.bindValue(":id_emp", a.m_id_emp);

    QString date;
    if(a.plan.avecEmail==true)
    {
        int d,m,y;
        a.plan.date_email.getDate(&y,&m,&d);
        date.append(QString::number(d)).append('/')
                .append(QString::number(m)).append('/')
                .append(QString::number(y));
    }else{
        date.append("01/01/1950");
    }

    q.bindValue(":date", date);

    if(q.exec())
        QMessageBox::information(nullptr,
                                 QObject::tr("Success"),
                                 QObject::tr("Annonce creer"),
                                 QMessageBox::Ok);

    else
        QMessageBox::critical(nullptr,
                              QObject::tr("Error"),
                              QObject::tr("information manquante"),
                              QMessageBox::Ok);

    /////////////////////////////////////////////////////////////////

}

void app::on_tout_les_candidat_annonce_clicked()
{
    ui->label_competences_annoncesPlan->hide();
    ui->comboBox_competance_annonce->hide();
}


void app::on_candidat_precis_annonce_clicked()
{
    ui->label_competences_annoncesPlan->show();
    ui->comboBox_competance_annonce->show();
}





void app::on_email_oui_annonce_clicked()
{
  ui->date_email_annonce->show();
}

void app::on_email_non_annonce_clicked()
{
     ui->date_email_annonce->hide();
}




void app::on_calcul_prix_annonce_clicked()
{
    creerPlan();
    creerPayment();

    int prix_total = a.payment.prix_brut + a.payment.calcInterer();

    ui->label_prixTotal_annonce->setText(QString("Prix Total: ").append(QString::number(prix_total)).append((" DT")));
}



void app::filtre(){



    filtredResult.erase(filtredResult.begin(),filtredResult.end());

    ////////////////////////////////// TITRE //////////////////////////////////
    if(filtre_index==0){

        QList<Annonce>::iterator it = qResult.begin();
        if(filtre_val!=""){
            while (it!=qResult.end()) {
                if(filtre_val.contains(it->design.titre) || it->design.titre.contains(filtre_val))
                    filtredResult.push_back(*it);
                it++;
            }
        }
        else{
            while(it!=qResult.end()){
                filtredResult.push_back(*it);
                it++;
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////// STATUS //////////////////////////////////
    if(filtre_index==1){

        QDate dNow(QDate::currentDate());
        QList<Annonce>::iterator it = qResult.begin();
        if(filtre_val== "active"){
            while (it!=qResult.end()) {
                if(it->plan.date_creation.daysTo(dNow) <= it->plan.nbr_jour)
                {
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }else if(filtre_val == "non-active"){
            while (it!=qResult.end()) {
                if(it->plan.date_creation.daysTo(dNow) >= it->plan.nbr_jour)
                {
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }
        else{
            while (it!=qResult.end()) {
                filtredResult.push_back(*it);
                it++;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////// DATE CREATION > //////////////////////////////////
    if(filtre_index == 2){
        QList<Annonce>::iterator it = qResult.begin();
        QDate dateMin = QDate::fromString(filtre_val, "dd/MM/yyyy");

        if(dateMin.isValid()){
            while (it!=qResult.end()) {
                if(dateMin.daysTo(it->plan.date_creation) >= 0){
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }else{
            while (it!=qResult.end()) {
                filtredResult.push_back(*it);
                it++;
            }
        }

    }
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////// DATE CREATION < //////////////////////////////////
    if(filtre_index == 3){
        QList<Annonce>::iterator it = qResult.begin();
        QDate dateMax = QDate::fromString(filtre_val, "dd/MM/yyyy");
        if(dateMax.isValid()){
            while (it!=qResult.end()) {
                if(dateMax.daysTo(it->plan.date_creation) <= 0){
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }else{
            while (it!=qResult.end()) {
                filtredResult.push_back(*it);
                it++;
            }
        }

    }
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////// DUREE > //////////////////////////////////
    if(filtre_index == 4){
        bool is_number;
        int jours = filtre_val.toInt(&is_number);
        QList<Annonce>::iterator it = qResult.begin();

        if(is_number){
            while (it!=qResult.end()) {
                if(it->plan.nbr_jour >= jours){
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }else{
            while (it!=qResult.end()) {
                filtredResult.push_back(*it);
                it++;
            }
        }

    }
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////// DUREE < //////////////////////////////////
    if(filtre_index == 5){
        bool is_number;
        int jours = filtre_val.toInt(&is_number);
        QList<Annonce>::iterator it = qResult.begin();

        if(is_number){
            while (it!=qResult.end()) {
                if(it->plan.nbr_jour <= jours){
                    filtredResult.push_back(*it);
                }
                it++;
            }
        }else{
            while (it!=qResult.end()) {
                filtredResult.push_back(*it);
                it++;
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////
}


void app::on_pushButton_consulterAnnonces_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void app::trie(){


    if(tri_index==0)
    {
        qSort(filtredResult.begin(),filtredResult.end(),Annonce::sortByTitre);
    }
    else if(tri_index==1)
    {
        qSort(filtredResult.begin(),filtredResult.end(),Annonce::asc_sortByDate);
    }
    else if(tri_index==2)
    {
        qSort(filtredResult.begin(),filtredResult.end(),Annonce::desc_sortByDate);
    }
    else if(tri_index==3)
    {
        qSort(filtredResult.begin(),filtredResult.end(),Annonce::asc_sortByDuree);
    }
    else if(tri_index==4)
    {
        qSort(filtredResult.begin(),filtredResult.end(),Annonce::desc_sortByDuree);
    }

}


void app::display(){

    if ( ui->scrollArea->layout() != NULL )
    {
        QLayoutItem *item;
        while ( ( item = ui->scrollArea->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete  ui->scrollArea->layout();
    }




    QVBoxLayout *scroll_layout = new QVBoxLayout(ui->scrollArea);

    for(const Annonce &a : filtredResult){

        int prix = a.payment.prix_brut + a.payment.calcInterer();
        QString objectName = "annonce_" + QString::number(a.id);
        QString style = "#" +objectName + "{"
                                          "border: 1px solid black;"
                                          "background-color:rgb(240,240,245);"
                                          "}";
        QString titre_val= "Titre: " + a.design.titre;
        QString cible_val= "Cible: " + a.plan.cible;
        QString duree_val= "duree: " + QString::number(a.plan.nbr_jour) + " jours";
        QString prixTotal_val= "Prix Total: " + QString::number(prix) + " DT";


        QWidget *annonce = new QWidget(ui->scrollArea);

        QVBoxLayout *layout = new QVBoxLayout(annonce);
        QLabel *title=new QLabel(annonce);
        QLabel *cible=new QLabel(annonce);
        QLabel *duree=new QLabel(annonce);
        QLabel *prixTotal=new QLabel(annonce);
        QPushButton *supprimer = new QPushButton(annonce);


        title->setText(titre_val);
        cible->setText(cible_val);
        duree->setText(duree_val);
        prixTotal->setText(prixTotal_val);

        supprimer->setText("supprimer");
        supprimer->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        supprimer ->setMaximumSize(150,50);
        supprimer->setContentsMargins(0,30,0,0);

        QSignalMapper* signalMapper = new QSignalMapper (this);
        connect(supprimer, SIGNAL(clicked()), signalMapper, SLOT(map()));

        signalMapper -> setMapping(supprimer,a.id);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(deleteAnnonce(int)));


        layout->addWidget(title);
        layout->addWidget(cible);
        layout->addWidget(duree);
        layout->addWidget(prixTotal);
        layout->addWidget(supprimer);


        annonce->setLayout(layout);
        annonce->setObjectName(objectName);
        annonce->setStyleSheet(style);
        annonce->setMinimumSize(300,100);


        scroll_layout->addWidget(annonce);
    }
    QSpacerItem *vspacer= new QSpacerItem(40,20,QSizePolicy::Fixed, QSizePolicy::Expanding);
    scroll_layout->addItem(vspacer);


    ui->scrollArea->setLayout(scroll_layout);
    ui->scrollArea->adjustSize();

}





void app::on_pushButton_statAnnonces_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void app::prepareChartData(QVector<int> &data ,QStringList &categories){


    QSqlQuery q;
    q.prepare("select * from annonces");
    q.exec();

    if(ui->echelle->currentIndex()==0)
    {
        data.fill(0,5);

        while(q.next()){
            QDate date =q.value(2).toDate();
            data[(date.day()-1)/7]++;
        }
        data[3]+=data[4];
        data.pop_back();

        categories << "s1" << "s2" << "s3" << "s4";
    }
    else if(ui->echelle->currentIndex()==1){
        data.fill(0,12);

        while (q.next()) {
            QDate date = q.value(2).toDate();
            data[date.month()-1]++;
        }

        categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sept" << "Oct" << "Nov" << "Dec";
    }
    else if(ui->echelle->currentIndex()==2){
        QDate dNow(QDate::currentDate());
        int curr_year=dNow.year();
        data.fill(0,5);

        while (q.next()) {
            QDate date = q.value(2).toDate();
            int index = 2 -  curr_year   + date.year();
            if(index >= 0 && index <= 4){
                data[index]++;
            }
        }

        categories << QString::number(curr_year-2) << QString::number(curr_year-1) <<QString::number(curr_year)
                   << QString::number(curr_year+1) <<QString::number(curr_year+2);

    }


}

void app::constructChart(){
    QVector<int> data;
    QStringList categories;
    prepareChartData(data,categories);

    QBarSet *set0 = new QBarSet("Annonce Cree");
    for (int i=0; i<data.size();i++) {
        *set0 << data[i];
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Annonce Cree");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,7);
    axisY->setTickCount(8);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);

    if ( ui->bar_chart->layout() != NULL )
    {
        QLayoutItem *item;
        while ( ( item = ui->bar_chart->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete  ui->bar_chart->layout();
    }

    QHBoxLayout *chart_layout = new QHBoxLayout(ui->bar_chart);
    chart_layout->addWidget(chartView);
    ui->bar_chart->setLayout(chart_layout);
    ui->bar_chart->adjustSize();
}



void app::on_tabWidget_currentChanged(int index)
{
    if(index==1){

        qResult.erase(qResult.begin(),qResult.end());

        Annonce a;
        QSqlQuery q;

        q.prepare("SELECT * FROM annonces");
        q.exec();

        while(q.next()){
            a.id = q.value(0).toInt();
            a.m_id_emp = q.value(12).toInt();

            a.design.titre = q.value(9).toString();
            a.design.description = q.value(10).toString();
            a.design.lien = q.value(11).toString();

            a.plan.cible = q.value(7).toString();
            a.plan.nbr_jour = q.value(1).toInt();
            a.plan.date_creation = q.value(2).toDate();
            a.plan.email_envoyee = q.value(13).toBool();
            if(q.value(8).toDate().year() == 1950)
                a.plan.avecEmail = false;
            else{
                a.plan.avecEmail= true;
                a.plan.date_email = q.value(8).toDate();
            }

            a.payment.prix_brut = q.value(3).toDouble();
            if(q.value(5).toInt()==1){
                a.payment.par_facilite = true;
                a.payment.nbr_mois = q.value(5).toInt();
                a.payment.avance = q.value(6).toDouble();
            }
            else
                a.payment.par_facilite = false;

            qResult.push_back(a);

        }

        filtre();
        trie();
        display();

    }else if(index == 2){
        constructChart();
    }
}


void app::deleteAnnonce(int id){
    QSqlQuery q;
    q.prepare("delete from annonces where id_annonce = :id ;");
    q.bindValue(":id",id);

    if(q.exec())
        QMessageBox::information(nullptr,
                                 QObject::tr("Success"),
                                 QObject::tr("Annonce suprimer"),
                                 QMessageBox::Ok);

    else
        QMessageBox::critical(nullptr,
                              QObject::tr("Error"),
                              QObject::tr("Annonce introuvable"),
                              QMessageBox::Ok);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(1);

}










void app::on_comboBox_6_currentIndexChanged(int index)
{
    if(index == 0){
        ui->filtre_val->setPlaceholderText("titre");
    }
    else if(index == 1){
        ui->filtre_val->setPlaceholderText("active ou non-active");
    }
    else if(index == 2 || index == 3 )
    {
        ui->filtre_val->setPlaceholderText("dd/mm/yyyy");
    }
    else if(index == 3 || index == 4 )
    {
        ui->filtre_val->setPlaceholderText("nombre de jours");
    }

    filtre_index= index;
    filtre();
    trie();
    display();
}



void app::on_comboBox_7_currentIndexChanged(int index)
{
    tri_index = index;
    filtre();
    trie();
    display();
}



void app::on_filtre_val_textChanged(const QString &arg1)
{
    filtre_val=arg1;
}

void app::on_filtre_val_editingFinished()
{
    filtre();
    trie();
    display();
}


void app::sendEmails(){

    QDate dNow(QDate::currentDate());
    QTime time(QTime::currentTime());
    QList<Annonce>::iterator it=qResult.begin();

    while (it!=qResult.end()) {
        if(!it->plan.email_envoyee && it->plan.avecEmail){
            if(it->plan.date_email.daysTo(dNow) >= 0 && time.hour() >= 8){
                QSqlQuery q;
                QStringList files;
                files.push_back(it->design.lien);


                if(it->plan.cible == "tous")
                {
                    q.prepare("select * from candidats");
                }else{
                    q.prepare("select * from candidats where competance = :competance ;");
                    q.bindValue(":competance" , it->plan.cible);
                }
                if(q.exec()){
                    while(q.next()){
                        Smtp *smtp = new Smtp("khadamni2a19@gmail.com","Khedma_aman_2021","smtp.gmail.com");
                        smtp->sendMail("khadamni2a19@gmail.com",q.value(5).toString(),it->design.titre,it->design.description,files);
                    }
                }

                q.prepare("UPDATE ANNONCES SET EMAIL_ENVOYEE = 1 WHERE ID_ANNONCE = :id;");
                q.bindValue(":id", it->id);
                q.exec();
            }
        }
        it++;
    }

}


void app::on_echelle_currentIndexChanged(int index)
{
     constructChart();
}



void app::on_pushButton_imprimer_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

     QWidget *w= ui->bar_chart;

     QPrinter printer(QPrinter::HighResolution);
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName(fileName);
     QPainter painter(&printer);

     double xscale = printer.pageRect().width() * 1.0 / w->width();
     double yscale = printer.pageRect().height() * 1.0 / w->height();
     double scale = (xscale < yscale ? xscale : yscale);

     painter.translate(printer.paperRect().center());
     painter.scale(scale,scale);
     painter.translate(-w->width()/2,-w->height()/2);

     ui->bar_chart->render(&painter);
     painter.end();

}

void app::on_pushButton_annulerCreationAnnonce_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void app::on_pushButton_precedentConsulterAnnonces_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void app::on_pushButton_PrecendentStatAnnonces_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

/////////////////////////////////////////////////////: EYA
///
///
///




void app::on_pushButton_listeEmployers_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void app::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




/////////////////////////////////////////////////////: Yasmine Mseddi
///
///
///


void app::on_pushButton_Factures_clicked()
{
   ui->stackedWidget->setCurrentIndex(10);
}


void app::on_pb_precedent_finance_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

/////////////////////////////////////////////////////////////////

///////////////////////// Ajout ///////////////////////////
void app::on_pb_ajouter_clicked()
{
    notification n ;

    int id=ui->id_lineEdit->text().toInt();
    int salaire=ui->salaire_lineEdit_4->text().toInt();
    int telephone=ui->tele_lineEdit_5->text().toInt();
    QString nom=ui->nom_lineEdit_2->text();
    QString prenom=ui->prenom_lineEdit_3->text();
    QString adress=ui->adress_lineEdit_6->text();

    finance f(nom,prenom,telephone,id,salaire,adress);
    bool test=f.ajouter();
     if(test)
      {
       n.notification_ajoute();
         QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                    QObject::tr("ajout successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tableView->setModel(f.afficher());

                }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                    QObject::tr("ajout failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
}
/////////////////////////////////////////////////////////////////

///////////////////////// Supprimer ///////////////////////////
void app::on_pb_supprimer_clicked()
{
    notification n ;
      finance f;
          f.setid(ui->comboBox->currentText().toInt());
          bool test;
          test=f.supprimer(f.getid());
          if(test)
           {
              n.notification_supprimer();

              QMessageBox::information(nullptr, QObject::tr("supp avec succes"),
                                         QObject::tr("sup successful.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);

      ui->tableView->setModel(f.afficher());
                     }
                         else
                             QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                         QObject::tr("sup failed.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);


}

/////////////////////////////////////////////////////////////////

///////////////////////// Load ///////////////////////////
void app::on_pb_load_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT id from finace");
             query->exec();
             model->setQuery(*query);
             ui->comboBox->setModel(model);
}
/////////////////////////////////////////////////////////////////

///////////////////////// Modifier ///////////////////////////
void app::on_pb_modifier_clicked()
{
    notification n ;
      int id=ui->id_lineEdit->text().toInt();
          QString nom=ui->nom_lineEdit_2->text();
          QString prenom=ui->prenom_lineEdit_3->text();
          QString adress=ui->adress_lineEdit_6->text();

          int telephone=ui->tele_lineEdit_5->text().toInt();

            int salaire=ui->salaire_lineEdit_4->text().toInt();


 finance f(nom,prenom,telephone,id,salaire,adress);

          bool test=f.modifier(f.getnom(),f.getprenom(),f.gettelephone(),f.getid(),f.getsalaire(),f.getadress());

          QMessageBox msgBox;

          if(test)
              {
              n.notification_modifier();

                  msgBox.setText("Modification avec succes.");
                  ui->tableView->setModel(f.afficher());
              }
          else
              msgBox.setText("Echec de Modification!!!!!!");
              msgBox.exec();
}
/////////////////////////////////////////////////////////////////

///////////////////////// Tri id ///////////////////////////
void app::on_pb_trier_id_clicked()
{
    finance f;
      ui->tableView->setModel(f.trier());
}
/////////////////////////////////////////////////////////////////

///////////////////////// Tri nom ///////////////////////////
void app::on_pb_trier_nom_clicked()
{
    finance f;
      ui->tableView->setModel(f.trier1());
}
/////////////////////////////////////////////////////////////////

///////////////////////// Tri Prenom ///////////////////////////
void app::on_pb_trier_prenom_clicked()
{
    finance f;
      ui->tableView->setModel(f.trier2());
}
/////////////////////////////////////////////////////////////////

///////////////////////// Recherche ///////////////////////////
void app::on_pb_rechercher_clicked()
{
    finance f;
    QString rech=ui->rech->text();
    if (rech=="")
     ui->tableView->setModel(f.afficher());
    else
        ui->tableView->setModel(f.rechercher(rech));
}

/////////////////////////////////////////////////////////////////

///////////////////////// PDF ///////////////////////////
void app::on_pb_pdf_clicked()
{
    QPdfWriter pdf("C:\\Users\\User\\Desktop\\yasmine\\finance.pdf");


   QPainter painter(&pdf);
   int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"finance");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 10));
          painter.drawText(500,3300,"NOM");
          painter.drawText(1500,3300,"prenom");
          painter.drawText(2500,3300,"telephone");
          painter.drawText(3500,3300,"id");
          painter.drawText(4500,3300,"salaire");
          painter.drawText(5500,3300,"adress");
          painter.drawRect(100,3000,9400,9000);

          QSqlQuery query;
          query.prepare("select * from finace");
          query.exec();
          while (query.next())
          {
              painter.drawText(500,i,query.value(0).toString());
              painter.drawText(1500,i,query.value(1).toString());
              painter.drawText(2500,i,query.value(2).toString());
              painter.drawText(3500,i,query.value(3).toString());
              painter.drawText(4500,i,query.value(4).toString());
              painter.drawText(5500,i,query.value(5).toString());

             i = i + 350;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
/////////////////////////////////////////////////////////////////

///////////////////////// Statistique ///////////////////////////
void app::on_pb_stat_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
                                model->setQuery("select * from finace where salaire  >700 ");
                                float nbr1=model->rowCount();
                                model->setQuery("select * from finace where salaire  between 300 and 700 ");
                                float nbr2=model->rowCount();
                                model->setQuery("select * from finace where salaire <300 ");
                                float nbr3=model->rowCount();
                                float total=nbr1+nbr2+nbr3;
                                QString a=QString(" salaire  plus que 700 "+QString::number((nbr1*100)/total,'f',2)+"%" );
                                QString b=QString("salaire entre 300 et 700 "+QString::number((nbr2*100)/total,'f',2)+"%" );
                                QString c=QString(" salaire inférieur à 300 "+QString::number((nbr3*100)/total,'f',2)+"%" );
                                QPieSeries *series = new QPieSeries();
                                series->append(a,nbr1);
                                series->append(b,nbr2);
                                series->append(c,nbr3);
                        if (nbr1!=0)
                        {QPieSlice *slice = series->slices().at(0);
                         slice->setLabelVisible();
                         slice->setPen(QPen());}
                        if ( nbr2!=0)
                        {
                                 // Add label, explode and define brush for 2nd slice
                                 QPieSlice *slice1 = series->slices().at(1);
                                 //slice1->setExploded();
                                 slice1->setLabelVisible();
                        }
                        if(nbr3!=0)
                        {
                                 // Add labels to rest of slices
                                 QPieSlice *slice2 = series->slices().at(2);
                                 //slice1->setExploded();
                                 slice2->setLabelVisible();
                        }
                                // Create the chart widget
                                QChart *chart = new QChart();
                                // Add data to chart with title and hide legend
                                chart->addSeries(series);
                                chart->setTitle("Pourcentage Par nombre  :salaire est: "+ QString::number(total));
                                chart->legend()->hide();
                                // Used to display the chart
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                chartView->resize(1000,500);
                                chartView->show();
}



