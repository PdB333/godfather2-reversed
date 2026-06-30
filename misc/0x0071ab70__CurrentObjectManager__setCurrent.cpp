// FUNC_NAME: CurrentObjectManager::setCurrent
// Function at 0x0071ab70: Sets the current active object, updates linked list linkage, and sets a validity flag.
// Known callers: 0x00711c60, 0x0071b4e0, 0x0071b5b0, 0x00767ea0

#include <cstdint>

// Forward declaration of refcount decrement function
void releaseObject(int** objectPtr);

// Class layout (offsets relative to this):
// +0x20: currentPtr (int*) - pointer to current active object
// +0x24: previousNext (int*) - used to maintain list linkage (stores the old next of the inserted object)
// +0x28: allowedList (int**?) - array of 12-byte entries (each entry = int pointer + 8 bytes unknown)
// +0x2c: listCount (uint32) - number of entries in allowedList
// +0x3c: flags (uint32) - bit 2 (0x4) indicates currentPtr is in allowedList

class CurrentObjectManager {
public:
    void __thiscall setCurrent(int* newObject) {
        int** currentSlot = reinterpret_cast<int**>(this + 0x20); // &currentPtr
        int* oldObject = *currentSlot;

        // If the new object is different from current, release old and assign new
        if (oldObject != newObject) {
            if (oldObject != nullptr) {
                releaseObject(currentSlot);
            }
            *currentSlot = newObject;
            if (newObject != nullptr) {
                // Save the old next pointer of the new object into this->previousNext
                *(reinterpret_cast<int**>(this + 0x24)) = *reinterpret_cast<int**>(newObject + 4);
                // Set the new object's next pointer to point back to this->currentPtr field
                *reinterpret_cast<int**>(newObject + 4) = reinterpret_cast<int*>(currentSlot);
            }
        }

        // Now update the validity flag based on whether current is in the allowed list
        if (*currentSlot != nullptr) {
            // Iterate over allowedList (12 bytes per entry, first int is the object pointer)
            int** listEntries = reinterpret_cast<int**>(this + 0x28);
            uint32_t count = *reinterpret_cast<uint32_t*>(this + 0x2c);
            for (uint32_t i = 0; i < count; i++) {
                // Each entry: first field is int* - compare with current
                if (*listEntries == *currentSlot) {
                    // Found, set bit 2 in flags
                    *reinterpret_cast<uint32_t*>(this + 0x3c) |= 4;
                    return;
                }
                // Advance by 3 ints (12 bytes)
                listEntries += 3;
            }
        }
        // Not found or current is null, clear bit 2
        *reinterpret_cast<uint32_t*>(this + 0x3c) &= ~4;
    }
};