// FUNC_NAME: EntityDataManager::~EntityDataManager
void __fastcall EntityDataManager::~EntityDataManager(EntityDataManager* this)
{
    // Set vtable to destructor vtable (first step of destruction)
    this->vtable = &PTR_FUN_00d8bfd4;
    this->vtable2 = &PTR_LAB_00d8bfd0;

    // Call cleanup/unregister function with a static callback
    unregisterCleanup(0, &LAB_00953320);

    // Delete all owned objects in the dynamic array
    uint count = this->m_objectCount; // +0x14
    if (count != 0) {
        uint i = 0;
        do {
            void* obj = *(void**)(this->m_objects + i * 4); // +0x10
            if (obj != nullptr) {
                // Call virtual destructor/release with argument 1
                (*(void(__thiscall**)(void*, int))obj)(obj, 1);
            }
            i++;
        } while (i < count);
    }

    // Free the array memory
    if (this->m_objects != 0) {
        operatorDelete(this->m_objects); // FUN_009c8f10
    }

    // Update vtable to base class destructor vtable
    this->vtable2 = &PTR_LAB_00d8bfcc;
    // Clear global singleton flag
    g_entityDataManagerDestroyed = 0; // DAT_011307c4
    // Final vtable assignment (likely base class)
    this->vtable = &PTR_LAB_00e3e74c;
}