#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include "util.h"

class Movie : public Product {
  public:
    Movie(const std::string name, double price, int qty, const std::string rating, const std::string genre);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

    std::string getRating() const; 
    std::string getGenre() const;

  protected:
    std::string rating_;
    std::string genre_;
};
#endif