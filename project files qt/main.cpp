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

// Function for writing to DB
void write_DB(std::vector<Movie>& movie_vector, Movie& obj) {
    // Check if title is already in DB, if not add
    for (unsigned int i = 0; i < movie_vector.size(); i++) {
        if (obj.get_title() == movie_vector[i].get_title()) {
            std::cout << "\"" << obj.get_title() << "\" already in the database" << std::endl;
            return;
        }
    }
    // Title is not duplicate, so push to vector and add to DB
    movie_vector.push_back(obj);
    std::ofstream fout("movieDB.txt", std::ios::app); // ios::app to append
    fout << "\n" << obj.get_title() << ";" << obj.get_director() << ";" << obj.get_actors() \
        << ";" << obj.get_year() << ";" << ";" << obj.get_genre() << ";" << obj.get_imdb_rating() << ";" \
        << obj.get_rt_rating();
    fout.close();
}

// Function for reading from DB
void read_DB(std::vector<Movie>& movie_vector) {
    std::ifstream fin("C:/Users/Akhil/Desktop/codes/Qt/MovieDB/movieDB.txt"); // ifstream is read only
    std::cout << "Opened DB file, Reading now" << std::endl;
    std::vector<std::string> token_vector;
    std::string line;
    while (getline(fin, line)) {
        token_vector.clear();
        int pos = 0;
        while ((pos = line.find(";")) != std::string::npos) {
            token_vector.push_back(line.substr(0, pos));
            line.erase(0, pos + 1); // 2 is length of ", "
        }
        token_vector.push_back(line); // last token doesn't have ", "
        Movie obj(token_vector[0], token_vector[1], token_vector[2], token_vector[3], \
            stoi(token_vector[4]), token_vector[5], stof(token_vector[6]), stoi(token_vector[7]));
        movie_vector.push_back(obj);
    }
    fin.close();
    std::cout << "Reading completed, closing DB file" << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<Movie> movie_vector; // This is where movie DB will be read to, and new movies will be added to
    read_DB(movie_vector);
    if (movie_vector.size() == 0) {
        std::cout << "Database could not be read or is empty" << std::endl;
        return a.exec();
    }
    MainWindow w(movie_vector);
    w.show();
    return a.exec();
}
