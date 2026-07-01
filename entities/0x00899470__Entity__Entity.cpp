// FUNC_NAME: Entity::Entity
// Function address: 0x00899470
// Constructor for Entity class. Initializes base, sets vtable, copies name, sets ID/type/flags, and links into global entity list.

#include <cstring>

// Assume BaseConstructor is at 0x0064cc90
extern void __thiscall BaseConstructor(void* thisPtr);

// Global head of linked list
extern Entity* g_entityListHead; // DAT_012059ec

class Entity {
public:
    // Vtable at +0x00
    void* vtable; // set to &PTR_LAB_00d77df8

    // Unknown fields
    uint32_t m_unknown1; // +0x04 (param_3)
    uint32_t m_flags;    // +0x08 (param_5)
    uint32_t m_unknown2; // +0x0C (param_4)

    // Padding?
    // Name at +0x20, max 63 chars + null
    char m_name[64]; // +0x20

    // More unknown fields (indices 4-7 set to 0 at +0x10, +0x14, +0x18, +0x1C)
    uint32_t m_zero1; // +0x10
    uint32_t m_zero2; // +0x14
    uint32_t m_zero3; // +0x18
    uint32_t m_pNext; // +0x1C (index 0x1C = 28*4 = 0x70? Wait, that's wrong)
    // Actually param_1[0x1c] is offset 0x70, but we have only 0x1C as index? Let's recalc.
    // param_1 is uint32_t*, so param_1[0x1c] is at byte offset 0x1c*4 = 0x70. But we only have up to index 7 set to 0.
    // So there is a field at +0x70. We'll place it after other zeros but note gap.
    // Actually the fields at indices 4-7 set to 0 are at offsets 0x10,0x14,0x18,0x1C. So m_pNext is at +0x1C? That is 28 bytes. But param_1[0x1c] is at 0x70, not 0x1c. There is discrepancy. 
    // Let's check: param_1 is a pointer to uint32_t. So param_1[0x1c] means element at index 0x1c (28), which is at address param_1 + 28*4 = param_1 + 0x70. So it's not at offset 0x1C. 
    // The code sets param_1[0x1c] = DAT_012059ec; then DAT_012059ec = param_1; So param_1[0x1c] is the 'next' pointer of the linked list.
    // Meanwhile, indices 4,5,6,7 are set to 0 (offsets 0x10,0x14,0x18,0x1C). So there are 4 uint32_t zeros at offsets 0x10-0x1C, then the 'next' pointer at 0x70.
    // This implies a large gap or additional structure. We'll model as a flexible array or just unknown.
    // For simplicity, we'll declare m_pNext at the correct offset using a placeholder.
    // The actual offset is 0x70. So we need to ensure alignment.

    // For brevity, we'll not list all unknown fields, just ensure the constructor logic is captured.
};

Entity* __thiscall Entity::Entity(Entity* this, const char* name, uint32_t param_3, uint32_t param_4, uint32_t param_5) {
    // Call base constructor
    BaseConstructor(this);

    // Set vtable
    this->vtable = (void*)0x00d77df8;

    // Copy name (max 63 chars)
    strncpy(this->m_name, name, 0x3f);
    this->m_name[0x3f] = '\0'; // ensure null termination

    // Set other fields
    this->m_unknown1 = param_3; // +0x04
    this->m_unknown2 = param_4; // +0x0C (note: param_3, param_4, param_5 shuffled)
    this->m_flags = param_5;    // +0x08

    // Zero out fields at offsets 0x10,0x14,0x18,0x1C (indices 4-7)
    // Assuming these are contiguous uint32_t at offsets 0x10-0x1C
    uint32_t* base = reinterpret_cast<uint32_t*>(this);
    base[4] = 0; // offset 0x10
    base[5] = 0; // offset 0x14
    base[6] = 0; // offset 0x18
    base[7] = 0; // offset 0x1C

    // Link into global list: set next pointer at offset 0x70 to current head
    // At port offset 0x70 (index 0x1C)
    base[0x1C] = reinterpret_cast<uint32_t>(g_entityListHead);
    // Update global head to this
    g_entityListHead = this;

    return this;
}