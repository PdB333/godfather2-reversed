// FUNC_NAME: EAObject::setActive

void EAObject::setActive(bool active) {
    // +0x24: active flag
    *(char *)(this + 0x24) = (char)active;

    // Global flag to skip audio control during certain phases (e.g., loading)
    if (g_isInitializing == '\0') {
        // Suspend/resume any active sounds for this object
        g_soundManager->setSoundActive(this->soundHandle, active);
        g_soundManager->setSoundActive(this->soundHandle, active);
    }

    // Call global callback (e.g., for UI or scripting)
    if (g_activeChangeCallback != (code *)0x0) {
        (*g_activeChangeCallback)(this->soundHandle, active);
    }

    if (active == '\0') {
        // Deactivation: remove from global active object list
        for (uint i = 0; i < g_activeObjectCount; i++) {
            if (g_activeObjectList[i] == this) {
                // Replace with last element (shrink list)
                if ((int)i < (int)(g_activeObjectCount - 1)) {
                    g_activeObjectList[i] = g_activeObjectList[g_activeObjectCount - 1];
                }
                g_activeObjectCount--;
                break;
            }
        }
    } else {
        // Activation: add to list if capacity allows
        if (g_activeObjectCount < 128) {
            g_activeObjectList[g_activeObjectCount] = this;
            g_activeObjectCount++;
        }
    }
}