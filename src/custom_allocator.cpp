#include "custom_allocator.hpp"

void vs::PrintContainerMap(std::map<int, int, std::less<int>, vs::custom_allocator<std::pair<const int, int>, 10>>& dict) {
	for (const auto& node : dict) {
		std::cout << node.first << " " << node.second << std::endl;
	}
	std::cout << std::endl;
}
