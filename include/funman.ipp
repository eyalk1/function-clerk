#pragma once

#include "utility_templates.ipp"

#include <optional>
#include <tuple>
#include <type_traits>

template <typename f, typename... Args>
requires std::invocable<f, Args...> funman<f, Args...>::funman(f func)
    : func_m(func) {
  static constexpr auto all_types_are_different =
      ((count_type<Args, Args...>() == 1) && ...);
  static_assert(std::is_invocable_v<f, Args...>,
                "The combination of function and the list of types given "
                "cannot be called");
  static_assert(
      all_types_are_different,
      "Not all the types that were given to the funman are different");
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <typename... arg_t>
void funman<f, Args...>::operator()(arg_t&&... new_arg) {
  static constexpr auto all = (contains<arg_t, Args...>() && ...);
  static constexpr auto all_types_are_different =
      ((count_type<Args, Args...>() == 1) && ...);
  static_assert(all,
                "not all the types that were giner are part of the function "
                "parameter list");
  static_assert(all_types_are_different,
                "Not all the types that were given are different");

  std::tie(std::get<get_t_index<arg_t, Args...>()>(arguments)...) =
      std::tie((new_arg)...);
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
auto funman<f, Args...>::operator()() {
  if constexpr (std::is_same_v<R, void>) {
    if (is_tuple_full(arguments, Indices()))
      call_impl(Indices());
    return std::nullopt;
  } else {
    if (is_tuple_full(arguments, Indices()))
      return std::optional<R>(call_impl(Indices()));
    return std::optional<R>();
  }
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <typename... cancels>
void funman<f, Args...>::unValid() {
  static constexpr auto all = (contains<cancels, Args...>() && ...);
  static_assert(all,
                "not all the types that were given are part of the function "
                "parameter list");
  ((std::get<std::optional<cancels>>(arguments) = std::nullopt), ...);
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <typename arg_t>
bool funman<f, Args...>::isValid() {
  static constexpr auto all = (contains<arg_t, Args...>());
  static_assert(all,
                "not all the types that were given are part of the function "
                "parameter list");

  return std::get<std::optional<arg_t>>(arguments).has_value();
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
bool funman<f, Args...>::areAllValid() {
  return areAllValid_impl(Indices());
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
bool funman<f, Args...>::areAnyValid() {
  return areAnyValid_impl(Indices());
}



template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <typename new_f_t>
requires std::is_invocable_v<new_f_t, Args...>
void funman<f, Args...>::change_function(new_f_t new_func) {
  func_m = new_func;
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <std::size_t... I>
auto funman<f, Args...>::call_impl(std::index_sequence<I...>)
    -> funman<f, Args...>::R {
  return std::invoke(func_m, std::get<I>(arguments).value()...);
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <std::size_t... I>
bool funman<f, Args...>::areAllValid_impl(std::index_sequence<I...>) {
  return (isValid<typename std::tuple_element_t<I, args_t>::value_type>() && ...);
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
template <std::size_t... I>
bool funman<f, Args...>::areAnyValid_impl(std::index_sequence<I...>) {
  return (isValid<typename std::tuple_element_t<I, args_t>::value_type>() || ...);
}

template <typename f, typename... Args>
requires std::invocable<f, Args...>
auto funman<f, Args...>::args() -> funman<f, Args...>::args_t const& {
  return arguments;
}
