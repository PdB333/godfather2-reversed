// FUNC_NAME: InventoryManager::getRandomItem

#include <cstdlib> // for rand()

// Forward declaration for Item struct (size 0x10)
struct InventoryItem {
    uint8_t data[0x10]; // Placeholder, actual fields unknown
};

class InventoryManager {
public:
    // Offset +0x50: Number of items in the inventory
    int itemCount;

    // Offset +0x58: Pointer to array of InventoryItem structures (each 0x10 bytes)
    InventoryItem* items;

    // Returns a pointer to a randomly selected inventory item, or nullptr if empty.
    InventoryItem* __thiscall getRandomItem() {
        if (itemCount <= 0) {
            return nullptr;
        }

        int randomIndex = std::rand() % itemCount;
        // randomIndex is guaranteed to be in [0, itemCount)
        return &items[randomIndex];
    }
};