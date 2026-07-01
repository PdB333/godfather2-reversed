// FUNC_NAME: CharacterController::getCurrentMovementSpeed
// Address: 0x007fd840
// Returns movement speed based on current state and flags.
// Offset +0x1b8c: current movement state (byte, e.g., 0x04 for a specific state)
// Offset +0x8e0: flags (uint, bit 1 tested)
// Offset +0x1c8c: default speed (float)
// Offset +0x1ca4: alternate speed (float)
float __fastcall CharacterController::getCurrentMovementSpeed(void* thisPtr)
{
    // Check if movement state is 0x04 and bit 1 of flags is set
    if ( (*(char*)((int)thisPtr + 0x1b8c) == '\x04') &&
         ((*(uint*)((int)thisPtr + 0x8e0) >> 1 & 1) != 0) )
    {
        // Return alternate speed (e.g., sprint or special)
        return *(float*)((int)thisPtr + 0x1ca4);
    }
    // Return default speed
    return *(float*)((int)thisPtr + 0x1c8c);
}