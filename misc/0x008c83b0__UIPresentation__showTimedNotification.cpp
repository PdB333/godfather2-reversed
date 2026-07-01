// FUNC_NAME: UIPresentation::showTimedNotification
// Address: 0x008c83b0
// Role: Shows a timed notification (e.g., mission objective, crime scene) with optional entity focus, sound, and dialog.

void __thiscall UIPresentation::showTimedNotification(int this, int eventSubType, int eventMainType, float durationMultiplier) {
    bool hasFocusedEntity;
    uint32_t hash;
    int i;
    uint32_t entityCount;
    int entityArray;
    int entity;
    char local_107c; // placeholder for entity-specific data
    UIString mainString;
    UIString timeString;
    UIString formattedString;
    UIString titleString;
    int tempArrayStruct[3]; // for getEntityArray output
    char buffer[4112];

    // Check class type/version
    if (*(int*)(*(int*)(this + 0xc) + 0x54) != 0x637b907) {
        return;
    }
    if (eventMainType == 0) {
        return;
    }

    mainString.reset();
    hasFocusedEntity = false;
    titleString.reset();

    if (eventMainType == 5) {
        // --- Event type 5: possibly "objective" (checks flag bit 5) ---
        getEntityArray(tempArrayStruct);
        entityCount = tempArrayStruct[1];
        for (i = 0; i < entityCount; i++) {
            entity = *(*(int*)tempArrayStruct + i * 4);
            if (*(uint32_t*)(entity + 0x170) & (1 << 5)) {
                // Entity has the required component flag
                markTransformDirty(entity + 0x98);
                local_107c = *(char*)(entity + 0x7c);
                hasFocusedEntity = true;
                hash = 0x67e42992; // "ObjectiveNew" or similar
                goto LAB_GET_MAIN_STRING;
            }
        }
        hash = 0x3e65a5b5; // "ObjectiveGeneric" or similar
    LAB_GET_MAIN_STRING:
        GetLocalizedString(hash, &mainString);
        TriggerSFX(0x97d011e1);
        freeEntityArray(tempArrayStruct[0]);
    }
    else if (eventMainType == 6) {
        // --- Event type 6: possibly "crime scene" (checks flag bit 6) ---
        getEntityArray(tempArrayStruct);
        entityCount = tempArrayStruct[1];
        for (i = 0; i < entityCount; i++) {
            entity = *(*(int*)tempArrayStruct + i * 4);
            if (*(uint32_t*)(entity + 0x170) & (1 << 6)) {
                markTransformDirty(entity + 0x98);
                local_107c = *(char*)(entity + 0x7c);
                hasFocusedEntity = true;
                hash = 0x3d12d9b2; // "CrimeSceneNew"
                goto LAB_GET_MAIN_STRING_2;
            }
        }
        hash = 0x7d30ad95; // "CrimeSceneGeneric"
    LAB_GET_MAIN_STRING_2:
        GetLocalizedString(hash, &mainString);
        TriggerSFX(0xa3f489c1);
        freeEntityArray(tempArrayStruct[0]);
    }
    else {
        // --- Event subtype handling for non-5/6 main types ---
        if (eventSubType == 5) {
            GetLocalizedString(0xa2cd9a6, &mainString); // "Subtype5String"
        }
        else if (eventSubType == 6) {
            GetLocalizedString(0x3b67286, &mainString); // "Subtype6String"
            TriggerSFX(0xf14d9955);
        }
        else {
            return;
        }
        goto LAB_BUILD_UI;
    }

    // Common UI build path for types 5 and 6
    if (mainString.isValid()) {
        LAB_BUILD_UI:
        UIPushGroup();
        timeString.reset();
        // Convert the global time factor (seconds) multiplied by duration to hours and minutes
        uint64_t totalSeconds = (uint64_t)(*(float*)(g_globalTimeFactor + 0x70) * durationMultiplier);
        int hours = (uint32_t)totalSeconds / 3600;
        int minutes = (uint32_t)(totalSeconds / 60) % 60;
        FormatTimeToString(hours, minutes, &timeString);

        // Get current locale string for default text
        const char* defaultText = GetUICultureString();
        if (defaultText == nullptr) defaultText = "";

        // Append time to UI
        UIPrintString(0x72, defaultText); // Some slot for time prefix
        const char* timeText = timeString.getData();
        if (timeText == nullptr) timeText = "";
        UIPrintString(0x74, timeText);

        // Build formatted message string
        formattedString.reset();
        const char* msgText = mainString.getData();
        if (msgText == nullptr) msgText = "";
        StringAppend(g_someLocale, buffer, &formattedString, msgText);

        if (formattedString.isValid()) {
            const char* message = formattedString.getData();
            if (message == nullptr) message = "";
            const char* title;
            uint32_t extraData = local_107c;
            if (hasFocusedEntity) {
                title = titleString.getData();
                if (title == nullptr) title = "";
                ShowUIMessage(message, title, (void*)0x922890, extraData, 0);
            }
            else {
                ShowUIMessage(message, titleString.getData(), nullptr, 0, 0);
            }
        }

        // Cleanup formatted string
        if (formattedString.isValid()) {
            formattedString.destroy();
        }
        UIPopGroup();
    }

    // Cleanup title and main strings
    if (titleString.isValid()) {
        titleString.destroy();
    }
    if (mainString.isValid()) {
        mainString.destroy();
    }
    return;
}