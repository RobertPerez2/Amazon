#include <iostream>
#include "mydatastore.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
using namespace std;

MyDataStore::MyDataStore(){
}

MyDataStore::~MyDataStore() 
{
  users.clear();
  products.clear();
}

void MyDataStore::addProduct(Product* p) {
  products.push_back(p);
  set<string> keywords = p->keywords();
  for(set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
      keywordmap[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u) {
  string username = u->getName();
  if( users.find(username) == users.end() ) {
    users.insert(make_pair(username, u));
  }
}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {

  
  set<Product*> hits;
  map<string, set<Product*> >::iterator it;
  //create a map membership between keyterms and the products
    // for each term, iterate through the products(their keywords) and if you can find the term in that product's keywords, then place in that respective map
  //each keyterm will hold all the items that have that keyword in their product info,
  //you'll use set intersection between these keywords and get the products that are ONLY found in both, you'll return that vector of products
  //you'll use set union between all those keywords and return that vector of products

  //what if the products come with their mappings set? what if in the product theres a function that places them in maps then we can combine the maps in the end.
  //everytime you add a product, check their keywords and place them into the mapping

  if(type == 0) // AND search, return vector of products that contained all the terms
  {

    if( !(terms.empty()) && (keywordmap.find(terms[0]) != keywordmap.end() ) ) 
    {
      hits = keywordmap.find(terms[0])->second ;
    }
    
    if(terms.size() > 1 )
    {
      for(unsigned int i=0; i < terms.size(); i++)
      {
        if(keywordmap.find(terms[i]) != keywordmap.end() )
        {
          hits = setIntersection( hits , keywordmap.find(terms[i])->second );
        }
        else
        {
          hits.clear();
          break;
        }
      } 
    }


  }
  else if(type == 1) //OR search, return vector of products that contained any of the terms
  {
    for(unsigned int i=0; i < terms.size(); i++)
    {
      if(keywordmap.find(terms[i]) != keywordmap.end())
      {
        it = keywordmap.find(terms[i]);
        hits = setUnion(hits, it->second);
      }
    }
  }
  else
  {
    cout << "Input must be either 0 or 1" << endl;
  }
  

  vector<Product*> complete;
  set<Product*>::iterator it2;
  for(it2 = hits.begin(); it2 != hits.end(); ++it2)
  {
    complete.push_back(*it2);
  }

  return complete;
}


void MyDataStore::dump(ostream& ofile) {


  ofile << "<products>\n";
  for(unsigned int i=0; i < products.size(); i++)
  {
    products[i]->dump(ofile);
  }
  ofile << "</products>\n" << "<users>\n";

  for(map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
  {
    (it->second)->dump(ofile);
  }
  ofile << "</users>" << endl;

}

void MyDataStore::addToCart( string user, vector<Product*>& hits, size_t index) {
    
    if(users.find(user) != users.end())
    {
      cart[user].push_back(hits[index-1]);
    }
    else
    {
      cout << "Invalid request\n" << endl;
    }
}

void MyDataStore::viewCart(string user) {

  if(users.find(user) != users.end())
  {
    if(cart.find(user) != cart.end() ) {
      for(unsigned int i=0; i < cart[user].size(); i++) {
        cout << "Item " << i+1 << endl;
        cout << (cart[user].at(i))->displayString() << endl;
      }
    }
    else
    {
      cout << "Cart Empty" << endl;
    }
  }
  else
  {
    cout << "Invalid username\n" << endl;
  }

}

void MyDataStore::buyCart(string user) {

  if(users.find(user) != users.end())
  {

    map<string, User*>::iterator it;
    it = users.find(user);
    vector<Product*> couldNotBuy;
    for(unsigned int i=0; i < cart[user].size(); i++) {
      if( (cart[user].at(i))->getQty() > 0) {
        if( (it->second)->getBalance()  >=  cart[user].at(i)->getPrice() ) {
          cart[user].at(i)->subtractQty(1);
          (it->second)->deductAmount( cart[user].at(i)->getPrice() );
        }
      }
      else {
        couldNotBuy.push_back( cart[user].at(i) );
      }
    }
    cart[user]=couldNotBuy;

  }
  else
  {
    cout << "Invalid username\n" << endl;
  }

}