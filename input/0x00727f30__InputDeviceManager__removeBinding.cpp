// FUNC_NAME: InputDeviceManager::removeBinding
// Function address: 0x00727f30
// Removes a binding object from one of the 4 controller slots.
// Each slot maintains a linear array of binding node pointers (8-byte entries).
// The binding object has a linked‑list node at offset +0x48.
// The function searches each slot for the node, removes it from the slot's array
// and from its linked list, then calls a callback with the slot index where it was found.

#include <cstdint>

// ----------------------------------------------------------------------------
// Forward declarations of helper functions (defined elsewhere in the binary)
// ----------------------------------------------------------------------------
extern bool __fastcall isSlotActive(uint32_t slotIndex);
extern void __fastcall removeNodeFromList(void* node);   // uses dummy‑node trick
extern void __fastcall onSlotRemoved(uint32_t foundIndex);

// ----------------------------------------------------------------------------
// InputDeviceManager::removeBinding
// ----------------------------------------------------------------------------
void __thiscall InputDeviceManager::removeBinding(void* thisPtr, void* binding) {
    // Layout of this object at offset +0x10:
    // struct SlotDescriptor {
    //     void**  entries;       // +0x00: pointer to array of binding node pointers (each 8 bytes)
    //     uint32_t entryCount;   // +0x04: number of entries in the array
    //     uint32_t _padding;     // +0x08
    // } slots[4];

    struct SlotDescriptor {
        void**  entries;
        uint32_t entryCount;
        uint32_t _padding;
    };

    SlotDescriptor* slot = reinterpret_cast<SlotDescriptor*>(
        reinterpret_cast<char*>(thisPtr) + 0x10);

    for (uint32_t slotIndex = 0; slotIndex < 4; ++slotIndex, ++slot) {
        if (!isSlotActive(slotIndex)) {
            continue;
        }

        // Determine the target node: if binding is non‑null, node is at binding+0x48
        void* targetNode = (binding != nullptr)
            ? reinterpret_cast<char*>(binding) + 0x48
            : nullptr;

        // If targetNode exists, prepare a dummy node on the stack for unlinking.
        // We save the node's original next pointer and then redirect it to the dummy.
        void* dummyNode = nullptr;
        if (targetNode != nullptr) {
            void* savedNext = *reinterpret_cast<void**>(
                static_cast<char*>(targetNode) + 4);
            *reinterpret_cast<void**>(
                static_cast<char*>(targetNode) + 4) = &dummyNode;
        }

        // Search the current slot's entry array for a match
        uint32_t foundIndex = 0xFFFFFFFF;
        for (uint32_t i = 0; i < slot->entryCount; ++i) {
            // Each entry is two pointers (8 bytes); the first is the node pointer.
            if (slot->entries[i * 2] == targetNode) {
                foundIndex = i;
                break;
            }
        }

        // If a target node existed, remove it from its linked list
        if (targetNode != nullptr) {
            removeNodeFromList(&dummyNode);
        }

        // Notify the removal at the found index (0xFFFFFFFF indicates not found)
        onSlotRemoved(foundIndex);
    }
}