// FUNC_NAME: SomeComponent::checkAndUpdate
// Address: 0x006ba120
// Role: Checks a boolean flag at offset +0x98 and triggers an action if set.
// Callees: FUN_00402080 (likely isFlagSet) and FUN_006b9f10 (likely handleAction)
void __fastcall SomeComponent::checkAndUpdate(int thisPtr)
{
    // Check if flag at offset 0x98 is non-zero (e.g., active state, pending event)
    char flag = FUN_00402080(thisPtr + 0x98);
    if (flag != 0) {
        // Perform associated action
        FUN_006b9f10();
    }
    // No further processing required
}