// FUNC_NAME: NPC::shouldDoRandomAction
bool __fastcall NPC::shouldDoRandomAction(NPC* this)
{
    // Check if the NPC's attribute at offset +0x74 is greater than 1
    // If so, perform a random probability check against a global threshold
    if (*(uint32_t*)((uint8_t*)this + 0x74) > 1) {
        // Normalize rand() to [0.0, 1.0) using precomputed reciprocal (DAT_00e44590)
        // and compare against the global probability constant (DAT_00d5f520)
        float randomFraction = (float)rand() * DAT_00e44590;  // __fastcall translates ecx/edx, but here only one param
        if (randomFraction < DAT_00d5f520) {
            return true;
        }
    }
    return false;
}