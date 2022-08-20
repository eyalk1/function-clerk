#include <NamedType/named_type.hpp>

#include "funman_all.hpp"

#include <functional>
#include <iostream>
#include <optional>
#include <tuple>
#include <type_traits>

// TODO: make it work with reference types(myabe jsut std::ref this?)
// add an option to give an 'unwrapping function' to be called on th object type
// before it is giben to the function at invocation.
// TODO: use std::apply instead of std::invoke - use make_tuple and delete the
// call_impl :)
// TODO write some examples: small and big

using namespace fluent;

struct informer {
  informer(int a) : m_a(a) { std::cout << "created\n"; };
  informer(informer const& rhs) : m_a(rhs.m_a) {
    std::cout << "copy constructed\n";
  };
  informer(informer&& rhs) : m_a(rhs.m_a) {
    std::cout << "move constructed\n";
  };
  informer operator=(informer const& rhs) {
      m_a = rhs.m_a;
    std::cout << "copy assigned\n";
  };
  informer operator=(informer&& rhs) {
      m_a = rhs.m_a;
    std::cout << "move assigned\n";
  };
  int m_a{7};
};

void function(informer){
    std::cout << "by value" << std::endl;
}

/*********************************************/

int main(void){
    auto f = funman<decltype(&function), informer>(&function);
    f(informer(2));
    f();
    return 0;
}