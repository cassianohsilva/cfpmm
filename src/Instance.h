/*
 * Instance.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <cstddef>
#include <vector>

#include "Item.h"

namespace cfpmm {

class Solution;
class Ant;

class Instance {
public:
	Instance(std::size_t nItems, std::size_t nKnacksacks,
			const std::vector<Item>& items, const std::vector<int>& capacities);

	virtual ~Instance();

	const std::vector<Item>& getItems() const {
		return items;
	}

	const std::vector<int>& getCapacities() const {
		return capacities;
	}

private:
	std::size_t nItems;
	std::size_t nKnacksacks;
	std::vector<Item> items;
	std::vector<int> capacities;

	friend class Solution;
	friend class Ant;
};

} /* namespace cfpmm */

#endif /* INSTANCE_H_ */