#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "StoredItem.h"
#include "ItemNotFoundException.h"
#include "DuplicateItemException.h"
#include <unordered_map>
#include <map>
#include <memory>
#include <vector>

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item);
    std::shared_ptr<StoredItem> findById(const std::string& id) const;
    void removeItem(const std::string& id);
    std::vector<std::shared_ptr<StoredItem>> listItemsByDescription() const;
};

#endif // STORAGEMANAGER_H
