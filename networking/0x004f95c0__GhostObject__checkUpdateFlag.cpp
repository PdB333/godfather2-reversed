// FUNC_NAME: GhostObject::checkUpdateFlag
// Address: 0x004f95c0
// Role: Checks if a specific update flag is set on this ghost object.
//       Returns the flag value if set, otherwise 0.
//       Uses virtual function at vtable offset 0x10 to perform the check.
//       The virtual function likely takes a flag ID and an optional output pointer.

uint GhostObject::checkUpdateFlag(uint flag) {
    uint outData = 0;  // +0x00 local data, unused in return but passed to vfunc
    // Virtual call at vtable+0x10: (bool (__thiscall*)(GhostObject*, uint, uint*))
    bool success = (*(bool (__thiscall**)(GhostObject*, uint, uint*))(*(uint*)this + 0x10))(this, flag, &outData);
    return success ? flag : 0;
}