/*
 * InstanceGenerator.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#include "InstanceGenerator.h"

#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

namespace cfpmm {

constexpr auto UNIFORM_MIN = 10;
constexpr auto UNIFORM_MAX = 1000;

using namespace std;

InstanceGenerator::InstanceGenerator() {

}

InstanceGenerator::~InstanceGenerator() {

}

void InstanceGenerator::generate(std::size_t nItems, std::size_t nKnacksacks,
		correlation correlated, bool similar) {

#define RAND(MIN, MAX, GEN) (uniform_int_distribution<int>(MIN, MAX)(GEN))

	using c = correlation;
	using uid = uniform_int_distribution<int>;

	// Create random number generator generator
	default_random_engine generator(
			chrono::system_clock::now().time_since_epoch().count());

	vector<int> weights(nItems);
	vector<int> prices(nItems);
	vector<int> capacities(nKnacksacks);

	// TODO Check this implementation
	if (correlated == c::NONE) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {

			// Knacksack Problems - page 185
			weights.push_back(distribution(generator));
			prices.push_back(distribution(generator));
		}
	} else if (correlated == c::WEAK) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {
			auto wi = distribution(generator);

			// Knacksack Problems - page 185
			weights.push_back(distribution(generator));
			prices.push_back(RAND(wi - 100, wi + 100, generator));
		}
	} else if (correlated == c::STRONG) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {

			auto wi = distribution(generator);

			// Knacksack Problems - page 186
			weights.push_back(wi);
			prices.push_back(wi + 100);
		}
	}

	double weightSum = 0.0;

	for (int i = 0; i < nItems; ++i) {
		weightSum += weights[i];
	}

	if (similar) {
		for (int i = 0; i < nKnacksacks - 1; i++) {

			double wj = 0.5 * weightSum;
			double ck = 0;

			for (int k = 0; k < i; k++) {
				ck += capacities[4];
			}

			uid distribution(UNIFORM_MIN, UNIFORM_MIN + wj - ck);

			capacities.push_back(distribution(generator));
		}
	} else {

		double minBound = 0.4 * weightSum / nKnacksacks;
		double maxBound = 0.6 * weightSum / nKnacksacks;
		double lastCapacity = 0.5 * weightSum;

		uid distribution(minBound, maxBound);

		for (int i = 0; i < nKnacksacks - 1; i++) {
			capacities.push_back(distribution(generator));

			lastCapacity -= capacities[i];
		}

		capacities.push_back(lastCapacity);
	}

#undef RAND
}

bool InstanceGenerator::saveToFile(const string& filename, size_t nItems,
		size_t nKnacksacks, const vector<int>& weigths,
		const vector<int>& prices, const vector<int>& capacities) {

	ofstream file(filename.c_str());

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file << nItems << " " << nKnacksacks << "\n";

	for (const auto& w : weigths) {
		file << w << " ";
	}

	for (const auto& p : prices) {
		file << p << " ";
	}

	for (const auto& c : capacities) {
		file << c << " ";
	}

	file.close();

	return false;
}

} /* namespace cfpmm */

