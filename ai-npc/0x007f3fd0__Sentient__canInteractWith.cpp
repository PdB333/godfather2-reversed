// FUNC_NAME: Sentient::canInteractWith
// Address: 0x007f3fd0
// Role: Checks if this Sentient can interact with another Sentient. 
// Returns true if interaction is allowed based on global flags, character state (offset +0x1f1c), and relationship permissions.

// Global flags/data
extern bool g_interactionsEnabled;        // _DAT_0112c810
extern char g_relationshipPermissions[];  // _DAT_0112bb68 – array of per-relationship permission bytes

// Offset to a character state byte (e.g., 'P' = Player-controlled)
static const int kCharacterStateOffset = 0x1f1c;
static const char kPlayerControlState = 'P';   // ASCII 0x50

/** 
 * Returns an index into g_relationshipPermissions for the current relationship/context.
 * Likely returns the player index or some relationship key.
 */
int GetRelationshipIndex(); // FUN_007f3f60

bool Sentient::canInteractWith(Sentient* other)
{
    // If interactions are globally disabled, or either entity is player-controlled,
    // allow interaction unconditionally.
    if (!g_interactionsEnabled)
        return true;
    if (*(char*)(this + kCharacterStateOffset) == kPlayerControlState)
        return true;
    if (*(char*)(other + kCharacterStateOffset) == kPlayerControlState)
        return true;

    // Get the relationship index for the current context (e.g., player index)
    int idx = GetRelationshipIndex();

    // Check if the relationship permission allows interaction.
    // Bits 1-7 (mask 0xFE) must be zero; i.e., value must be 0 or 1.
    return (g_relationshipPermissions[idx] & 0xfe) == 0;
}