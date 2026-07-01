// FUNC_NAME: NamedResourceNode::NamedResourceNode

// Structure: NamedResourceNode
// Offsets:
// +0x00: vtable pointer (via base class)
// +0x04: fieldParamA (param_3)
// +0x08: fieldParamB (param_5) [note swapped order in original: param_5 stored at +0x08]
// +0x0C: fieldParamC (param_4)
// +0x10: fieldCounter1 (zeroed)
// +0x14: fieldCounter2 (zeroed)
// +0x18: fieldCounter3 (zeroed)
// +0x1C: fieldCounter4 (zeroed)
// +0x20: name[64] (0x40 bytes, null-terminated)
// +0x70: pNext (linked list pointer)

extern NamedResourceNode* g_resourceListHead; // formerly DAT_012059ec

NamedResourceNode* __thiscall NamedResourceNode::NamedResourceNode(NamedResourceNode* this, char* name, undefined4 paramA, undefined4 paramB, undefined4 paramC)
{
    // Call base class constructor (if any) – currently unknown
    someBaseInit(); // FUN_0064cc90

    this->vtable = &vtable_NamedResourceNode; // PTR_LAB_00d7e080

    // Copy name with maximum length 63 characters (64 bytes including null)
    _strncpy(this->name, name, 0x3f);

    this->fieldParamA = paramA;   // +0x04
    this->fieldParamC = paramC;   // +0x0c
    this->fieldParamB = paramB;   // +0x08

    // Initialize four counter/reserved fields to zero
    this->fieldCounter1 = 0; // +0x10
    this->fieldCounter2 = 0; // +0x14
    this->fieldCounter3 = 0; // +0x18
    this->fieldCounter4 = 0; // +0x1c

    // Insert this node at the head of the global linked list
    this->pNext = g_resourceListHead; // +0x70
    g_resourceListHead = this;

    return this;
}