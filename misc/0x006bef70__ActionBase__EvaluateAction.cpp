// FUNC_NAME: ActionBase::EvaluateAction
// Address: 0x006bef70
// Role: Evaluates and executes one of two actions based on target/source/context IDs and flags.
// Observed offsets:
//   +0x10: m_pTarget (pointer to object with ID at +0x40)
//   +0x14: m_pSource (pointer to object with ID at +0x54)
//   +0x18: m_pContext (pointer to object with ID at +0x54)
//   +0x20: m_pExtra (optional pointer)
//   +0x34: m_flags (uint: bit0 = allowed, bit2 = skip pre-check, bit3 = blocked)
// Returns: 0=aborted, 1=action1 taken, 2=action2 taken, 3=error

static const int INVALID_ID = 0x637b907;

int __fastcall ActionBase::EvaluateAction(ActionBase* this)
{
    int targetId = *(int*)(*(int*)((char*)this + 0x10) + 0x40); // m_pTarget->idField40
    int sourceId = *(int*)(*(int*)((char*)this + 0x14) + 0x54); // m_pSource->idField54
    int contextId = *(int*)(*(int*)((char*)this + 0x18) + 0x54); // m_pContext->idField54

    // If neither source nor context matches the target, it's an error state
    if (sourceId != targetId && contextId != targetId)
    {
        Cleanup(); // 0x008bd820 – finalization routine
        return 3;
    }

    uint flags = *(uint*)((char*)this + 0x34);

    // Allowed only if bit3 not set, and (bit0 is set with a valid source ID OR an extra pointer exists)
    if (!(flags >> 3 & 1) &&
        (((flags & 1) != 0 && sourceId == INVALID_ID) || *(int*)((char*)this + 0x20) != 0))
    {
        // If bit2 is not set, perform a pre‑execution viability check
        if (!(flags >> 2 & 1))
        {
            if (!CanProceed()) // 0x006beb50 – check if action is possible
                return 0;
        }

        // If the target ID differs from source, update the source's state
        if (targetId != sourceId)
            SetState(sourceId, 0, 0, 1); // 0x006b68c0

        ExecutePrimaryAction(
            *(void**)((char*)this + 0x14),   // m_pSource
            *(void**)((char*)this + 0x18),   // m_pContext
            *(void**)((char*)this + 0x10));  // m_pTarget
        // 0x006be8a0 – primary action execution

        Cleanup();
        return 1;
    }
    else
    {
        ExecuteFallbackAction(
            *(void**)((char*)this + 0x14),   // m_pSource
            *(void**)((char*)this + 0x18),   // m_pContext
            *(void**)((char*)this + 0x10));  // m_pTarget
        // 0x006be840 – fallback action execution

        Cleanup();
        return 2;
    }
}