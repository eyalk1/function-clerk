#pragma once

#include <type_traits>
#include <tuple>
#include <optional>

/**
 *
 */

template<typename... T> struct is_tuple{
	using value = std::false_type;
	static constexpr auto val{false};
};

template<typename... T> struct is_tuple<std::tuple<T...>>{
	using value = std::true_type;
	static constexpr auto val{true};
};

template<typename... T>
using is_tuple_v = typename is_tuple<T...>::value;

template<typename... T>
concept tuple_c = is_tuple<T...>::val;

template<typename... T> struct is_tuple_of_optionals{
	using value = std::false_type;
	static constexpr auto val{false};
};

template<typename... T> struct is_tuple_of_optionals<std::tuple<std::optional<T>...>>{
	using value = std::true_type;
	static constexpr auto val{true};
};

template<typename... T>
using is_tuple_of_optionals_v = typename is_tuple_of_optionals<T...>::value;

template<typename... T>
concept tuple_of_optionals_c = is_tuple<T...>::val;




template<typename target, typename...typelist>
consteval bool contains(){
	return std::disjunction_v<std::is_same<target, typelist>...>;
}



template<std::size_t... I>
auto is_tuple_full(tuple_of_optionals_c auto const & tuple_to_check, std::index_sequence<I...>){
	static_assert(is_tuple_v<std::decay_t<decltype(tuple_to_check)>>(), "not a tuple");
	static_assert(is_tuple_of_optionals_v<std::decay_t<decltype(tuple_to_check)>>(), "not a tuple of optionals");

	return (std::get<I>(tuple_to_check).has_value() && ...);
}


template<typename target, typename head, typename... tail>
consteval size_t get_t_index(){
	static_assert(contains<target, head, tail...>(), "target is not in the typelist.");

	if constexpr (std::is_same_v<target,head>)
		return 0;
	else
		return 1 + get_t_index<target,tail...>();
}


template<typename target, typename head, typename... tail>
consteval unsigned int count_type(){
	if constexpr (sizeof...(tail) == 0)
		return std::is_same_v<target, head>;
	else
		return std::is_same_v<target, head> + count_type<target, tail...>();
}
