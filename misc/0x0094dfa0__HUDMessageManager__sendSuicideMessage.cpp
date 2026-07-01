// FUNC_NAME: HUDMessageManager::sendSuicideMessage
// Function address: 0x0094dfa0
// Role: Constructs and sends a HUD suicide/kill message via InformEvent system.
// Uses a formatted string with color and player name, then posts the event.
// Note: The code calls an uninitialized function pointer (local_4) - likely a
// decompilation artifact or a custom string cleanup mechanism.

void __thiscall HUDMessageManager::sendSuicideMessage(void* this, int isSuicide)
{
    const char* playerName;
    const char* colorString;
    const char* messageBuffer[3];  // Buffer for formatted message (might be a temp string)
    void (*cleanupFunc)(const char*);  // Uninitialized destructor pointer

    // Get player name from class member (offset 0)
    playerName = *(const char**)this;
    if (playerName == (const char*)0x0)
    {
        playerName = (const char*)0x0120546e;  // Default unnamed string
    }

    // Choose color based on suicide flag
    if (isSuicide != 0)
    {
        colorString = (const char*)0x00e35114;  // Color for suicide
    }
    else
    {
        colorString = (const char*)0x00e35154;  // Color for kill
    }

    // Format the HUD message string
    // Format: [c=%s]{k:%s}{$mp_hud_suicide}[c=RESET]
    // c = color, k = player name, $mp_hud_suicide = localized suicide text
    FUN_004d4a60(
        messageBuffer,
        1,
        "[c=%s]{k:%s}{$mp_hud_suicide}[c=RESET]",
        colorString,
        playerName
    );

    // Fallback to default if formatted string is null
    const char* formattedMsg = messageBuffer[0];
    if (formattedMsg == (const char*)0x0)
    {
        formattedMsg = (const char*)0x0120546e;
    }

    // Send the event to the UI system
    FUN_005a04a0(
        "InformEvent",      // Event name
        0,                  // Flags
        &DAT_00d8b7d4,      // Event data (likely a struct or string)
        1,                  // Count
        formattedMsg        // Message string
    );

    // Cleanup the formatted message if it was allocated
    if (messageBuffer[0] != (const char*)0x0)
    {
        (*cleanupFunc)(messageBuffer[0]);  // Potential crash: cleanupFunc uninitialized
    }

    return;
}