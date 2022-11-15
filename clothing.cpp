#include "clothing.h"
#include <sstream>
using namespace std;

Clothing::Clothing(const string name, double price, int qty, const string size, const string brand) : Product("clothing" , name, price, qty){
   size_ = size;
   brand_ = brand;
}

std::string Clothing::getSize() const
{
  return size_;
}

std::string Clothing::getBrand() const
{
  return brand_;
}

std::set<std::string> Clothing::keywords() const
{

  string clothingstr = name_ + " " + size_ + " " + brand_;
  clothingstr = convToLower(clothingstr);
  set<string> clothingInfo = parseStringToWords(clothingstr);
  //returns the string set of keywords that this product should be associated with
  return clothingInfo;
}

//create/return a string that contains the product info
std::string Clothing::displayString() const
{
  stringstream clothingstr;
  clothingstr << name_; clothingstr << '\n';
  clothingstr << "Size: "; clothingstr << size_;
  clothingstr << " Brand: "; clothingstr << brand_; clothingstr << '\n';
  clothingstr << price_; clothingstr << " "; clothingstr << qty_; clothingstr << " left.";

  return clothingstr.str();
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}