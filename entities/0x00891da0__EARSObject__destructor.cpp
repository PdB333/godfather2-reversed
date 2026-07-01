// FUNC_NAME: EARSObject::destructor
void __thiscall EARSObject::destructor(EARSObject *this)
{
    // Set vtable to deleting destructor pointer
    this->vtable = &PTR_FUN_00d777c8;          // +0x00
    this->unknownPtr = &PTR_LAB_00d777b8;      // +0x04

    // Debug or cleanup call with signature constant
    DebugLog(0x57600d39);

    // Free dynamically allocated buffer if present
    if (this->allocatedBuffer != 0)            // +0x08
    {
        MemoryFree(this->allocatedBuffer);     // FUN_009c8f10
    }

    // Switch vtable to final destructor stage
    this->unknownPtr = &PTR_LAB_00e30fe0;      // +0x04
    this->vtable = &PTR_LAB_00d777b4;          // +0x00

    // Clear global singleton pointer or state flag
    g_someGlobal = 0;                          // DAT_011299c0
}