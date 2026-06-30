// FUNC_NAME: Entity::~Entity

void __fastcall Entity::~Entity(Entity *this)
{
    // Vtable assignments (polymorphic destruction)
    this->vtable = &g_EntityVtable;      // +0x00
    this->subVtable1 = &g_BaseVtable;    // +0x3C (0xf)
    this->subVtable2 = &g_BaseVtable2;   // +0x48 (0x12)
    this->subVtable3 = &g_BaseVtable3;   // +0x50 (0x14)

    // Release global static objects (managers, singletons)
    g_EntityManager.~Manager();          // DAT_0120e93c
    g_ComponentRegistry.~Registry();     // DAT_012069f4

    // Clean up embedded sub-objects (first 4: positions 0x54,0x5C,0x64,0x6C)
    this->subObject0.~SubObject();       // +0x15
    this->subObject0.~SubObject();       // redundant? maybe for clarity
    this->subObject1.~SubObject();       // +0x17
    this->subObject1.~SubObject();       // redundant?
    this->subObject2.~SubObject();       // +0x19
    this->subObject3.~SubObject();       // +0x1b

    // Release global audio/havok streams
    g_AudioStream.~Stream();             // DAT_0112a628
    g_HavokStream.~Stream();             // DAT_0112a5c4

    // Release component pointer at +0xB8
    if (this->pComponent1 != nullptr) {  // +0x2e
        releaseComponent(this->pComponent1); // FUN_009c8eb0
    }

    // Release pointer at +0x108
    if (this->pLargeData != nullptr) {   // +0x42
        safeDelete(&this->pLargeData);   // FUN_004daf90
    }

    // Release three pairs of pointers at +0xE4, +0xDC, +0xD4
    // Loop decrementing by 2 each time, starting at +0x39 (0xE4)
    int *ppPtr = &this->pArray[0x39 / 4]; // +0x39 = 0xE4
    for (int i = 0; i < 3; i++) {
        // ppPtr[-2] is the pointer we check, ppPtr is the address of the pointer itself
        if (*(ppPtr - 2) != 0) {
            safeDelete(ppPtr);           // FUN_004daf90
        }
        ppPtr -= 2;                     // move to previous pair
    }

    // Release pointer at +0xBC
    if (this->pSecondary != nullptr) {   // +0x2f
        safeDelete(&this->pSecondary);   // FUN_004daf90
    }

    // Final static cleanup
    shutdownGlobalSystems();             // FUN_0046c640
}