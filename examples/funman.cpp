#include <NamedType/named_type.hpp>

#include <cassert>

#include "funman_all.hpp"

#include <functional>
#include <iostream>

using namespace fluent;

using GroceryList = NamedType<std::vector<std::string>, struct GroceryListTag>;

using Limit = NamedType<bool, struct boolTag>;

static const GroceryList::argument grocerylist;
static const Limit::argument limit;

int SuperPharm(GroceryList gl, Limit should_limit_price){
  std::cout << "SuperPharm: ";
  for(auto& i : gl.get())
    std::cout << i << ' ';
  std::cout << std::endl;
  int price = gl.get().size();
  if(should_limit_price.get() && price > 100)
    return -1;
  return price;
}

int Shuphersal(GroceryList gl, Limit should_limit_price){
  std::cout << "Shuphersal: ";
  for(auto& i : gl.get())
    std::cout << i << ' ';
  std::cout << std::endl;
  int price = gl.get().size();
  if(should_limit_price.get() && price > 100)
    return -1;
  return price + 100;
}

/*********************************************/

int main(void){
  auto f2 = make_fun<GroceryList, Limit>(&Shuphersal);
  // didn't start shopping
  assert(f2.areAnyValid() == false);
  // added some items
  f2(grocerylist = {std::string("banana"), std::string("apple")});
  // I've got a grocery list but not a limit yet
  assert(f2.isValid<GroceryList>() == true);
  // mom isn't happy with the list so she unvalidated it
  f2.unValid<GroceryList>();
  // nothing
  assert(f2.areAnyValid() == false);
  // added two argument at once in any order!
  f2(limit = true, grocerylist = {std::string("Ginger"), std::string("keyboard")});
  // we're ready!
  assert(f2.areAllValid() == true);
  // apply the function!
  assert(f2() == 102);
  // let's try another supermarket!
  f2.change_function(&SuperPharm);
  f2(limit = true, grocerylist = {std::string("nails"), std::string("hammer"), std::string("wood")});
  assert(f2() == 3);

  return 0;
}