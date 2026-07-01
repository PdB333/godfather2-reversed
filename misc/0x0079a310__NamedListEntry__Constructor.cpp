// FUNC_NAME: NamedListEntry::Constructor
// Address: 0x0079a310
// Role: Constructor for a named list entry, adds to global linked list

class NamedListEntry {
public:
    // vtable pointer at +0x00
    // +0x04: field_04 (param3)
    // +0x08: field_08 (param5)
    // +0x0C: field_0C (param4)
    // +0x10: field_10 (zeroed)
    // +0x14: field_14 (zeroed)
    // +0x18: field_18 (zeroed)
    // +0x1C: field_1C (zeroed)
    // +0x20: name[64] (max 63 chars + null)
    // +0x70: next pointer (linked list)
};

NamedListEntry* __thiscall NamedListEntry::Constructor(NamedListEntry* this, char* name, int param3, int param4, int param5) {
    // Call base constructor (address 0x0064cc90)
    FUN_0064cc90(); // base constructor call

    // Set vtable pointer
    this->vtable = &PTR_LAB_00d6a704;

    // Copy name with length limit (63 characters)
    _strncpy(reinterpret_cast<char*>(reinterpret_cast<uint8_t*>(this) + 0x20), name, 0x3f);

    // Store parameters in specific order
    this->field_04 = param3;   // +0x04
    this->field_0C = param4;   // +0x0C
    this->field_08 = param5;   // +0x08

    // Zero out fields at offsets 0x10 through 0x1C
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    // Link this node into the global singly-linked list
    this->next = DAT_012059ec; // previous head
    DAT_012059ec = this;       // new head

    return this;
}