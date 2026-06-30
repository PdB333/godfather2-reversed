// FUNC_NAME: BaseObject::~BaseObject
// Address: 0x00760290
// Role: Base class destructor – cleans up three sub-objects at offsets 0x4, 0x10, 0x20 (dword indices 1,4,8)
//        then swaps vtable to purecall, and conditionally frees memory (param_2 & 1).

void __thiscall BaseObject::~BaseObject(BaseObject* thisObj, byte freeMemoryFlag)
{
    // Set vtable to original (most likely redundant when called directly, but used by derived dtors)
    thisObj->vtablePtr = &PTR_FUN_00d653ec;

    // Destroy sub-object at offset 0x20 (if not null)
    if (thisObj->subObject3 != nullptr)
    {
        FUN_004daf90(reinterpret_cast<int*>(&thisObj->subObject3)); // sub-object dtor
    }
    // Destroy sub-object at offset 0x10
    if (thisObj->subObject2 != nullptr)
    {
        FUN_004daf90(reinterpret_cast<int*>(&thisObj->subObject2));
    }
    // Destroy sub-object at offset 0x04
    if (thisObj->firstSubObject != nullptr)
    {
        FUN_004daf90(reinterpret_cast<int*>(&thisObj->firstSubObject));
    }

    // Replace vtable with purecall trap (prevents accidental virtual calls after destruction)
    thisObj->vtablePtr = &PTR___purecall_00e407a4;

    // If low bit of freeMemoryFlag is set, free the memory (e.g., operator delete)
    if ((freeMemoryFlag & 1) != 0)
    {
        FUN_009c8eb0(thisObj);
    }
}