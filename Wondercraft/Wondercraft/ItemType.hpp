#pragma once

#include <string>

namespace ItemType {
	enum ItemType {
		NONE,

		WARM_STONE,
		COOL_STONE,
		DRY_STONE,
		WET_STONE,

		FIRE_GEM,
		EARTH_GEM,
		AIR_GEM,
		WATER_GEM,

		BASIC_HAT,
		FIRE_HAT,
		EARTH_HAT,
		AIR_HAT,
		WATER_HAT,

		BASIC_ROBE,
		FIRE_ROBE,
		EARTH_ROBE,
		AIR_ROBE,
		WATER_ROBE,

		BASIC_STAFF,
		FIRE_STAFF,
		EARTH_STAFF,
		AIR_STAFF,
		WATER_STAFF,

		HEALTH_POTION
	};

	std::string enumToString(ItemType);
	ItemType stringToEnum(std::string&);
};