// FUNC_NAME: NetObject::getGhostID
int __thiscall NetObject::getGhostID(uint32 *outValue) {
    // outValue is likely passed on stack (since __thiscall puts this in ECX, rest on stack).
    // The decompiler shows unaff_ESI, but based on the calling convention we treat it as a pointer parameter.
    uint32 local_value = 0;
    
    // Check if this is valid and has the ghost flag (bit 27 at offset 0x14 / +5 int slots)
    if (this != NULL && (this->flags & 0x8000000U) != 0) {
        const uint32 propertyID = 0xb1079603; // Likely a CRC/hash for GhostID
        
        // Call virtual method at vtable+0x10 (vtable[4])
        // It takes the propertyID and a pointer to receive the value, returns bool
        bool success = (*(bool (__thiscall **)(NetObject*, uint32, uint32*))(*(uint32*)this + 0x10))(this, propertyID, &local_value);
        
        if (success) {
            *outValue = propertyID; // Note: This seems to store the property ID itself, not the retrieved value.
            // Actually it stores the constant 0xb1079603, but logically it should store the value from the call.
            // The decompiler shows *unaff_ESI = uVar2 where uVar2 is the constant.
            // This might be intentional or a bug. We preserve the original behavior.
            return 1;
        }
    }
    
    *outValue = 0;
    return 0;
}