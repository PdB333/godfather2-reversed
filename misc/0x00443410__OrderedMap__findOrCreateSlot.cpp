// FUNC_NAME: OrderedMap::findOrCreateSlot

// Reconstructed from 0x00443410
// EARS engine container: sorted key-value map with 2-uint nodes (key, value pointer)
// Object layout: +0x00 uint* pairsArray, +0x04 int count (signed, max > 0)

#include <cstddef>

class OrderedMap {
public:
    // Returns pointer to value slot for given key, or nullptr if key already exists.
    // Inserts new node at sorted position if key not found.
    uint* __thiscall findOrCreateSlot(uint key) {
        int i = 0;
        if (this->count > 0) {
            uint* current = this->pairsArray; // base of sorted key-value pairs (each pair = 2 uints: key, value)
            do {
                if (key == current[0]) {
                    return nullptr; // key already present, no insertion
                }
                if (key < current[0]) {
                    break; // found insertion point
                }
                i++;
                current += 2; // advance to next pair
            } while (i < this->count);
        }
        // Allocate a new node (2 uints) via internal allocator
        uint* newNode = allocatePair(); // FUN_00443910
        if (newNode == nullptr) return nullptr; // allocation failure (not explicit in asm but safe)
        newNode[0] = key;          // store key
        // newNode[1] will hold the value, left uninitialized (caller should write)
        return &newNode[1];        // return pointer to value slot
    }

private:
    uint* pairsArray;  // +0x00: pointer to dynamically allocated array of key-value pairs (sorted by key)
    int count;         // +0x04: number of pairs currently in array

    // Internal allocation function (FUN_00443910) – returns pointer to a new 2-uint block.
    static uint* allocatePair(); // assumed static or global
};