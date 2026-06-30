// FUNC_NAME: PlayerStateMachine::updateState
void __fastcall PlayerStateMachine::updateState(int this)
{
    int* parentBase;
    int* pSomething = *(int**)(this + 0xC4); // +0xC4: pointer to something
    if (pSomething != nullptr) {
        // Adjust pointer: parent object is located 0x48 bytes before pSomething
        parentBase = (int*)((int)pSomething - 0x48);
    } else {
        parentBase = nullptr;
    }
    *(int**)(this + 0xB4) = parentBase; // +0xB4: m_pParent

    if (parentBase != nullptr) {
        // Virtual call through parent's vtable at offset 0x58
        int result = (*(int(__thiscall**)(int))(*(int*)parentBase + 0x58))(parentBase);
        *(int*)(this + 0x84) = result; // +0x84: m_someValue

        // Copy transform from parent (offset 0x34 in parent) to this (offset 0x30)
        // Assuming a 48-byte transform (4x3 matrix or similar)
        copyTransform((void*)(this + 0x30), (void*)(parentBase + 0x34));
        return;
    }

    // No parent – deactivate state
    deactivateState(0); // FUN_0051d230(0)

    // Check a flag on an external object pointed to by this+0x10
    int* pOwner = *(int**)(this + 0x10); // +0x10: m_pOwner
    if ((*(uint*)(pOwner + 0x14) & 0x1000) != 0) {
        // Owner has flag 0x1000
        if ((*(uint*)(this + 0xC) & 0x20000) == 0) {
            // Set our own flag 0x20000
            *(uint*)(this + 0xC) |= 0x20000;
            // Trigger transition or effect
            triggerTransition(); // FUN_0051b120()
        }
        // Clear flag 0x40000
        *(uint*)(this + 0xC) &= ~0x40000;
        return;
    }

    // Otherwise fall back to default behavior
    defaultUpdate(this); // FUN_0051b2b0(this)
}