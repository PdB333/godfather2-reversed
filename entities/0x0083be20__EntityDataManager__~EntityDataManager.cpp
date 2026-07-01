// FUNC_NAME: EntityDataManager::~EntityDataManager

void EntityDataManager::~EntityDataManager()
{
    // Set vtable to this class's vtable to ensure correct virtual dispatch during destruction
    this->vtable = &EntityDataManager_vtable; // PTR_FUN_00d742f0

    // Array of 256 sub-objects at offset 0xC28 (this + 0x30a * 4)
    // Each sub-object is 12 bytes (3 ints) with structure:
    //   +0x00 handle        (if non-zero, sub-object is allocated)
    //   +0x04 field_4
    //   +0x08 field_8
    struct SubObject { int handle; int field_4; int field_8; };
    SubObject* arr = reinterpret_cast<SubObject*>(reinterpret_cast<char*>(this) + 0xC28);

    // Iterate backwards over all 256 sub-objects
    for (int i = 255; i >= 0; i--)
    {
        SubObject& obj = arr[i];
        if (obj.handle != 0)
        {
            // Destroy the sub-object (free memory / release resources)
            FUN_004daf90(&obj); // SubObject::destroy or analogous cleanup
        }
    }

    // Set vtable to purecall to prevent any further virtual calls after destruction
    this->vtable = &purecall_vtable; // PTR___purecall_00e407a4
}