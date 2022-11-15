#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string user, std::vector<Product*>& hits, std::size_t index);
    void viewCart(std::string user);
    void buyCart(std::string user);
    
  private:
    std::vector<Product*> products;
    std::map<std::string, User*> users;
    /*Some kind of mapping between keywords and products 
      that match that keyword should be implemented.*/
    std::map < std::string, std::set<Product*> > keywordmap;
    std::map< std::string, std::vector<Product*> > cart;
    
};
#endif