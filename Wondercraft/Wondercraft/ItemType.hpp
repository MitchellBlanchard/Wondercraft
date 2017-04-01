#pragma once

#include <string>

//The types of items in the game
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

	//converts the enum to it's acossiated string
	std::string enumToString(ItemType);

	//converts the string to it's acossiated enum
	ItemType stringToEnum(std::string&);

	bool isHat(ItemType);
	bool isRobe(ItemType);
	bool isStaff(ItemType);
};