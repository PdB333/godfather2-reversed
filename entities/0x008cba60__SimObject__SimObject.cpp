// FUNC_NAME: SimObject::SimObject

void __fastcall SimObject::SimObject(void* thisPtr)
{
    // Set vtable pointer (using known vtable address 0x00d7c2d8)
    *(uint32_t**)thisPtr = &SimObject_vtable;

    // Call base class constructor with global initialization data
    SimObjectBase::SimObjectBase(&g_SimObjectInitData);

    // Execute post-initialization routine
    SimObject::postInitialize();
}