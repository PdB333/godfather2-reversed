// FUNC_NAME: NamedObject::NamedObject
// Constructor for a named object that is stored in a global singly-linked list.
// The base constructor FUN_0064cc90 is called first (likely initializing vtable or base fields).
// Parameters: name (string up to 63 chars + null), data1, data2, data3 (unknown usage).
// Layout:
//   +0x00: vftable pointer (set to &PTR_LAB_00d79c40)
//   +0x04: data1
//   +0x08: data3
//   +0x0C: data2  (note param_4 is stored at index 3)
//   +0x10: 0 (initialized)
//   +0x14: 0
//   +0x18: 0
//   +0x1C: 0
//   +0x20: char name[64]
//   +0x70: pointer to previous head of global list (DAT_012059ec)
// Global: DAT_012059ec is updated to point to this new object.

void __thiscall NamedObject__Constructor(NamedObject* thisObj, const char* name, int data1, int data2, int data3)
{
    // Call base class constructor (assumed void __thiscall baseConstructor(void*))
    baseConstructor(thisObj);

    // Set vftable
    thisObj->vftable = &PTR_LAB_00d79c40;

    // Copy name string with limit
    strncpy(thisObj->name, name, 0x3f);
    thisObj->name[0x3f] = '\0'; // Ensure null termination

    // Assign data parameters
    thisObj->data1 = data1;
    thisObj->data3 = data3;
    thisObj->data2 = data2;

    // Zero out four fields
    thisObj->field_10 = 0;
    thisObj->field_14 = 0;
    thisObj->field_18 = 0;
    thisObj->field_1C = 0;

    // Link into global singly-linked list (store previous head)
    thisObj->next = DAT_012059ec; // offset 0x70
    DAT_012059ec = thisObj;

    return;
}