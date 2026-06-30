// FUNC_NAME: FocusList::setCurrentIndex

#include <cstdint>

// Forward declaration of the item type
struct FocusItem {
    // +0x28: some flag related to being new selection
    uint32_t newFlag; // unknown exact meaning
    // +0x38: some flag related to old selection
    uint32_t oldFlag;
    // +0x54: property to clear on new item
    uint32_t propNew;
    // +0x5c: property to clear on old item
    uint32_t propOld;
};

// Global absolute function; likely clears a property at given address to given value
extern void setProperty(uint32_t addr, uint32_t value); // FUN_00402050

class FocusList {
public:
    // +0x10: pointer to array of pointers to FocusItem
    FocusItem** items;
    // +0x1c: current selected index (-1 for none)
    int32_t currentIndex;
    // +0x20: reentrancy guard counter
    uint32_t guardCounter;

    void setCurrentIndex(int32_t newIndex) {
        // Enter critical section
        guardCounter++;

        int32_t oldIndex = currentIndex;

        if (newIndex != oldIndex) {
            FocusItem* oldItem = (oldIndex == -1) ? nullptr : items[oldIndex];
            FocusItem* newItem = (newIndex == -1) ? nullptr : items[newIndex];

            // Only perform the update if guard counter is low enough (prevents deep recursion)
            if (guardCounter < 10) {
                currentIndex = newIndex;

                // Clear old item's property if it has the oldFlag set
                if (oldItem != nullptr && oldItem->oldFlag != 0) {
                    setProperty((uint32_t)&oldItem->propOld, 0);
                }

                // If the newIndex was actually set (no race condition), clear new item's property
                if (newIndex == currentIndex && newItem != nullptr && newItem->newFlag != 0) {
                    setProperty((uint32_t)&newItem->propNew, 0);
                }
            }
        }

        // Leave critical section
        guardCounter--;
    }
};