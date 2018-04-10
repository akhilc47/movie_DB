#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::vector<Movie> &movie_vector, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_next_clicked();
    void on_pushButton_prev_clicked();
    void on_pushButton_vlc_clicked();
    void on_pushButton_KMP_clicked();
    void on_pushButton_filter_clicked();

private:
    Ui::MainWindow *ui;
    std::vector <Movie> movie_vector;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* item;
    int movie_number;
    unsigned int year_before;
    unsigned int year_after;
    float imdb_gt;
    unsigned int rt_gt;
    bool filter_on;
    void setWindow(Movie& movie);
    void resetFilter();
    void setFilter();
};

#endif // MAINWINDOW_H
