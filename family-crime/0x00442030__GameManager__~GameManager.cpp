// FUNC_NAME: GameManager::~GameManager
void __fastcall GameManager::destroy(GameManager* this)
{
    // vtable setup at object start
    this->vtable0 = &PTR_FUN_00e31104;               // +0x00
    this->field_08 = &PTR_LAB_00e31110;              // +0x08
    this->field_0C = &PTR_LAB_00e31120;              // +0x0C

    // Deregister or notify with a resource ID
    ResourceSystem::deregister(0xe60b027d);

    // Destroy child object if present
    if (this->childObject != nullptr)                // +0x24
    {
        ChildObject::destroy(this->childObject);     // FUN_00442370
    }

    // Release child via virtual call on allocator
    // allocator is at +0x14, its vtable+4 is a Release method
    Allocator* alloc = this->allocator;               // +0x14
    alloc->release(this->childObject, 0);             // virtual call (vtable+4)

    // Clear child pointer and release secondary child
    this->secondaryChild->ptr = nullptr;             // +0x1C[0]
    this->secondaryChild[0] = 0;                     // +0x1C[1] (maybe length)
    alloc->release(this->secondaryChild, 0);          // virtual call

    // Null the secondary child pointer
    this->secondaryChild = nullptr;                   // +0x1C

    // Release third child
    alloc->release(this->thirdChild, 0);              // +0x18

    // Call destructor on allocator (vtable+0xC)
    alloc->destroy();                                 // virtual call (vtable+0xC)

    // Clear allocator pointer
    this->allocator = nullptr;                        // +0x14

    // Update vtable to a base class (temporary)
    this->field_0C = &PTR_LAB_00e31124;              // +0x0C

    // Clear global singleton pointer
    g_globalManager = nullptr;                        // DAT_01223428

    // Set vtable to base
    this->field_08 = &PTR_LAB_00e30fe0;              // +0x08

    // Deinitialize memory pool or similar
    MemoryPool::shutdown();                           // FUN_0049c640
}