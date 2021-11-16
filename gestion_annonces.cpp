#include "gestion_annonces.h"
#include "ui_gestion_annonces.h"


gestion_annonces::gestion_annonces(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_annonces)
{
    ui->setupUi(this);

    ui->candidat_precis_annonce->setChecked(true);
    ui->popup_oui_annonce->setChecked(true);
    ui->email_oui_annonce->setChecked(true);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);

    filtre_index=0;
    tri_index=0;


    sendEmails();
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendEmails()));
    timer->start(1000 * 60 * 60);


}

gestion_annonces::~gestion_annonces()
{
    delete ui;
}

void gestion_annonces::creerDesign(){
    QString titre= ui->input_titre_annonce->text();
    QString description = ui->input_description_annonce->toPlainText();
    QFont font = ui->comboBox_font_annonce->currentFont();
    QString lien="";

    if(a.design.lien!="")
        lien=a.design.lien;

    Design d(titre, description, lien, font);

    a.design = d;

}

void gestion_annonces::creerPlan(){
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

void gestion_annonces::creerPayment(){

    double prix_brut = 0;
    bool par_facilite = ui->facilite_oui_annonce->isChecked();
    int nbr_mois = ui->comboBox_nbrMois_annonce->currentText().toInt();
    double avance = ui->avance_annonce->text().toDouble();


    Payment pa(prix_brut,par_facilite,nbr_mois,avance);

    pa.calcPrixBrut(a.plan);

    a.payment = pa;
}

void gestion_annonces::on_pushButton_trouver_image_annonce_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.canva.com/announcements/templates/job-vacancy/"));
}

void gestion_annonces::on_pushButton_selectionner_image_annonce_clicked()
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


void gestion_annonces::on_prec_creer_annonce_clicked()
{
    int curr = ui->creer_annonce_tabs->currentIndex();
    int next= curr-1;
    if(next <0 )
        next=0;

    ui->creer_annonce_tabs->setCurrentIndex(next);
}

void gestion_annonces::on_suiv_creer_annonce_clicked()
{
    int curr = ui->creer_annonce_tabs->currentIndex();
    int next= curr+1;
    if(next > 3 )
        next=3;

    ui->creer_annonce_tabs->setCurrentIndex(next);
}

void gestion_annonces::on_Confirmer_annonce_clicked()
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



void gestion_annonces::on_tout_les_candidat_annonce_clicked()
{
    ui->label_competance_annonce->hide();
    ui->comboBox_competance_annonce->hide();
}

void gestion_annonces::on_candidat_precis_annonce_clicked()
{
    ui->label_competance_annonce->show();
    ui->comboBox_competance_annonce->show();
}

void gestion_annonces::on_email_oui_annonce_clicked()
{
    ui->date_email_annonce->show();
}

void gestion_annonces::on_email_non_annonce_clicked()
{
    ui->date_email_annonce->hide();
}


void gestion_annonces::on_calcul_prix_annonce_clicked()
{
    creerPlan();
    creerPayment();

    int prix_total = a.payment.prix_brut + a.payment.calcInterer();

    ui->label_prixTotal_annonce->setText(QString("Prix Total: ").append(QString::number(prix_total)).append((" DT")));
}

void gestion_annonces::filtre(){



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

void gestion_annonces::trie(){


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

void gestion_annonces::display(){

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

void gestion_annonces::prepareChartData(QVector<int> &data ,QStringList &categories){


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

void gestion_annonces::constructChart(){
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

void gestion_annonces::on_tabWidget_currentChanged(int index)
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

void gestion_annonces::deleteAnnonce(int id){
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



void gestion_annonces::on_comboBox_6_currentIndexChanged(int index)
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

void gestion_annonces::on_comboBox_7_currentIndexChanged(int index)
{
    tri_index = index;
    filtre();
    trie();
    display();
}

void gestion_annonces::on_filtre_val_textChanged(const QString &arg1)
{
    filtre_val=arg1;
}

void gestion_annonces::on_filtre_val_editingFinished()
{
    filtre();
    trie();
    display();
}

void gestion_annonces::sendEmails(){

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

void gestion_annonces::on_echelle_currentIndexChanged(int index)
{
    constructChart();
}

void gestion_annonces::on_pushButton_clicked()
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
