// FUNC_NAME: CooldownManager::triggerCooldown
void CooldownManager::triggerCooldown(const char* eventName) {
    if (eventName == nullptr) return;

    // Compute string length without null terminator
    const char* p = eventName;
    while (*p != '\0') ++p;
    int lengthWithoutNull = p - (eventName + 1);  // strlen - 1

    // Hash the event name
    uint32_t eventHash = computeHash(0x62dbe036, eventName, lengthWithoutNull);

    // Look up event data from the hash
    EventData* eventData = findEventData(eventHash);
    if (eventData == nullptr) return;

    // Get or create a cooldown entry for this event
    CooldownEntry* entry = getCooldownEntry(eventHash);
    if (entry == nullptr) return;

    uint32_t currentTime = g_GlobalTimer;  // DAT_01205224

    // Update entry fields
    entry->eventHash = eventHash;
    entry->maxCount = *(uint32_t*)(eventData + 0x10);     // +0x10: maximum trigger count before cooldown
    entry->someParam = *(uint32_t*)(eventData + 0x14);    // +0x14: unknown parameter
    entry->count += 1;                                    // +0x0C: current trigger count
    entry->lastTriggerTime = currentTime;                 // +0x14: last time triggered

    // Check if cooldown should be applied
    if (entry->count >= entry->maxCount) {
        float cooldownFloat = *(float*)(eventData + 0x0C);  // +0x0C: cooldown duration multiplier
        uint32_t cooldown = (uint32_t)(cooldownFloat * g_CooldownScale);  // DAT_00d60d04
        if (cooldown < 10) {
            cooldown = 30000;  // Default 30 seconds
        }

        entry->count = 0;
        entry->cooldownEndTime = currentTime + cooldown;  // +0x10: time when cooldown expires
    }
}