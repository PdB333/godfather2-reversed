// FUNC_NAME: NamedRegistryEntry::NamedRegistryEntry
// Function at 0x007fa240 - Constructor for a named registry entry with linked list insertion
// This appears to be a base class constructor for an entry in a global registry (e.g., string-named objects)
// Structure layout (offsets in bytes from this):
// +0x00: vtable pointer
// +0x08: name string (63 chars max, null-terminated)
// +0x04: field1 (param3, likely an ID)
// +0x0C: field2 (param4, another ID)
// +0x08? Actually careful: index 1 -> offset 4, index 2 -> offset 8, index 3 -> offset 12, etc.
// From param_1[1], param_1[2], param_1[3] offsets: 0x4, 0x8, 0xC
// index 0x1c -> offset 0x70: next pointer
// +0x70: pointer to next entry in singly-linked list
// global head pointer at DAT_012059ec

undefined4 * __thiscall NamedRegistryEntry::NamedRegistryEntry(undefined4 *this, char *name, undefined4 id1, undefined4 id2, undefined4 id3)
{
    // Call base class constructor (likely initializes some base fields)
    Base::Base(); // FUN_0064cc90 - possibly a base object constructor
    
    // Set vtable pointer to this class's virtual table
    *this = &PTR_LAB_00d71d44;
    
    // Copy the name string (up to 63 characters) to offset +0x20 (index 8, which is 8*4=32 bytes from this)
    // But param_1+8 is actually this+8 (in pointer arithmetic, param_1 is undefined4*, so adding 8 means 32 bytes)
    // The strncpy writes to (char*)(this+8) which is 32 bytes into the structure.
    _strncpy((char *)(this + 8), name, 0x3f); // +0x20 offset for name
    
    // Initialize fields at offsets 4, 8, 12 (index 1,2,3)
    this[1] = id1;   // +0x04
    this[3] = id2;   // +0x0C
    this[2] = id3;   // +0x08
    
    // Initialize next pointers to null
    this[4] = 0;     // +0x10
    this[5] = 0;     // +0x14
    this[6] = 0;     // +0x18
    this[7] = 0;     // +0x1C? Actually index 7 -> 0x1C, but notice next is at index 0x1C = 28. So indices 4-7 are intermediate fields.
    // Actually index 0x1C = 28, so next pointer is at offset 112 bytes. The above indices 4-7 are offsets 16-28 bytes, which might be other fields.
    
    // Insert this entry at head of global linked list (singly linked list via next pointer at offset 0x70)
    this[0x1c] = DAT_012059ec;  // this->next = g_head
    DAT_012059ec = this;         // g_head = this
    
    return this;
}