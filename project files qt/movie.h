#ifndef MOVIE_H
#define MOVIE_H

#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

class Movie
{
private:
    std::string location;
    std::string title;
    std::string director;
    std::string actors;
    unsigned int year;
    std::string genre;
    float imdb_rating;
    unsigned int rt_rating;

public:
    Movie(std::string, std::string, std::string, std::string, unsigned int, std::string, float, unsigned int); // Constructor
    void print_movie(); // Print movie details line by line
    std::string get_location() { return location; }
    std::string get_title() { return title; }
    unsigned int get_year() { return year; }
    std::string get_director() { return director; }
    std::string get_actors() { return actors; }
    std::string get_genre() { return genre; }
    float get_imdb_rating() { return imdb_rating; }
    unsigned int get_rt_rating() { return rt_rating; }
};

#endif // MOVIE_H
