// FUNC_NAME: GameManager::GameManager
void __fastcall GameManager::GameManager(GameManager* this)
{
    // Set up base class vtable pointers
    this->vtable = &PTR_FUN_00d5db44;          // +0x00: base vtable
    this->field_4 = &PTR_LAB_00d5db34;         // +0x04: second vtable (possibly for multiple inheritance)

    // Initialize member at offset 0xFC
    someInitFunc(this + 0xFC);                 // +0xFC: member object (e.g., sub-system)

    // Initialize global static objects
    someInitFunc(&DAT_0112a578);               // global object 1
    someInitFunc(&DAT_0112b36c);               // global object 2
    someInitFunc(&DAT_0112a564);               // global object 3
    someInitFunc(&DAT_0112a56c);               // global object 4

    // Deinitialize the same objects (likely to reset them)
    someDeinitFunc(this + 0xFC);               // +0xFC: member object
    someDeinitFunc(&DAT_0112a578);             // global object 1
    someDeinitFunc(&DAT_0112b36c);             // global object 2
    someDeinitFunc(&DAT_0112a564);             // global object 3
    someDeinitFunc(&DAT_0112a56c);             // global object 4

    // Final initialization step
    finalizeInit();

    // Switch vtable to derived class
    this->vtable = &PTR_LAB_00d5dac8;          // +0x00: derived vtable

    // Clear a global initialization flag
    DAT_0112a554 = 0;                          // flag indicating the manager is ready
}