#include "ItemType.hpp"

std::string ItemType::enumToString(ItemType i){
	switch (i) {
	case NONE: return "";

	case WARM_STONE: return "warm stone";
	case COOL_STONE: return "cool stone";
	case DRY_STONE:  return "dry stone";
	case WET_STONE:  return "wet stone";

	case FIRE_GEM:  return "fire gem";
	case EARTH_GEM: return "earth gem";
	case AIR_GEM:   return "air gem";
	case WATER_GEM: return "water gem";

	case BASIC_HAT: return "basic hat";
	case FIRE_HAT:  return "fire hat";
	case EARTH_HAT: return "earth hat";
	case AIR_HAT:   return "air hat";
	case WATER_HAT: return "water hat";

	case BASIC_ROBE: return "basic robe";
	case FIRE_ROBE:  return "fire robe";
	case EARTH_ROBE: return "earth robe";
	case AIR_ROBE:   return "air robe";
	case WATER_ROBE: return "water robe";

	case BASIC_STAFF: return "basic staff";
	case FIRE_STAFF:  return "fire staff";
	case EARTH_STAFF: return "earth staff";
	case AIR_STAFF:   return "air staff";
	case WATER_STAFF: return "water staff";

	case HEALTH_POTION: return "health potion";

	default: return "";
	}
}

ItemType::ItemType ItemType::stringToEnum(std::string& s) {
	if(s == "warm stone") return WARM_STONE;
	else if (s == "cool stone") return COOL_STONE;
	else if (s == "dry stone")  return DRY_STONE;
	else if (s == "wet stone")  return WET_STONE;

	else if (s == "fire gem")  return FIRE_GEM;
	else if (s == "earth gem") return EARTH_GEM;
	else if (s == "air gem")   return AIR_GEM;
	else if (s == "water gem") return WATER_GEM;

	else if (s == "basic hat") return BASIC_HAT;
	else if (s == "fire hat")  return FIRE_HAT;
	else if (s == "earth hat") return EARTH_HAT;
	else if (s == "air hat")   return AIR_HAT;
	else if (s == "water hat") return WATER_HAT;

	else if (s == "basic robe") return BASIC_ROBE;
	else if (s == "fire robe")  return FIRE_ROBE;
	else if (s == "earth robe") return EARTH_ROBE;
	else if (s == "air robe")   return AIR_ROBE;
	else if (s == "water robe") return WATER_ROBE;

	else if (s == "basic staff") return BASIC_STAFF;
	else if (s == "fire staff")  return FIRE_STAFF;
	else if (s == "earth staff") return EARTH_STAFF;
	else if (s == "air staff")   return AIR_STAFF;
	else if (s == "water staff") return WATER_STAFF;

	else if (s == "health potion") return HEALTH_POTION;

	else return ItemType::NONE;
}