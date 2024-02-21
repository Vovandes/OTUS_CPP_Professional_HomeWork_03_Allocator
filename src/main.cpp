#include "custom_allocator.hpp"
#include "my_list.hpp"

int main() {
	// A сonstant for 10 elements:
	// @param NumElem - max size for allocate;
	const size_t NumElem{ 10 };

	vs::FactorialContainer<10> factorials;

	try {
		// Define std::map instance with DEFAULT allocator(std::allocator<>)
		auto dict = std::map<size_t, size_t, std::less<size_t>, std::allocator<std::pair<const size_t, size_t>>>{};

		// Insert 10 elements in std::map(allocated with DEFAULT allocator) :
		// @key - values from 0 to 9
		// @value - factorial of key value
		for (size_t i = 0; i < NumElem; ++i) {
			dict.emplace(std::pair<size_t, size_t>(i, factorials[i]));
		}

		// Define std::map instance with CUSTOM allocator(vs::custom_allocator<>)
		auto dict_with_custom_allocator 
			= std::map<size_t, size_t, std::less<size_t>, vs::custom_allocator<std::pair<const size_t, size_t>, NumElem>>{};

		// Insert 10 elements in std::map (allocated with CUSTOM allocator):
		// @key - values from 0 to 9
		// @value - factorial of key value
		//
		// Implement custom memory allocation for fixed number of map nodes
		for (size_t i = 0; i < NumElem; ++i) {
			dict_with_custom_allocator.emplace(std::pair<size_t, size_t>(i, factorials[i]));
		}
		std::cout << std::endl;

		// Print elements from dict_with_custom_allocator
		vs::PrintContainerMap(dict_with_custom_allocator);

		//////////////////////////////////////////////////////////////////////////

		// 6. Define custom container (Linked list) with DEFAULT allocator
		auto list_default = vs::my_list<int, std::allocator<int>>{};
		// 7. Insert 10 elements from 0 to 9
		for (int i = 0; i < 10; ++i) {
			list_default.push_back(i);
		}

		// 8. Define custom container (Linked list) with CUSTOM allocator
		auto list_custom = vs::my_list<int, vs::custom_allocator<int, NumElem>>{};
		// 9. Insert 10 elements from 0 to 9
		for (int i = 0; i < 10; ++i) {
			list_custom.push_back(i);
		}

		// 10. Print all elements from list_custom
		for (auto it = list_custom.cbegin(), itF(list_custom.cend()); it != itF; ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size my container = " << list_custom.size() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}