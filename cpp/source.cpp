// MovieDB, ver0.1, 30-Mar-2018
// Akhil Cholayil, agent47akhil@gmail.com
// Program to store movie details in a database for easy access based on attributes.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // for setw and left in printing

using namespace std;
const string unk = "unknown"; // when an attribute is not given, use as default in constructor

class Movie {
private:
	string title;
	unsigned int year;
	string director;
	string lead;
	string genre;
	float imdb_rating;
	unsigned int rt_rating;

public:
	Movie(string, unsigned int, string, string, string, float, unsigned int); // Constructor
	void print_movie(); // Print movie details line by line
	string get_title() { return title; };
	unsigned int get_year() { return year; };
	string get_director() { return director; };
	string get_lead() { return lead; };
	string get_genre() { return genre; };
	float get_imdb_rating() { return imdb_rating; };
	unsigned int get_rt_rating() { return rt_rating; };
};

Movie::Movie(string title, unsigned int year = 9999, string director = unk, \
	string lead = unk, string genre = unk, float imdb = 0, unsigned int rt = 0): \
	title(title), year(year), director(director), lead(lead), genre(genre), \
	imdb_rating(imdb), rt_rating(rt) {}

void Movie::print_movie() {
	cout << setw(30) << left << "Movie Name: " << title << endl;
	cout << setw(30) << left << "Year: " << year << endl;
	cout << setw(30) << left << "Director: " << director << endl;
	cout << setw(30) << left << "Lead: " << lead << endl;
	cout << setw(30) << left << "Genre: " << genre << endl;
	cout << setw(30) << left << "IMDB Rating: " << imdb_rating << endl;
	cout << setw(30) << left << "Rotten Tomatoes Rating: " << rt_rating << endl;
	cout << "-----------------------------------------------------------" << endl;
}

vector<Movie> movie_vector; // This is where movie DB will be read to, and new movies will be added to

void write_DB(Movie& obj) {
	// Check if title is already in DB, if not add
	for (unsigned int i = 0; i < movie_vector.size(); i++) {
		if (obj.get_title() == movie_vector[i].get_title()) {
			cout << "\"" << obj.get_title() << "\" already in the database" << endl;
			return;
		}
	}
	// Title is not duplicate, so push to vector and add to DB
	movie_vector.push_back(obj);
	ofstream fout("movieDB.txt", ios::app); // ios::app to append
	fout << "\n" << obj.get_title() << ", " << obj.get_year() << ", " << obj.get_director() << ", "\
		<< obj.get_lead() << ", " << obj.get_genre() << ", " << obj.get_imdb_rating() << ", " \
		<< obj.get_rt_rating();
	fout.close();
}

void read_DB(vector<Movie>& movie_vector) {
	ifstream fin("movieDB.txt"); // ifstream is read only
	vector<string> token_vector;
	string line;
	while (getline(fin, line)) {
		token_vector.clear();
		int pos = 0;
		while ((pos = line.find(", ")) != std::string::npos) {
			token_vector.push_back(line.substr(0, pos));
			line.erase(0, pos + 2); // 2 is length of ", "
		}
		token_vector.push_back(line); // last token doesn't have ", "
		Movie obj(token_vector[0], stoi(token_vector[1]), token_vector[2], \
			token_vector[3], token_vector[4], stof(token_vector[5]), stoi(token_vector[6]));
		movie_vector.push_back(obj);
	}
	fin.close();
}

int main() {
	read_DB(movie_vector);
	for (unsigned int i = 0; i < movie_vector.size(); i++) {
		movie_vector[i].print_movie();
	}
	Movie matrix("The Matrix", 1999, "Wachowskis", "Keanu Reeves", "sci-fi", 8.7, 87);
	write_DB(matrix);
	Movie titanic("Titanic", 1997, "James Cameroon", "Leo Dicaprio", "Drama", 7.8, 88);
	write_DB(titanic);
	cout << "\nAfter adding new movies" << endl;
	for (unsigned int i = 0; i < movie_vector.size(); i++) {
		movie_vector[i].print_movie();
	}
	return 0;
}