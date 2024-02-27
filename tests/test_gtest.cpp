#include "custom_allocator.hpp"
#include "my_list.hpp"

#include <vector>

#include <gtest/gtest.h>

TEST(Google_test, test_version) {
	EXPECT_GT(vs::version(), 0);
}

TEST(Google_test, test_allocation_vector) {
	size_t constexpr tmp = 10;
	auto vector_test = std::vector<int, vs::custom_allocator<int, tmp>>(10, 1);

	EXPECT_EQ(vector_test.size(), tmp);

	EXPECT_EQ(vector_test.get_allocator().get_Size(), tmp);
	EXPECT_EQ(vector_test.get_allocator().get_Capacity(), tmp);

	vector_test.emplace_back(1);
	EXPECT_EQ(vector_test.get_allocator().get_Size(), tmp*2);
}

TEST(Google_test, test_allocation_map) {
	constexpr size_t CONST = 5;
	auto fact_test = vs::FactorialContainer<CONST>{};
	auto map_test = std::map<size_t, size_t, std::less<size_t>, vs::custom_allocator<std::pair<const size_t, size_t>, CONST>>{};

	for (size_t i = 0; i < CONST; ++i) {
		map_test.emplace(std::pair<size_t, size_t>(i, fact_test[i]));
	}
	EXPECT_EQ(map_test.size(), CONST);
	EXPECT_EQ(map_test[CONST - 1], fact_test[CONST - 1]);
}

TEST(Google_test, test_container_size_and_clear) {
	auto container_test = vs::my_list<int>{ 1, 2, 3, 4, 5 };

	EXPECT_EQ(container_test.size(), 5);

	container_test.push_back(6);
	EXPECT_EQ(container_test.size(), 6);

	container_test.clear();
	EXPECT_EQ(container_test.size(), 0);
}
