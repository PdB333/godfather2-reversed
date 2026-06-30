// FUNC_NAME: HandlerManager::setHandlerSlot
// Function address: 0x00542e80
// Reconstructed from Ghidra decompilation for The Godfather 2 (x86, EARS engine)
// This function manages an array of handler slots (each 8 bytes: {ownerPtr, nextPtr}) used for linked list insertion.

#include <cstdint>

class HandlerManager {
public:
    // Virtual function table offset 0x214 (0x85*4): checks if a handler ID is valid.
    virtual bool isHandlerValid(int handlerId, int* pHandlerId) = 0;

    // Updates a handler slot at the given index.
    // param1: slotIndex - index into the handler array
    // param2: handlerId - identifier used to validate the handler
    // param3: listOwner - pointer to an object containing a list head at offset +0x48 (or 0 to detach)
    // Returns true if the slot was updated, false if not.
    // Note: The ESI register may hold the listOwner pointer; it is treated as a parameter here.
    bool setHandlerSlot(int slotIndex, int handlerId, void* listOwner) {
        // Call virtual function to check if handlerId is valid.
        if (!isHandlerValid(handlerId, &handlerId)) {
            return false;
        }

        // Array of handler slots is at this + 0x2B8 (0xAE * 4)
        // Each slot is 8 bytes: first int = owner pointer, second int = next pointer
        HandlerSlot* slotArray = reinterpret_cast<HandlerSlot*>(this->handlerArray);
        HandlerSlot* slot = &slotArray[slotIndex]; // slotIndex used as multiplier (8 bytes each)

        int currentOwner = slot->ownerPtr; // first int of the slot

        // Condition to allow update: currentOwner is 0 or 0x48, or listOwner is null.
        if (currentOwner == 0 || currentOwner == 0x48 || listOwner == nullptr) {
            // Compute new owner: if listOwner is null, use 0; otherwise use listOwner + 0x48 (list head inside object)
            int* newOwner = (listOwner != nullptr) ? reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(listOwner) + 0x48) : nullptr;

            if (slot->ownerPtr != reinterpret_cast<int>(newOwner)) {
                // Remove old connection if it existed (function at 0x004daf90 unlinks a slot)
                if (slot->ownerPtr != 0) {
                    removeHandlerSlot(slot);
                }

                slot->ownerPtr = reinterpret_cast<int>(newOwner);

                if (newOwner != nullptr) {
                    // Insert slot after the newOwner node in a singly linked list.
                    // newOwner + 4 points to the "next" pointer of the head node.
                    slot->nextPtr = *(reinterpret_cast<int*>(newOwner) + 1); // *(newOwner + 4)
                    *reinterpret_cast<int**>(reinterpret_cast<uint8_t*>(newOwner) + 4) = &slot->nextPtr; // newOwner->next = &slot->nextPtr
                    // Note: This assumes the slot's nextPtr is directly after ownerPtr in the struct.
                }
                return true;
            }
        }
        return false;
    }

private:
    // Structure for each handler slot (8 bytes)
    struct HandlerSlot {
        int ownerPtr;   // pointer to the list head owner (or 0)
        int nextPtr;    // next node in the list (if linked)
    };

    // Placeholder for the handler array (size unknown)
    // Offset +0x2B8 from this
    /* 0x2B8 */ HandlerSlot handlerArray[?]; // actual size depends on implementation

    // Helper function to remove a slot from its list (called from 0x004daf90)
    void removeHandlerSlot(HandlerSlot* slot);
};

// Note: The actual signature and base class may differ. 
// The virtual function isHandlerValid takes two ints; the second is a pointer to the first.
// The listOwner pointer is passed in ESI in the original binary; here it's an explicit parameter.
// The constant 0x48 likely represents the size or offset of a member structure.