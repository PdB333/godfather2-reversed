// FUNC_NAME: GameSystem::Initialize
void __fastcall GameSystem::Initialize(GameSystem* this)
{
    // Set vtables for multiple inheritance interfaces
    this->vfptr = (GameSystemVtbl*)&PTR_FUN_00d5fd1c;    // +0x00 primary vtable
    this->interface1 = (IInterface1*)&PTR_LAB_00d5fd0c;   // +0x3C offset
    this->interface2 = (IInterface2*)&PTR_LAB_00d5fd08;   // +0x48 offset

    // Global engine subsystem initialization (e.g., audio, memory)
    GlobalEngine::Initialize(&g_EngineData);               // FUN_004086d0

    // Initialize embedded subobject at offset +0x70
    SubObject::Construct(&this->subObject);               // FUN_00408310

    // If a callback-object pointer exists at +0x60, invoke its initializer function
    if (this->callbackObject != nullptr)                  // param_1[0x18] at +0x60
    {
        ((void (*)(void*))this->callbackFunc)(this->callbackObject); // param_1[0x1b] at +0x6C
    }

    // Post-construction setup (e.g., register with manager lists)
    PostConstructInit();                                   // FUN_0046c640
}