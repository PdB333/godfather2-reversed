// FUNC_NAME: CEffectManager::handleVisualEffect
uint __thiscall CEffectManager::handleVisualEffect(int this, int param2, char param3, int param4)
{
    int* pEffectData;
    int currentTick;
    uint result;

    currentTick = g_currentTick; // DAT_01205224
    pEffectData = *(int**)(this + 0x218); // +0x218: pointer to effect data structure

    // Initialize result with the low byte of whatever was in EAX at function entry (likely a return value from caller)
    result = entry_EAX & 0xFFFFFF00;

    if (pEffectData != nullptr) {
        // Check if this effect already processed in current tick and param3 is true
        if ((*(int*)(this + 0x23c) == currentTick) && (param3 != '\0')) {
            // Call a function to start/create a new effect (param4 might be effect ID or data)
            result = EffectSystem::startEffect(param4); // FUN_00571450(param4)
            *(int*)(this + 0x23c) = currentTick;       // +0x23c: last update tick
            return result;
        }

        // Update flag at offset 0x10 in the effect data based on param4 (boolean-like)
        if ((char)param4 == '\0') {
            pEffectData[4] &= ~0x800;   // Clear bit 11 (0x800) – likely "active" or "visible"
        } else {
            pEffectData[4] |= 0x800;    // Set bit 11
        }

        if (param3 != '\0') {
            // Call to stop/remove the effect (param2 might be effect handle)
            result = EffectSystem::stopEffect(param2, 0); // FUN_00578620(param2,0)
            *(int*)(this + 0x23c) = currentTick;
            return result;
        }

        // Default: call virtual function at index 1 in the effect data's vtable
        // The effect data structure is assumed to be a polymorphic object with a vtable pointer as first member
        result = ((int(__thiscall*)(int*, int))(*(void***)pEffectData)[1])(pEffectData, param2);
        *(int*)(this + 0x23c) = currentTick;
    }

    return result;
}