// FUNC_NAME: EntityGUIDMap::Find
// Address: 0x005faf10
// Role: Searches a linked list container for a data node matching a 128-bit (4-int) key.
// The container holds a sentinel node at offset +0x28 (this->mSentinel).
// Each node has a next pointer at offset 0, a data pointer at offset 8 (node[2]).
// The data block has the 4-int key at offsets 0x10, 0x14, 0x18, 0x1c.

#include <cstdint>

// Forward declare the node structure used internally
struct GUIDListNode {
    GUIDListNode* mNext;  // +0x00
    GUIDListNode* mPrev;  // +0x04 (unused in this function)
    void* mData;          // +0x08 (pointer to the actual data block)
};

// The data block that contains the key
struct GUIDData {
    // ... other fields ...
    int mKey0; // +0x10
    int mKey1; // +0x14
    int mKey2; // +0x18
    int mKey3; // +0x1c
};

class EntityGUIDMap {
public:
    // Find an entry by its 4-int key (GUID).
    // Returns pointer to the data if found, nullptr otherwise.
    void* Find(const int key[4]) {
        // Quick exit for zero key (invalid)
        if ((key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0)) {
            return nullptr;
        }

        // Get the sentinel node stored at this+0x28
        GUIDListNode* sentinel = reinterpret_cast<GUIDListNode*>(mSentinelPtr);

        // Start from the first real node (sentinel->mNext)
        GUIDListNode* currentNode = sentinel->mNext;
        void* result = nullptr;

        while (currentNode != sentinel) {
            // Assert that we haven't wrapped around incorrectly (debug)
            if (currentNode == sentinel) {
                __debugbreak(); // FUN_00b97aea - assertion failure
            }

            // Access the data block
            GUIDData* data = static_cast<GUIDData*>(currentNode->mData);

            // Compare all four key components
            if (data->mKey0 == key[0] &&
                data->mKey1 == key[1] &&
                data->mKey2 == key[2] &&
                data->mKey3 == key[3]) {
                result = data;
            }

            // Another sentinel check (unlikely but present in original)
            if (currentNode == sentinel) {
                __debugbreak();
            }

            // Move to next node
            currentNode = currentNode->mNext;

            // If we already found the match, return immediately
            if (result != nullptr) {
                return result;
            }
        }

        return result; // nullptr if not found
    }

private:
    // At offset +0x28, a pointer to the sentinel node
    // The sentinel node is part of a circular doubly linked list.
    // The actual data nodes are stored between sentinel->mNext and sentinel.
    uint32_t mSentinelPtr; // actually a pointer to GUIDListNode, stored as uint32 for alignment
};