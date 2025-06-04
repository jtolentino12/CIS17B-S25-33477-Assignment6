#include "StoredItem.h"

StoredItem::StoredItem(std::string id, std::string desc, std::string loc)
    : id(id), description(desc), location(loc) {}

std::string StoredItem::getId() const { return id; }
std::string StoredItem::getDescription() const { return description; }
std::string StoredItem::getLocation() const { return location; }
