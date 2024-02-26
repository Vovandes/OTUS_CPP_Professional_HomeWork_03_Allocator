#include "custom_allocator.hpp"
#include "my_list.hpp"

#include <vector>

#include <gtest/gtest.h>

TEST(Google_test, test_version) {
	EXPECT_GT(version(), 0);
}

TEST(Google_test, test_allocation_vector) {
	auto vector_test = std::vector<int, vs::custom_allocator<int, 10>>(10, 1);

	EXPECT_EQ(vector_test.size(), 10);

	EXPECT_EQ(vector_test.get_allocator().get_Size(), 10);
	EXPECT_EQ(vector_test.get_allocator().get_Capacity(), 10);

	vector_test.emplace_back(1);
	EXPECT_EQ(vector_test.get_allocator().get_Size(), 11);
	EXPECT_EQ(vector_test.get_allocator().get_Capacity(), 10 * 2);
}

TEST(Google_test, test_allocation_map) {
	size_t const CONST = 5;
	auto fact_test = vs::FactorialContainer<CONST>;
	auto map_test = std::map<size_t, size_t, std::less<size_t>, vs::custom_allocator<std::pair<const size_t, size_t>, CONST>>{};

	for (size_t i = 0; i < CONST; ++i) {
		map_test.emplace(std::pair<size_t, size_t>(i, fact_test[i]));
	}
	EXPECT_EQ(map_test.size(), CONST);
	EXPECT_EQ(map_test[CONST - 1], fact_test[CONST - 1]);
}

TEST(Google_test, test_container_size_and_clear) {
	auto container_test = vs::my_list<int, vs::custom_allocator<int, 5>>{ 1, 2, 3, 4, 5 };

	EXPECT_EQ(container_test.size(), 5);

	container_test.push_back(6);
	EXPECT_EQ(container_test.size(), 6);

	container_test.clear();
	EXPECT_EQ(container_test.size(), 0);
}
