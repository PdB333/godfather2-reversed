// FUNC_NAME: Player::~Player
// Destructor for the Player class. Frees subcomponents, stops timers, releases COM objects, and cleans up global state.
void __thiscall Player::~Player(Player* this) {
    // Set vtable pointers for proper destruction order (multiple inheritance / base class subobjects)
    this->vtable1 = &PTR_FUN_00d8ae70;  // VTable for this class
    this->vtable2 = &PTR_LAB_00d8ae48; // Base class vtable at offset 0x10
    this->vtable3 = &PTR_LAB_00d8ae44; // Another base vtable at offset 0x4C
    this->vtable4 = &PTR_LAB_00d8ae34; // Yet another at offset 0x50

    // Free sub-components (likely animation, Lua, etc.)
    freeMemory(this->animationData);          // +0xE0
    freeMemory(this->animationData2);         // +0xE4
    freeMemory(this->someResource1);          // +0xF8
    freeMemory(this->someResource2);          // +0xFC
    freeMemory(this->dialogManager);          // +0x130
    freeMemory(this->luaState1);              // +0xB8
    freeMemory(this->luaState2);              // +0xBC
    freeMemory(this->pathfindingData1);       // +0x108
    freeMemory(this->pathfindingData2);       // +0x10C

    // Release global handles (mutexes, critical sections, resource handles)
    releaseHandle(&DAT_01130450);
    releaseHandle(&DAT_011303b0);
    releaseHandle(&DAT_01130240);
    releaseHandle(&DAT_01130348);
    releaseHandle(&DAT_011301d0);
    releaseHandle(&DAT_01130498);
    releaseHandle(&DAT_0112a5a4);
    releaseHandle(&DAT_01130248);

    // Stop any active timer if bit12 of flag at +0x5C is set
    if (((uint)this->flags >> 0xC) & 1) {
        stopTimer(&this->timer, &LAB_0093bd50, 1);
    }

    // Release objects in an array if global singleton is active
    if ((DAT_0112a680 != 0) && (this->arrayCount != 0)) {
        uint i = 0;
        do {
            releaseObject(*(void**)(this->objectArray + i * 8)); // Each element is 8 bytes, pointer at offset 4
            i++;
        } while (i < (uint)this->arrayCount);
    }

    // Free the array itself
    if (this->objectArray != 0) {
        freeMemory(this->objectArray);
    }

    // Release COM-like objects (probably DirectX or engine interfaces)
    if (this->comObject1 != 0) {
        releaseComObject(&this->comObject1);  // +0x11C
    }
    if (this->comObject2 != 0) {
        releaseComObject(&this->comObject2);  // +0x114
    }

    // Call destructors for sub-objects via function pointers
    if (this->subObject1 != 0) {
        void (*destroyer)(void*) = (void (*)(void*))this->destroyFunc1;  // +0xA8
        destroyer(this->subObject1); // +0x9C
    }
    if (this->subObject2 != 0) {
        void (*destroyer)(void*) = (void (*)(void*))this->destroyFunc2;  // +0x94
        destroyer(this->subObject2); // +0x88
    }

    // Run global cleanup
    globalCleanup();

    // Change vtable to final base class after destruction
    this->vtable3 = &PTR_LAB_00d8a9e0;

    // Reset global singleton pointer and shut down subsystem
    DAT_01129c4c = 0;
    shutdownSystem();
}