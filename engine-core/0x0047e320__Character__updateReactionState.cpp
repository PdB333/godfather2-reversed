// FUNC_NAME: Character::updateReactionState
// Function address: 0x0047e320
// This function computes a new reaction state for a character based on an absolute value threshold,
// current state, and input parameters. It sets the state at offset +0x98.
// Constants:
//   FLOAT_ABS_MASK = 0x7FFFFFFF (to compute absolute float value via integer AND)
//   REACTION_THRESHOLD = global float at DAT_00e44598
//   IMPACT_OFFSET = global float at DAT_00e2b1a4 (subtracted from value for secondary check)

class Character {
public:
    // +0x7c: currentState (int) – e.g., 0 = idle, 0x48 = damaged
    int currentState;

    // +0x90: isDeadOrFlag (char) – bit flag, possibly dead or invulnerable
    char isDeadOrFlag;

    // +0x94: reactionValue (float) – magnitude of impact or input force
    float reactionValue;

    // +0x98: newState (int) – output: 0,1,2,3 (e.g., stun, normal, fall, etc.)
    int newState;

    // This method likely uses __fastcall (this in ECX, reactionType in EDX, isSomething on stack)
    void __fastcall updateReactionState(int reactionType, char isSomething);
};

// Constants from globals
static const uint FLOAT_ABS_MASK = 0x7FFFFFFF; // Masks out sign bit
extern const float REACTION_THRESHOLD; // DAT_00e44598
extern const float IMPACT_OFFSET;      // DAT_00e2b1a4

void __fastcall Character::updateReactionState(int reactionType, char isSomething)
{
    // Convert float to integer bits, AND with mask to get absolute value, then back to float
    uint absBits = *(uint*)&reactionValue & FLOAT_ABS_MASK;
    float absValue = *(float*)&absBits;

    if (absValue <= REACTION_THRESHOLD)
    {
        // Small reaction value – near idle zone
        if (isDeadOrFlag != 0 || reactionType == 2)
        {
            newState = 2; // e.g., "knocked back" or "block"
            return;
        }
        // If in idle or damaged state and not reacting to type 1, go to idle
        if ((currentState == 0 || currentState == 0x48) && reactionType != 1)
        {
            newState = 0; // idle
            return;
        }
    }
    else
    {
        // Large reaction (e.g., strong hit)
        if (currentState == 0 || currentState == 0x48)
        {
            // Set state to 3 minus deadFlag (deadFlag ? 2 : 3)
            newState = 3 - (uint)(isDeadOrFlag != 0);
            return;
        }
        // If isSomething is false OR the absolute difference from IMPACT_OFFSET exceeds threshold
        if (isSomething == 0 || 
            (*(float*)&(*(uint*)&reactionValue - *(uint*)&IMPACT_OFFSET & FLOAT_ABS_MASK) >= REACTION_THRESHOLD))
        {
            newState = 3; // e.g., "falling" or "ragdoll"
            return;
        }
    }
    // Default to state 1 (e.g., "stumble")
    newState = 1;
}