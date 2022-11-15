#include "book.h"
using namespace std;

Book::Book(const string name, double price, int qty, const string isbn, const string author) : Product("book" , name, price, qty){
   author_ = author;
   isbn_ = isbn;
}

std::string Book::getAuthor() const
{
  return author_;
}

std::string Book::getISBN() const
{
  return isbn_;
}

std::set<std::string> Book::keywords() const
{

  string bookstr = name_ + " " + author_ + " ";
  bookstr = convToLower(bookstr);
  set<string> bookInfo = parseStringToWords(bookstr);
  bookInfo.insert(isbn_); //no punctuation or size analysis necessary for isbn

  //returns the string set of keywords that this product should be associated with
  return bookInfo;
}

//create/return a string that contains the product info
std::string Book::displayString() const
{
/*
  <name>
  Author: <author> ISBN: <isbn>
  <price> <quantity> left.
*/

  stringstream bookstr;
  bookstr << name_; bookstr << '\n';
  bookstr << "Author: "; bookstr << author_;
  bookstr << " ISBN: "; bookstr << isbn_; bookstr << '\n';
  bookstr << price_; bookstr << " "; bookstr << qty_; bookstr << " left.";

  return bookstr.str();
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}