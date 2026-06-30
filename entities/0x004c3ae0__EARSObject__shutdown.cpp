// FUNC_NAME: EARSObject::shutdown
void __fastcall EARSObject::shutdown() {
    // +0x1c: some control/count field
    m_controlCount = 0;

    // Global or static cleanup – argument 0 indicates a specific resource index or none
    staticCleanup(0);

    // +0x40: state/flags field
    m_stateFlags = 0;

    // Release the resource pointed to by +0x3c (e.g., a model or texture handle)
    resourceRelease(*(void**)(this + 0x3c));

    // +0x3c: resource pointer, now cleared
    *(void**)(this + 0x3c) = nullptr;

    // +0x44: another counter or pointer
    m_otherField = 0;
}