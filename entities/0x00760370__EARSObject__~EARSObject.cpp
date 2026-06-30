// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00760370
// Destructor for base EARSObject. Sets vtable to intermediate destructor vtable,
// releases child object at offset +0x04, then sets vtable to purecall to prevent further virtual calls.

void __fastcall EARSObject::~EARSObject(void* this)
{
    // Set vtable to the class's destruction-stage vtable (prevents virtual calls during cleanup)
    *(void***)this = (void**)&PTR_FUN_00d65404;

    // Release sub-object if present (likely a heap-allocated component or data)
    if (*(void**)((char*)this + 4) != 0) {
        FUN_004daf90((void**)((char*)this + 4)); // +0x04: m_pComponent or m_pData
    }

    // Finalize by setting vtable to purecall trap to catch accidental virtual calls after destruction
    *(void***)this = (void**)&PTR___purecall_00e407a4;
}