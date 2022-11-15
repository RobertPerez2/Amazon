#include "movie.h"
using namespace std;

Movie::Movie(const string name, double price, int qty, const string rating, const string genre) : Product("movie" , name, price, qty){
   rating_ = rating;
   genre_ = genre;
}

std::string Movie::getRating() const
{
  return rating_;
}

std::string Movie::getGenre() const
{
  return genre_;
}

std::set<std::string> Movie::keywords() const
{

  string moviestr = name_ + " " + rating_ + " ";
  moviestr = convToLower(moviestr);
  set<string> movieInfo = parseStringToWords(moviestr);
  
  movieInfo.insert( convToLower(genre_) ); //no punctuation or size analysis necessary for isbn

  //returns the string set of keywords that this product should be associated with
  return movieInfo;
}

//create/return a string that contains the product info
std::string Movie::displayString() const
{
/*
  <name>
  Author: <author> ISBN: <isbn>
  <price> <quantity> left.
*/

  stringstream moviestr;
  moviestr << name_; moviestr << '\n';
  moviestr << "Genre: "; moviestr << genre_;
  moviestr << " Rating: "; moviestr << rating_; moviestr << '\n';
  moviestr << price_; moviestr << " "; moviestr << qty_; moviestr << "left.";

  return moviestr.str();
}

void Movie::dump(std::ostream& os) const
{
/*
book
Data Abstraction & Problem Solving with C++
79.99
20
978-013292372-9
Carrano and Henry
*/
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}