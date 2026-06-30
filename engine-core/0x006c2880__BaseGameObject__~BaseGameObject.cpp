// FUNC_NAME: BaseGameObject::~BaseGameObject
// Function address: 0x006c2880
// Destructor for a base game object (size 0x1b0). Sets destructor vtable and cleans up subobjects.

undefined4* __thiscall BaseGameObject::~BaseGameObject(undefined4* this, byte deleteFlag)
{
    // Set vtable to destructor vtable to prevent virtual calls during destruction
    *this = &PTR_FUN_00d5ef08;                                   // +0x00: vtable pointer
    this[0xf] = &PTR_LAB_00d5eef8;                               // +0x3C: function table or metadata pointer
    this[0x12] = &PTR_LAB_00d5eef4;                               // +0x48: another pointer
    this[0x14] = &PTR_LAB_00d5eef0;                               // +0x50: another pointer

    // Destroy subobject at offset +0x90 if it exists
    if (this[0x24] != 0) {                                        // +0x90: pointer to child/component
        FUN_004daf90(this + 0x24);                                // subobject destructor
    }

    // Call global cleanup (likely static state or manager)
    FUN_00473880();

    // If delete flag is set, free the memory block (size 0x1b0 bytes)
    if ((deleteFlag & 1) != 0) {
        FUN_0043b960(this, 0x1b0);                                // operator delete(this, size)
    }

    return this;
}