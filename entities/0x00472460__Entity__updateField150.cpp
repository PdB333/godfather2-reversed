// FUNC_NAME: Entity::updateField150
void __thiscall Entity::updateField150(void) {
    float currentTime;

    if (this->field_150 != g_defaultField150) {
        if (!g_globalCondition) {
            this->field_150 = g_defaultField150;
            this->field_15e_flags |= 0x100; // set bit 8
            return;
        }
        if (g_someObject->field_54 != 0) {
            currentTime = getCurrentTime();
            if (currentTime >= g_timeThreshold) {
                triggerFunction(1.0f); // FUN_004706f0 with 1.0
            }
        }
    }
}