// FUNC_NAME: Object::checkAndDestroy
// Function address: 0x00725150
// Called to conditionally destroy an object after checking an owner's permission and internal flags.
// param_1 (this): object to potentially destroy
// param_2 (pOwner): owner/manager object with a virtual method at vtable+0x10 to approve destruction
// Offset +0xe8: uint32 flags; bit0 = already destroyed, bit1 = pendingDelete (or similar)

void __thiscall Object::checkAndDestroy(void* pOwner)
{
    if (pOwner == nullptr) {
        return;
    }

    // Call virtual method at vtable offset 0x10 on pOwner, passing 'this' as argument.
    // Typically returns 0 if destruction is allowed, non-zero if not.
    bool ownerAllowsDestruction = ((uint8 (__thiscall *)(void*)) 
        (*(void**)*(int**)pOwner)[0x10 / 4])(this) == 0;

    if (ownerAllowsDestruction &&
        ((m_flags >> 1) & 1) == 0 &&    // bit1 == 0 (not pending delete)
        (m_flags & 1) == 0)             // bit0 == 0 (not already destroyed)
    {
        // Perform actual destruction via static function that takes pOwner twice
        // (possibly sets reference or double-checks pointer)
        FUN_00724e60(pOwner, pOwner);
    }
}