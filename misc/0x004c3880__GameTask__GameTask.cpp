// FUNC_NAME: GameTask::GameTask
int __thiscall GameTask::GameTask(GameTask* this, void* owner)
{
    // Debug trace call with message ID 6 and a global string
    debugPrint(6, DAT_00e35654);

    // Zero-initialize a block of fields (likely state flags or child pointers)
    this->someField0 = 0;       // +0x1c
    this->someField1 = 0;       // +0x20
    this->someField2 = 0;       // +0x24
    this->someField3 = 0;       // +0x28
    this->someField4 = 0;       // +0x2c
    this->someField5 = 0;       // +0x30

    // Store owner reference
    this->owner = owner;        // +0x18

    // Self-pointer for later internal use
    this->selfPtr = this;       // +0x34

    // Duplicate owner reference (maybe for a different purpose)
    this->ownerCopy = owner;    // +0x38

    // Zero-initialize more fields (possibly child list or state machine)
    this->field3C = 0;          // +0x3c
    this->field40 = 0;          // +0x40
    this->field44 = 0;          // +0x44
    this->field48 = 0;          // +0x48

    // Set a sentinel/marker to -1 (often used for "invalid" or "no index")
    this->invalidIndex = -1;    // +0x4c

    // Register with the parent object; owner is treated as a pointer-to-pointer
    // and we pass the dereferenced parent object (e.g., a scene graph node)
    registerWithParent(*(void**)owner); // +0x18 -> deref to get parent pointer

    return this;
}