#include <QApplication>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>

MainWindow::MainWindow(std::vector<Movie> &movie_vector, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    movie_vector(movie_vector),
    scene(new QGraphicsScene()),
    item(new QGraphicsPixmapItem()){
    std::cout << "Constructor invoked" << std::endl;
    ui->setupUi(this);
    setWindow(movie_vector[0]);
    ui->lineEdit_before->setInputMask("9999");
    ui->lineEdit_before->setPlaceholderText(QString::fromUtf8("YYYY"));
    ui->lineEdit_after->setInputMask("9999");
    ui->lineEdit_after->setPlaceholderText(QString::fromUtf8("YYYY"));
    ui->lineEdit_imdb->setInputMask("9.9");
    ui->lineEdit_imdb->setPlaceholderText(QString::fromUtf8("0-9.9"));
    ui->lineEdit_rt->setInputMask("99");
    ui->lineEdit_rt->setPlaceholderText(QString::fromUtf8("0-99"));
    resetFilter();
    std::cout << "Constructor finished" << std::endl;
}

MainWindow::~MainWindow() {
    std::cout << "Destructor invoked" << std::endl;
    delete ui;
    delete scene;
    delete item;
}

void MainWindow::setWindow(Movie &movie) {
    QTextBrowser *textBrowser_Title = this->findChild<QTextBrowser*>("textBrowser_Title");
    textBrowser_Title->setText(QString::fromUtf8(movie.get_title().c_str()));
    QTextBrowser *textBrowser_Year = this->findChild<QTextBrowser*>("textBrowser_Year");
    textBrowser_Year->setText(QString::number(movie.get_year()));
    QTextBrowser *textBrowser_IMDB = this->findChild<QTextBrowser*>("textBrowser_IMDB");
    textBrowser_IMDB->setText(QString::number(movie.get_imdb_rating()));
    QTextBrowser *textBrowser_RT = this->findChild<QTextBrowser*>("textBrowser_RT");
    textBrowser_RT->setText(QString::number(movie.get_rt_rating()));
    QTextBrowser *textBrowser_Director = this->findChild<QTextBrowser*>("textBrowser_Director");
    textBrowser_Director->setText(QString::fromUtf8(movie.get_director().c_str()));
    QTextBrowser *textBrowser_Actors = this->findChild<QTextBrowser*>("textBrowser_Actors");
    textBrowser_Actors->setText(QString::fromUtf8(movie.get_actors().c_str()));
    QGraphicsView* movie_poster = this->findChild<QGraphicsView*>("movie_poster");
    int pos = movie.get_location().find_last_of("/\\");
    item->setPixmap(QPixmap(("C:/Users/Akhil/Desktop/codes/movie_DB/posters/"+movie.get_location().substr(pos+1)+".jpg").c_str()));
    scene->addItem(item);
    movie_poster->setScene(scene);
    movie_poster->show();
}

void MainWindow::on_pushButton_next_clicked() {
    if (filter_on) {
        for (int temp_n = (movie_number+1)%movie_vector.size(); temp_n != movie_number; temp_n = (temp_n+1)%movie_vector.size()) {
            Movie temp_mov = movie_vector[temp_n];
            std::cout << temp_n << " " << movie_number << " " << temp_mov.get_year() << std::endl;
            if ((temp_mov.get_year() <= year_before) && (temp_mov.get_year() >= year_after) &&
                    (temp_mov.get_imdb_rating() >= imdb_gt) && (temp_mov.get_rt_rating() >= rt_gt)) {
                movie_number = temp_n;
                setWindow(temp_mov);
                return;
            }
        }
        std::cout << "No movie matches the filters" << std::endl;
        return;
    }
    movie_number = (movie_number+1)%movie_vector.size();
    std::cout << movie_number << " " << movie_vector.size() << std::endl;
    setWindow(movie_vector[movie_number]);
}

void MainWindow::on_pushButton_prev_clicked() {
    if (filter_on) {
        int temp_n = movie_number-1;
        if (temp_n < 0) {
            temp_n += movie_vector.size();
        }
        for (; temp_n != movie_number;) {
            temp_n--;
            if (temp_n < 0) {
                temp_n += movie_vector.size();
            }
            Movie temp_mov = movie_vector[temp_n];
            std::cout << temp_n << " " << movie_number << " " << temp_mov.get_year() << std::endl;
            if ((temp_mov.get_year() <= year_before) && (temp_mov.get_year() >= year_after) &&
                    (temp_mov.get_imdb_rating() >= imdb_gt) && (temp_mov.get_rt_rating() >= rt_gt)) {
                movie_number = temp_n;
                setWindow(temp_mov);
                return;
            }
        }
        std::cout << "No movie matches the filters" << std::endl;
        return;
    }
    movie_number--;
    if (movie_number < 0) {
        movie_number += movie_vector.size();
    }
    std::cout << movie_number << " " << movie_vector.size() << std::endl;
    setWindow(movie_vector[movie_number]);
}

void MainWindow::on_pushButton_vlc_clicked() {
    std::string appname = "C:\\Program Files\\VideoLAN\\VLC\\vlc.exe";
    std::string folder = movie_vector[movie_number].get_location();
    size_t start_pos = 0;
    // replace forward or back slashes wilth doublebackslashes.
    while((start_pos = folder.find_first_of("/\\", start_pos)) != std::string::npos) {
        folder.replace(start_pos, 1, "\\");
        start_pos += 2; // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    // no idea what the below 5 lines do, but copied from stackoverflow
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    char buf[500] = {0};
    sprintf(buf, "\"%s\" --play-and-exit --playlist-tree \"%s\"", appname.c_str(), folder.c_str());
    // '\"' is required for printing double quotes, playlist-tree will play everything under that folder.
    // eg: buf = "C:\Program Files\VideoLAN\VLC\vlc.exe" --play-and-exit --playlist-tree "E:\FILMS\English\6+\17 Again [2009]"
    CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

}

void MainWindow::on_pushButton_KMP_clicked() {
    std::string appname = "C:\\KMPlayer\\KMPlayer.exe";
    std::string folder = movie_vector[movie_number].get_location();
    size_t start_pos = 0;
    // replace forward or back slashes wilth doublebackslashes.
    while((start_pos = folder.find_first_of("/\\", start_pos)) != std::string::npos) {
        folder.replace(start_pos, 1, "\\");
        start_pos += 2; // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    // no idea what the below 5 lines do, but copied from stackoverflow
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    char buf[500] = {0};
    sprintf(buf, "\"%s\" \"%s\"", appname.c_str(), folder.c_str());
    // '\"' is required for printing double quotes, playlist-tree will play everything under that folder.
    // eg: buf = "C:\Program Files\VideoLAN\VLC\vlc.exe" --play-and-exit --playlist-tree "E:\FILMS\English\6+\17 Again [2009]"
    CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}

void MainWindow::resetFilter() {
    movie_number = 0;
    year_before = 2050;
    year_after = 1900;
    imdb_gt = 0.0;
    rt_gt = 0;
    filter_on = false;
    ui->lineEdit_after->clear();
    ui->lineEdit_before->clear();
    ui->lineEdit_imdb->clear();
    ui->lineEdit_rt->clear();
}

void MainWindow::setFilter() {
    filter_on = true;
    int yb = ui->lineEdit_before->text().toInt();
    int ya = ui->lineEdit_after->text().toInt();
    if ((yb > 1900) && (ya < 2050) && (yb >= ya)) {
        year_after = ya;
        year_before = yb;
    }
    imdb_gt = ui->lineEdit_imdb->text().toFloat();
    rt_gt = ui->lineEdit_rt->text().toInt();
}

void MainWindow::on_pushButton_filter_clicked() {
    if (filter_on) {
        resetFilter();
        std::cout << filter_on << " " << year_before << " " << year_after << " " << imdb_gt << " " << rt_gt << std::endl;
    }
    else {
        setFilter();
        std::cout << filter_on << " " << year_before << " " << year_after << " " << imdb_gt << " " << rt_gt << std::endl;
    }
}
