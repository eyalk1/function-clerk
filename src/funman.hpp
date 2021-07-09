#ifndef funman__HPP
#define funman__HPP

/**
 * @file funmanp.hpp
 * @author eyal kamitchi (eyalkkamitchi1@gmail.com)
 * @brief funman is an utility to abstract funcation into object with some trivial features:
 * 1. arguments can be given at any order.
 * 2. argument can be given via python syntax(i.e. thing='value').
 * 3. argument can be validated.
 * 3. argument can be over-written.
 * @version 0.1
 * @date 09-07-2021
 * 
 * 
 */

#include <type_traits>
#include <concepts>
#include <optional>


/**
 * @brief the funman class.
 * this class holds a tuple of the arguments, and a pointer to a callable object.
 * 
 * @
 * 
 */

template <typename f, typename... Args>
requires std::invocable<f, Args...>
struct funman
{
    using R = std::result_of_t<f(Args...)>;

    using args_t = std::tuple<std::optional<Args>...>;

    using Indices = std::make_index_sequence<sizeof...(Args)>;

    funman(f func);

    template<typename... arg_t>
    void operator()(arg_t&&... new_arg);

    auto operator()();

    template<typename...cancels>
    void unValid();

    template<typename arg_t>
    bool isValid();

    bool areAllValid();

    bool areAnyValid();

    template<typename new_f_t>
    requires std::is_same_v<new_f_t, f>
    void change_function(new_f_t new_func);
private:
    args_t arguments;
    f func_m;

    template<std::size_t... I>
    R call_impl(std::index_sequence<I...>);

    template<std::size_t... I>
    bool areAllValidImpl(std::index_sequence<I...>);

public:
    args_t const& args();
};
#endif