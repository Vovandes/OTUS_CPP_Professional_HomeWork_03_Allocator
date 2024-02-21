#include "custom_allocator.hpp"

void vs::PrintContainerMap(std::map<size_t, size_t, std::less<size_t>, vs::custom_allocator<std::pair<const size_t, size_t>, 10>>& dict) {
	for (const auto& node : dict) {
		std::cout << node.first << " " << node.second << std::endl;
	}
	std::cout << std::endl;
}
