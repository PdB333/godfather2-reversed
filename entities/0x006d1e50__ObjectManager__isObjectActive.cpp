// FUNC_NAME: ObjectManager::isObjectActive
// Function at 0x006d1e50: Checks if an object is active (flag at +0x10 has 0x8000) and not in a disabled state (flag at +0x12 does not have 0x8000)
// Called from FUN_006d24d0 (likely a gameplay update)

bool __cdecl ObjectManager::isObjectActive(int objectHandle) {
    // Resolve handle to object pointer via some manager lookup (e.g., SimObjectTable::getObject)
    void* objPtr = (void*)FUN_00410540(objectHandle); // likely SimManager::resolveHandle or similar
    if (objPtr != nullptr) {
        // Flags at +0x10 and +0x12 are ushort fields (e.g., objectStateFlags and objectSubstateFlags)
        ushort stateFlags = *(ushort*)((uint)objPtr + 0x10); // +0x10: main state flags
        ushort substateFlags = *(ushort*)((uint)objPtr + 0x12); // +0x12: secondary state flags (maybe disable flag)
        // Bit 0x8000 might be "active" or "enabled"
        if ((stateFlags & 0x8000) != 0 && (substateFlags & 0x8000) == 0) {
            return true;
        }
    }
    return false;
}