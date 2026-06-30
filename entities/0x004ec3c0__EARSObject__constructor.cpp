// FUNC_NAME: EARSObject::constructor
// Address: 0x004ec3c0
// Constructor for EARSObject base class. Sets vtable, initializes reference count to 0,
// and assigns an object ID. If objectId is -1, generates a new unique ID from a static counter.

void __thiscall EARSObject::constructor(EARSObject* this, int objectId)
{
    // +0x00: vtable pointer
    // +0x04: reference count (int)
    // +0x08: object ID (int)
    this->refCount = 0;
    this->vtablePtr = &PTR_LAB_00e372c4; // vtable for EARSObject
    if (objectId != -1) {
        this->objectId = objectId;
        return;
    }
    // Generate new ID from static counter
    this->objectId = s_nextObjectId;
    s_nextObjectId++;
}