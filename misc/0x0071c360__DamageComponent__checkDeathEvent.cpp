// FUNC_NAME: DamageComponent::checkDeathEvent
// Function address: 0x0071c360
// Role: Checks if a specific event (identified by hash 0x55859efa) is active on the parent object,
//       and if so (and a flag is set), clears the death flag at offset 0x28.

// Offsets:
//   this + 0x08: m_pOwnerEntity (Entity*) – pointer to an entity
//   this + 0x28: m_deathFlag (int) – flag cleared when death event confirmed
//   Entity + 0x10: virtual function (likely isEventActive(uint32 eventHash))
//   Entity offset 0x48: sub-object embedded? 0x48 subtracted to get base class pointer.

// Note: 0x48 is used as a sentinel value meaning "no valid entity".

class DamageComponent {
public:
    void checkDeathEvent(byte paramFlag) {
        Entity* pOwner = *(Entity**)(this + 8);
        if (pOwner != nullptr && pOwner != (Entity*)0x48) {
            // Get base class pointer by subtracting offset 0x48 (embedded object)
            int* pBase = (int*)((uintptr_t)pOwner - 0x48);
            // Call virtual function at vtable+0x10 (index 4) with event hash
            bool result = ((bool (__thiscall*)(void*, uint32))(*((int**)pBase) + 4))(pBase, 0x55859efa);
            if (result && (paramFlag & 1)) {
                *(int*)(this + 0x28) = 0; // Clear death flag
            }
        }
    }
};