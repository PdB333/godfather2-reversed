// FUNC_NAME: TargetManager::setTargetId
// Function address: 0x0071df90
// Role: Set a target identifier and perform one-time initialization if not already done.

void __thiscall TargetManager::setTargetId(int this, int targetId)
{
    // Store target ID at offset +0xC
    *(int *)(this + 0xC) = targetId;

    // Check flag at +0x84, bit 0. If not set, set it and call initialization routine.
    if ((*(unsigned int *)(this + 0x84) & 1) == 0)
    {
        *(unsigned int *)(this + 0x84) |= 1;
        // One-time initialization (likely registers or prepares the target)
        FUN_007ee2e0();
    }
}