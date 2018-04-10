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

const std::string unk = "unknown";

// Constructor for Movie objects
Movie::Movie(std::string location, std::string title, std::string director = unk, std::string actors = unk, \
    unsigned int year = 9999, std::string genre = unk, float imdb = 0, unsigned int rt = 0): \
    location(location), title(title), director(director), actors(actors), year(year), \
    genre(genre), imdb_rating(imdb), rt_rating(rt) {}

// Method for printing details
void Movie::print_movie() {
    std::cout << std::setw(30) << std::left << "Movie Name: " << title << std::endl;
    std::cout << std::setw(30) << std::left << "Year: " << year << std::endl;
    std::cout << std::setw(30) << std::left << "Director: " << director << std::endl;
    std::cout << std::setw(30) << std::left << "actors: " << actors << std::endl;
    std::cout << std::setw(30) << std::left << "Genre: " << genre << std::endl;
    std::cout << std::setw(30) << std::left << "IMDB Rating: " << imdb_rating << std::endl;
    std::cout << std::setw(30) << std::left << "Rotten Tomatoes Rating: " << rt_rating << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
}
