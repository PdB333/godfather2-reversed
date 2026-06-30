// FUNC_NAME: SomeClass::clearFlag4IfCondition
// Function address: 0x00749070
// Role: Checks a flag bit and a pointer condition, then clears the flag if two subcalls succeed.
// This appears to be a state update that disables a feature (likely related to sound/physics based on global DAT_01131040).
// Offsets: this+0x50 -> flags (uint), this+0x54 -> pointer to something (non-null check)

void __fastcall SomeClass::clearFlag4IfCondition(int this)
{
    // Check if bit 4 of flags is set and pointer at +0x54 is not null
    if (((*(uint *)(this + 0x50) >> 4 & 1) != 0) && (*(int *)(this + 0x54) != 0))
    {
        // Call with the global DAT_01131040 (likely a singleton manager)
        int iVar1 = FUN_0043b870(*(int*)0x01131040);
        if (iVar1 != 0)
        {
            // Additional side effect (e.g., stop a sound or disable physics)
            FUN_009b1250();
            // Clear bit 4 to mark the feature as disabled
            *(uint *)(this + 0x50) = *(uint *)(this + 0x50) & 0xffffffef;
        }
    }
}