#include "StorageManager.h"

void StorageManager::addItem(const std::shared_ptr<StoredItem>& item) {
    if (itemById.find(item->getId()) != itemById.end()) {
        throw DuplicateItemException("Item with ID " + item->getId() + " already exists.");
    }
    itemById[item->getId()] = item;
    itemByDescription[item->getDescription()] = item;
}

std::shared_ptr<StoredItem> StorageManager::findById(const std::string& id) const {
    auto it = itemById.find(id);
    if (it == itemById.end()) {
        throw ItemNotFoundException("Item with ID " + id + " not found.");
    }
    return it->second;
}

void StorageManager::removeItem(const std::string& id) {
    auto it = itemById.find(id);
    if (it == itemById.end()) {
        throw ItemNotFoundException("Cannot remove. Item with ID " + id + " not found.");
    }
    itemByDescription.erase(it->second->getDescription());
    itemById.erase(it);
}

std::vector<std::shared_ptr<StoredItem>> StorageManager::listItemsByDescription() const {
    std::vector<std::shared_ptr<StoredItem>> items;
    for (const auto& pair : itemByDescription) {
        items.push_back(pair.second);
    }
    return items;
}
