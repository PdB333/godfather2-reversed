// FUNC_NAME: GameManager::constructor
//
// Address: 0x009244e0
// Role: Constructor for core game manager singleton/object
// Sets up vtable, initializes internal pointers, and optionally calls additional setup
// if the "allocated" flag (param_2 bit 0) is set.

undefined4* __thiscall GameManager::constructor(GameManager* this, byte constructionFlags)
{
    // Set vtable pointer (class-specific)
    this->vtable = &VTable_GameManager;                          // +0x00

    // Initialize pointer at offset 0x10 (likely base class or sub-object vtable)
    this->field_0x10 = &SomeVTable_1;                            // +0x10

    // Initialize pointer at offset 0x4C (last assignment overwrites first – 
    // possibly a bug in analysis or intended default/fallback)
    this->field_0x4C = &SomeVTable_2;                            // +0x4C
    this->field_0x4C = &SomeVTable_3;                            // +0x4C (overwrites)

    // Reset global initialization flag
    g_gameManagerInitialized = false;                            // DAT_01129c48

    // Call global initializer (e.g., register class, load resources, etc.)
    GameManager::globalInit();

    // If constructionFlags has bit 0 set, do additional per‑instance setup
    if ((constructionFlags & 1) != 0) {
        GameManager::postConstructInit(this);                    // FUN_005c4480
    }

    return this;
}