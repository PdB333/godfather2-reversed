// FUNC_NAME: Node::assign
// Function address: 0x008c96f0
// Reconstructed C++ for EA EARS engine intrusive list node assignment/copy constructor.
// This function copies data from source node (param_2) into this node, maintaining linked list integrity.
// It appears to be a copy assignment that also repositions this node in the list to point to the same next as source.
// The node structure:
// +0x00: vtable pointer (set to PTR_FUN_00d76628)
// +0x04: unknown (set to 0)
// +0x08: next pointer (intrusive linked list)
// +0x0c: prev pointer
// +0x10 to +0x40: data payload (0x30 bytes copied from source)

#include <cstdint>

// Forward declaration of the detach function (FUN_004daf90)
extern void detachNode(void* nodeNextPtr); // likely detaches node from current list

class Node {
public:
    // VTable pointer; actual class type determined by vtable
    uintptr_t* vtable;

    // Unknown field, usually zero
    uint32_t field_0x04;

    // Next node in intrusive list
    Node* next;

    // Previous node in intrusive list
    Node* prev;

    // Data payload (size 0x30 bytes, offsets 0x10 to 0x40)
    uint8_t data[0x30];

    // Assignment/copy constructor: copies from source and adjusts list pointers
    // Returns this pointer
    Node* assign(Node* source) {
        // Set vtable
        vtable = &PTR_FUN_00d76628;  // external symbol

        // Clear unknown field
        field_0x04 = 0;

        // Clear initial list pointers
        next = nullptr;
        prev = nullptr;

        // Process linked list update: copy next pointer from source,
        // but only if this node's next pointer does not already match
        if (next != source->next) {
            Node* newNext = source->next;
            // If we currently have a next node, detach from it
            if (next != nullptr) {
                detachNode(next);
            }
            // Set new next
            next = newNext;
            // If new next is not null, update its previous pointer to point to this
            if (newNext != nullptr) {
                this->prev = newNext->prev;  // copy previous of newNext? Actually reads newNext->prev (offset +0x0c)
                newNext->prev = this;        // make newNext point back to this
            }
        }

        // Copy data payload from source (offsets 0x10 to 0x40)
        // Individual field copies as per decompilation:
        // This can be replaced with memcpy for clarity, but original uses per-field copies.
        // For accurate reconstruction, we preserve the per-field assignment.
        *(uint32_t*)(data + 0x00) = *(uint32_t*)(source->data + 0x00);                    // offset 0x10
        *(uint64_t*)(data + 0x04) = *(uint64_t*)(source->data + 0x04);                    // offset 0x14 (8 bytes)
        *(uint32_t*)(data + 0x0c) = *(uint32_t*)(source->data + 0x0c);                    // offset 0x1c
        *(uint64_t*)(data + 0x10) = *(uint64_t*)(source->data + 0x10);                    // offset 0x20 (8 bytes)
        *(uint32_t*)(data + 0x18) = *(uint32_t*)(source->data + 0x18);                    // offset 0x28
        *(uint32_t*)(data + 0x1c) = *(uint32_t*)(source->data + 0x1c);                    // offset 0x2c
        *(uint32_t*)(data + 0x20) = *(uint32_t*)(source->data + 0x20);                    // offset 0x30
        *(uint32_t*)(data + 0x24) = *(uint32_t*)(source->data + 0x24);                    // offset 0x34
        *(uint32_t*)(data + 0x28) = *(uint32_t*)(source->data + 0x28);                    // offset 0x38
        *(uint32_t*)(data + 0x2c) = *(uint32_t*)(source->data + 0x2c);                    // offset 0x3c
        // Note: offset 0x40 is the last copied dword (data + 0x30)
        *(uint32_t*)(data + 0x30) = *(uint32_t*)(source->data + 0x30);                    // offset 0x40

        return this;
    }
};
// The external vtable symbol
extern uintptr_t PTR_FUN_00d76628;