// FUNC_NAME: ResolveAndGetObjectFlag
uint __fastcall ResolveAndGetObjectFlag(void* unused, uint handle)
{
    // unused param is ECX (possibly this, but not used)
    // Local variables for callee output, but ignored
    undefined local5;
    undefined local4[4];

    // FUN_005f0560 likely resolves a handle to an object pointer.
    // Expected signature: uint __fastcall ResolveObjectHandle(uint handle, undefined* out1, undefined* out2)
    // Returns object pointer or error (0 or 0xFFFFFFE0)
    uint objPtr = FUN_005f0560(handle, &local5, local4);
    if ((objPtr != 0) && (objPtr != 0xFFFFFFE0))
    {
        // Object is valid; read flags at offset +0x28 (e.g., m_stateFlags)
        // Right shift 6 (bit 6 moved to LSB) then mask to isolate bit 0 and bits 8-31
        return *(uint*)(objPtr + 0x28) >> 6 & 0xFFFFFF01;
    }
    // Return the raw error code with lower byte cleared
    return objPtr & 0xFFFFFF00;
}