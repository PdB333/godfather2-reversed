// FUNC_NAME: EAObject::initEnginePointers
void __fastcall EAObject::initEnginePointers(EAObject* this)
{
    // Obtain a system-wide handle/ID (e.g., asset or resource identifier)
    uint32_t handle = getEngineObjectHandle();
    this->field_0x10 = handle;  // +0x10: engine handle

    // Obtain a handle from a global pointer (likely a resource or config object)
    uint32_t ptrHandle = getExternalPointerHandle(&PTR_DAT_0110a37c);
    this->field_0x14 = ptrHandle;  // +0x14: external pointer handle

    // Initialize any debugging or logging subsystems
    initDebugOutput();
}