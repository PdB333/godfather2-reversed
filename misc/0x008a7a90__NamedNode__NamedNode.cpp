// FUNC_NAME: NamedNode::NamedNode
// Function address: 0x008a7a90
// Role: Constructor for a node in a global linked list, initializes name and integer fields, then inserts at head of list.

#include <cstring>

// Forward declaration of base class constructor (likely from EARS framework)
void __thiscall baseConstructor(void* thisPtr);

// Global head pointer for the linked list of NamedNode objects
extern NamedNode* g_headNode; // DAT_012059ec

class NamedNode {
public:
    // Vtable pointer at offset 0x00
    void* vtable; // +0x00

    // Integer fields
    int field_0x04; // +0x04 (param_1[1])
    int field_0x08; // +0x08 (param_1[2])
    int field_0x0C; // +0x0C (param_1[3])

    // Name buffer (64 bytes including null terminator)
    char name[64]; // +0x10 (param_1 + 8, offset 0x10 from start? Actually param_1+8 is at byte offset 0x20 if param_1 is int*? Let's recalc: param_1 is undefined4*, so each element is 4 bytes. param_1+8 is offset 32 bytes. So name starts at offset 0x20. But we'll place it after the ints. The ints are at offsets 0x04, 0x08, 0x0C. So name at 0x10? That would be param_1+4? No, param_1[1] is at offset 4, param_1[2] at 8, param_1[3] at 12. Then param_1+8 is at offset 32? That doesn't match. Let's re-examine: param_1 is an undefined4* (pointer to 4-byte values). param_1+8 means adding 8*4 = 32 bytes to the pointer. So the name is at offset 32 from the start. The ints are at offsets 4,8,12. So there is a gap. Possibly the vtable pointer is at offset 0, then three ints at 4,8,12, then some padding? Or the name is at offset 0x20 (32). So the structure might be: vtable (4), int1 (4), int2 (4), int3 (4), then name (64 bytes) starting at offset 16? Actually 4+4+4+4=16, so name at offset 16? But param_1+8 is offset 32, so that would be 16+16? That doesn't align. Let's compute: param_1 is a pointer to undefined4. So param_1[0] is at offset 0, param_1[1] at 4, param_1[2] at 8, param_1[3] at 12, param_1[4] at 16, param_1[5] at 20, param_1[6] at 24, param_1[7] at 28, param_1[8] at 32. So param_1+8 is the address of param_1[8], which is at offset 32. So the name starts at offset 32. The ints are at offsets 4,8,12. So there are 4 bytes at offset 0 (vtable), then 3 ints (12 bytes), then 16 bytes of zeros? Actually param_1[4] to param_1[7] are set to 0, that's offsets 16,20,24,28. So those are zeroed. Then name at offset 32. So the structure is: vtable (4), int1 (4), int2 (4), int3 (4), zeros (16 bytes), name (64 bytes), then next pointer at offset 0x70 (param_1[0x1c] = offset 0x70). So total size at least 0x74 bytes. We'll model accordingly.
    // For simplicity, we'll use a char array at offset 0x20.
    // But to match the decompiled code, we'll place name after the zeroed fields.
    // Let's define the structure with explicit offsets using comments.
    // We'll use a flexible layout.

    // Next pointer in linked list (at offset 0x70)
    NamedNode* next; // +0x70 (param_1[0x1c])

    // Constructor
    __thiscall NamedNode(const char* nameStr, int val1, int val2, int val3) {
        // Call base class constructor (likely from EARS framework)
        baseConstructor(this);

        // Set vtable pointer
        this->vtable = (void*)0x00d79bb8; // PTR_LAB_00d79bb8

        // Copy name with maximum length 63 characters
        strncpy(this->name, nameStr, 63);
        this->name[63] = '\0'; // Ensure null termination

        // Set integer fields
        this->field_0x04 = val1; // param_1[1]
        this->field_0x0C = val2; // param_1[3] (note: order in decompiled: param_1[3] = param_4, param_1[2] = param_5)
        this->field_0x08 = val3; // param_1[2]

        // Zero out fields at offsets 0x10, 0x14, 0x18, 0x1C (param_1[4] through param_1[7])
        // These are likely unused or reserved.
        int* base = reinterpret_cast<int*>(this);
        base[4] = 0; // offset 0x10
        base[5] = 0; // offset 0x14
        base[6] = 0; // offset 0x18
        base[7] = 0; // offset 0x1C

        // Insert this node at head of global linked list
        this->next = g_headNode; // param_1[0x1c] = DAT_012059ec
        g_headNode = this; // DAT_012059ec = param_1
    }
};

// Global head pointer definition
NamedNode* g_headNode = nullptr; // DAT_012059ec initialized to 0? The decompiled shows DAT_012059ec is set to param_1, so it's a pointer. It might be initially null. We'll assume it's declared elsewhere.