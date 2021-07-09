#include <NamedType/named_type.hpp>

#include "funman_all.hpp"

#include <type_traits>
#include <tuple>
#include <iostream>
#include <optional>
#include <functional>

//TODO: make it work with reference types(myabe jsut std::ref this?)
//add an option to give an 'unwrapping function' to be called on th object type before it is giben to the function at invocation.
//TODO: use std::apply instead of std::invoke - use make_tuple and delete the call_impl :)
//TODO write some examples: small and big

using namespace fluent;

struct informer {
    informer(int a):m_a(a){std::cout<<"created\n";};
    informer(informen const& rhs):m_a(rhs.m_a){std::cout << "copy constructed\n"};
    informer(informer&& rhs):m_a(rhs.m_a){std::cout << "move constructed\n";};
    informer operator=(informer const & rhs):m_a(rhs.m_a){std::cout << "copy assigned\n";};
    informer operator=(informer&& rhs):m_a(rhs.m_a){std::cout << "move assigned\n";};
};

/*********************************************/