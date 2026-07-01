// FUNC_NAME: MissionManager::validateMissionTrigger
// Function at 0x007bad30: Checks if a given trigger condition matches the current active mission ID and subtype, and if so, stores the ID and activates the flag.
uint __thiscall MissionManager::validateMissionTrigger(MissionManager* this, int triggerId, char triggerSubtype)
{
    // Get the global game state or mission manager singleton
    GameState* gameState = reinterpret_cast<GameState*>(FUN_00481640());
    if (gameState == nullptr) {
        return 0;
    }

    // Access the large structure at this+0x58 (likely a player or active mission object)
    MissionObject* missionObj = *reinterpret_cast<MissionObject**>(reinterpret_cast<char*>(this) + 0x58);
    // Offset 0x2198: flag indicating whether this trigger has been activated
    char* activationFlag = reinterpret_cast<char*>(missionObj) + 0x2198;
    if (*activationFlag != '\0') {
        // Already activated, return non-zero (so caller knows it's active)
        // The return value is the address of the flag shifted to clear low byte (odd but harmless)
        return reinterpret_cast<uint>(activationFlag) & 0xFFFFFF00;
    }

    // Read a 64-bit value at offset 0x21A0: low 32 bits = some ID, high 32 bits = subtype or extra data
    uint64_t storedValue = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(missionObj) + 0x21A0);
    uint storedId = static_cast<uint>(storedValue & 0xFFFFFFFF);
    int storedSubtype = static_cast<int>(storedValue >> 32);

    // Read a byte at offset 0x21A8 (possibly an additional flag or data)
    char storedByte = *reinterpret_cast<char*>(reinterpret_cast<char*>(missionObj) + 0x21A8);

    // Match: triggerId must equal storedId, and triggerSubtype must be -1 (wildcard) or equal storedSubtype
    if (triggerId == storedId && (triggerSubtype == -1 || triggerSubtype == storedSubtype)) {
        // Store the matched ID and extra data into this object for later use
        *reinterpret_cast<uint*>(reinterpret_cast<char*>(this) + 0x78) = storedId;       // +0x78: matched ID
        *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x74) = storedSubtype;  // +0x74: matched subtype (low byte)
        *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x7C) = storedByte;     // +0x7C: extra byte

        // Set activation flag to 1
        *activationFlag = 1;

        // Return 1 to indicate success
        return 1;
    }

    // Did not match, return non-zero (using shifted flag address) if gameState was valid
    return reinterpret_cast<uint>(activationFlag) & 0xFFFFFF00;
}