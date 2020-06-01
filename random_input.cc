// C++17

#include <type_traits>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>
#include <iomanip>

namespace __detail {

template<typename R, typename ...As>
struct __function_traits_base {
    using function_type = std::function<R(As...)>;

    using result_type = R;

    using argument_types = std::tuple<As...>;
};

template<typename F>
struct __function_traits;
template<typename F>
struct __function_traits<std::reference_wrapper<F>> : public __function_traits<F> {};
template<typename R, typename ...As>
struct __function_traits<R(*)(As...)> : public __function_traits_base<R, As...> {};
template<typename R, typename C, typename ...As>
struct __function_traits<R(C::*)(As...)> : public __function_traits_base<R, As...> {};
template<typename R, typename C, typename ...As>
struct __function_traits<R(C::*)(As...) const> : public __function_traits_base<R, As...> {};
template<typename F>
struct __function_traits : public __function_traits<decltype(&F::operator())> {};

}

template<typename F>
struct function_traits : public __detail::__function_traits<std::decay_t<F>> {};



template<typename As>
struct generate_params;

template<>
struct generate_params< std::tuple<> > {
    std::tuple<> operator() () {
        return std::make_tuple();
    }
};

template<typename A, typename ...As> 
struct generate_params< std::tuple<A, As...> > {
	std::tuple<A, As...> operator() () {
		std::default_random_engine r;
		A random_value = static_cast<A>(r()); 
		auto rest_values = generate_params<std::tuple<As...>>()();
		return std::tuple_cat(std::tuple<A>(random_value), rest_values);
	}
};




template<typename F> 
typename function_traits<F>::result_type random_run(F f) {
	using arg_types = typename function_traits<F>::argument_types;
	arg_types args = generate_params<arg_types>()();
	return std::apply(f, args);
}

/// test:

struct Car {
	long long operator() (int a) {
		return a;
	}
};

int bar(int a, int b) {
	return a * b;
}

int main() {
	auto foo = [](int a, int b, float c) -> float {
		return a + b + 3.14159;
	};

	std::cout << random_run(foo) << std::endl;
	std::cout << random_run(bar) << std::endl;
	std::cout << random_run(Car()) << std::endl;

	return 0;
}


