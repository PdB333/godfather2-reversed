// FUNC_NAME: sendTeamKillNotification
// Address: 0x0094df10
// Sends a HUD notification for a team kill event in multiplayer.

void sendTeamKillNotification(const char** killerNamePtr, const char** victimNamePtr, int isTeamKill)
{
    const char* victimName;
    const char* killerName;
    const char* teamKillColor;
    
    // Default to empty string if null pointer
    victimName = (*victimNamePtr != nullptr) ? *victimNamePtr : "\0";
    killerName = (*killerNamePtr != nullptr) ? *killerNamePtr : "\0";
    
    // Select color based on team kill flag
    // +0x0: white/normal color string (DAT_00e35154)
    // +0x0: red/team kill color string (DAT_00e35114)
    if (isTeamKill != 0) {
        teamKillColor = "\x00e35114";  // RED_COLOR_STRING
    } else {
        teamKillColor = "\x00e35154";  // WHITE_COLOR_STRING
    }
    
    // Format: [c=color]{k:killer}{m:victim}{$mp_hud_team_kills}[c=RESET]
    char* formattedMessage = formatGameString(1, "[c=%s]{k:%s}{m:%s}{$mp_hud_team_kills}[c=RESET]",
                                              teamKillColor, killerName, victimName);
    
    // Use formatted string or fallback to empty
    const char* message = (formattedMessage != nullptr) ? formattedMessage : "\0";
    
    // Post the event
    // DAT_00d8b7d4 is the event ID for team kill HUD notification
    postEvent("InformEvent", 0, "\x00d8b7d4", 1, message);
    
    // Free allocated string if not null
    if (formattedMessage != nullptr) {
        deallocateString(formattedMessage);
    }
}