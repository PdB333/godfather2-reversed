// FUNC_NAME: CActiveComponentManager::updateActiveComponents
// Function at 0x006fd730: Iterates over 3 managed slots, queries for a component interface (hash 0x55859efa) on each active entity, and calls its update method if the component is not disabled.
// Each slot structure (0x58 bytes) contains a state integer and a pointer to a member within an entity (offset -0x48 from entity base).
void __thiscall CActiveComponentManager::updateActiveComponents(void* thisPtr)
{
    // Slots array starts at offset 0x78 from this.
    // Each slot is 0x58 bytes, first field is state (int), then at offset 0x18 is a pointer to an entity member.
    uint slotsBase = (uint)thisPtr + 0x78;
    // Pointer to current slot's entity member pointer field (+0x18 relative to slot start)
    uint* pCurSlotMemberPtr = (uint*)((uint)thisPtr + 0x90); // first slot member ptr at +0x90
    int slotCount = 3;

    do {
        // Check if slot is active (state != 0 && state != 6)
        int slotState = *(int*)((uint)pCurSlotMemberPtr - 0x18); // state at offset -24 (0x78)
        if ((slotState != 0) && (slotState != 6)) {
            uint pMember = *pCurSlotMemberPtr;
            uint* pEntity = 0;
            // Compute entity base from member pointer (subtract 0x48). If member pointer is null or entity base is null, skip.
            if ((pMember != 0) && ((pEntity = (uint*)(pMember - 0x48), pEntity) != 0)) {
                // Query for component interface using hash 0x55859efa
                uint componentPtr = 0;
                // vtable+0x10: bool queryInterface(uint hash, uint* outPtr);
                int (__thiscall* queryInterface)(void*, uint, uint*) = *(int (__thiscall**)(void*, uint, uint*))(*(int*)pEntity + 0x10);
                bool found = (bool)(*queryInterface)(pEntity, 0x55859efa, &componentPtr);
                if (found) {
                    pEntity = (uint*)componentPtr; // use the component pointer
                } else {
                    pEntity = 0;
                }
            } else {
                pEntity = 0;
            }

            // If component is valid and its disabled flag (bit 0 of byte at +0x8e6) is clear, call update method
            if ((pEntity != 0) && ((*(uint8*)((uint)pEntity + 0x8e6) & 1) == 0)) {
                // vtable+0x27c: void updateComponent();
                void (__thiscall* updateComponent)(void*) = *(void (__thiscall**)(void*))(*(int*)pEntity + 0x27c);
                (*updateComponent)(pEntity);
            }
        }
        // Move to next slot (0x16 ints = 0x58 bytes)
        pCurSlotMemberPtr += 0x16;
        --slotCount;
    } while (slotCount != 0);
}