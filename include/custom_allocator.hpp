#pragma once

#include <iostream>

#include <map>
#include <array>
#include <list>
#include <utility>
#include <memory>

//#define USE_PRETTY 1

#define __PRETTY_FUNCTION__  __FUNCSIG__

namespace vs {
	template<typename Q, size_t capacity>
	class custom_allocator {
	public:

		// Using:
		using value_type = Q;

		using pointer = Q*;
		using const_pointer = const Q*;
		using reference = Q&;
		using const_reference = const Q&;

		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		template<typename U, size_t capacity_U = capacity>
		struct rebind {
			using other = vs::custom_allocator<U, capacity>;
		};

		custom_allocator() {}
		~custom_allocator() {}

		template <typename U, size_t capacity_U = capacity>
		explicit custom_allocator(const custom_allocator<U, capacity_U>&) noexcept
		{ }

		pointer allocate(size_t n) {
#ifdef USE_PRETTY
			std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif // !USE_PRETTY
			if (m_size + n > m_capacity) {
#ifdef USE_PRETTY
				std::cout << "Memore realloc!!!" << std::endl;
#endif // !USE_PRETTY			
				m_capacity = m_capacity * 2;
				m_pointer = reinterpret_cast<pointer>(std::realloc(m_pointer, m_capacity * sizeof(value_type)));
			}
			if (!m_pointer) {
				m_pointer = reinterpret_cast<pointer>(std::malloc(m_capacity * sizeof(value_type)));
			}
			if (!m_pointer) {
				throw std::bad_alloc();
			}
			auto tmp_ptr = m_pointer + m_size;
			m_size += n;

			return tmp_ptr;
		}

		void deallocate(pointer ptr, std::size_t n) {
#ifdef USE_PRETTY
			std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif // !USE_PRETTY
			if (!ptr) {
				return;
			}
			m_size -= n;
			if (m_size != 0) {
				return;
			}
			std::free(m_pointer);
			m_pointer = nullptr;
		}

//		template<typename U, typename ...Args>
//		void construct(U* ptr, Args &&...args) {
//#ifdef USE_PRETTY
//			std::cout << __PRETTY_FUNCTION__ << std::endl;
//#endif // !USE_PRETTY
//			new(ptr) U(std::forward<Args>(args)...);
//		};
//
//		void destroy(Q* ptr) {
//#ifdef USE_PRETTY
//			std::cout << __PRETTY_FUNCTION__ << std::endl;
//#endif // !USE_PRETTY
//			ptr->~Q();
//		}

		using propagate_on_container_copy_assignment = std::true_type;
		using propagate_on_container_move_assignment = std::true_type;
		using propagate_on_container_swap = std::true_type;

		size_t get_Capacity() const { return m_capacity; }
		size_t get_Size() const { return m_size; }

	private:
		size_t m_capacity{ capacity };
		size_t m_size{ 0 };
		Q* m_pointer{ nullptr };
	};
}

template <class T, size_t capacity, class U>
inline constexpr bool operator== (const vs::custom_allocator<T, capacity>&, const vs::custom_allocator<U, capacity>&) noexcept
{
	return true;
}

template <class T, size_t capacity, class U>
inline constexpr bool operator!= (const vs::custom_allocator<T, capacity>&, const vs::custom_allocator<U, capacity>&) noexcept
{
	return false;
}

namespace vs {
	//class Factorial:
	template<size_t n>
	class Factorial {
	public:
		static const size_t value = Factorial<n - 1>::value * n;
	};

	template<>
	class Factorial<0> {
	public:
		static const size_t value = 1;
	};

	//@tparam container_size - factorial number
	template<size_t container_size>
	class FactorialContainer {
	public:
		FactorialContainer() {
			FillArray(std::make_index_sequence<container_size>{});
		}
		size_t operator[](size_t index) const {
			return m_fact_container.at(index);
		}
	private:
		template<typename Q, Q... Ints>
		void FillArray(std::integer_sequence<Q, Ints...>) {
			((m_fact_container[Ints] = Factorial<Ints>::value), ...);
		}
		std::array<size_t, container_size> m_fact_container;
	};
}

namespace vs {
	void PrintContainerMap(std::map<size_t, size_t, std::less<size_t>, vs::custom_allocator<std::pair<const size_t, size_t>, 10>>& dict);
}
