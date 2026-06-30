// FUNC_NAME: Character::updateScriptedBehavior
void Character::updateScriptedBehavior(void* contextObj) {
    // Get the character object from the context (likely via a script wrapper)
    int charBase = getCharacterFromContext(contextObj); // 0x004b2740

    // Flag at +0x904 indicates whether a scripted dialogue/action is locked
    if (*(char*)(charBase + 0x904) != '\0') {
        return; // Already locked, do nothing
    }

    // Check if character has a target/active state (+0x98 non-zero) and if audio is playing
    if (*(int*)(charBase + 0x98) != 0 && isAudioPlaying()) {
        // Lock the scripted behavior and push an "end" command onto the script stack
        *(char*)(charBase + 0x904) = 1;
        int* stackPtr = (int*)(DAT_012068e8 + 0x14);
        **(int**)(DAT_012068e8 + 0x14) = &PTR_LAB_011245f0; // command pointer (some script opcode)
        *stackPtr = *stackPtr + 4;
        *(int*)*stackPtr = (int)contextObj; // context object
        *stackPtr = *stackPtr + 4;
        *(int*)*stackPtr = 0; // null argument
        *stackPtr = *stackPtr + 4;
        return;
    }

    // Push a "start" command onto the script stack
    int globalBase = DAT_012068e8;
    uint soundId = getCurrentSoundId(); // 0x0061eb30
    **(int**)(globalBase + 0x14) = &PTR_LAB_01124604; // command pointer for "start"
    *(int*)(globalBase + 0x14) += 4;
    **(int**)(globalBase + 0x14) = (int)contextObj;
    *(int*)(globalBase + 0x14) += 4;
    **(int**)(globalBase + 0x14) = soundId;
    int* stackPtr2 = (int*)(globalBase + 0x14);
    *stackPtr2 = *stackPtr2 + 4;

    // Get the current screen dimensions from a global structure (FS segment +0x2c, +0x24)
    int screenData = **(int**)(__readfsdword(0x2c) + 0x24);
    int screenWidth = *(int*)(screenData + 0x16c);

    // Get the character's flags at +0xb0
    uint flags = *(uint*)(charBase + 0xb0);

    // Determine the rendering rectangle for subtitles/dialogue box
    // This uses ushort values from a table indexed by screen width (if within 0x1000)
    ushort* rectTable = (ushort*)((screenWidth < 0x1000) ? (&DAT_011a0f28 + screenWidth * 0x38) : 0);

    if ((flags & 0x10) != 0) {
        // Bit 4 set: calculate rendering rectangle from target positions (offset +0xd8, +0xd4, +0xd0, +0xcc)
        float targetW = (float)*(int*)(charBase + 0xd8) + ((*(int*)(charBase + 0xd8) < 0) ? DAT_00e44578 : 0.0f);
        float targetZ = (float)*(int*)(charBase + 0xd4) + ((*(int*)(charBase + 0xd4) < 0) ? DAT_00e44578 : 0.0f);
        float targetY = (float)*(int*)(charBase + 0xd0) + ((*(int*)(charBase + 0xd0) < 0) ? DAT_00e44578 : 0.0f);
        float targetX = (float)*(int*)(charBase + 0xcc) + ((*(int*)(charBase + 0xcc) < 0) ? DAT_00e44578 : 0.0f);
        render2DBox(targetX, targetY, targetZ, targetW,
                    (float)*(ushort*)(rectTable + 2), (float)*(ushort*)(rectTable + 4));
    } else if ((flags & 0x20) != 0) {
        // Bit 5 set: handle dialogue mode (show/hide dialog, play sound)
        startDialogue(); // 0x004b2420
        if (*(float*)(charBase + 0xc4) <= DAT_00e44598) {
            hideDialog(); // 0x004b23a0
            playSound(null); // 0x0061ecd0
        } else {
            playSound(null);
        }
    } else if ((flags & 0x40) != 0) {
        // Bit 6 set: process child objects (subordinates, etc.)
        // Calculate rectangle based on screen width/height proportions
        int rectWidth = getScreenWidth(); // 0x0061ede0
        int rectHeight = getScreenHeight(); // 0x0061ee00
        float propWidth = 0.0f, propHeight = 0.0f;
        if (rectWidth != 0) {
            propWidth = (float)*(ushort*)(rectTable + 2) / (float)rectWidth;
            if (rectWidth < 0) propWidth += DAT_00e44578;
        }
        if (rectHeight != 0) {
            propHeight = (float)*(ushort*)(rectTable + 4) / (float)rectHeight;
            if (rectHeight < 0) propHeight += DAT_00e44578;
        }
        if (((flags & 0x100) == 0) && (propWidth < propHeight)) {
            propHeight = propWidth;
        }
        float finalWidth = (float)rectWidth;
        if (rectWidth < 0) finalWidth += DAT_00e44578;
        float finalHeight = (float)rectHeight;
        if (rectHeight < 0) finalHeight += DAT_00e44578;
        render2DBox((float)*(ushort*)(rectTable + 2) - finalWidth * propHeight,
                    (float)*(ushort*)(rectTable + 4) - finalHeight * propHeight,
                    finalWidth * propHeight, finalHeight * propHeight,
                    (float)*(ushort*)(rectTable + 2), (float)*(ushort*)(rectTable + 4));
        // NOTE: The scaling factor DAT_00e2cd54 is applied but omitted for clarity (likely aspect ratio)
    }

    // Copy position/rotation data to the object's data block
    float posX = *(float*)(charBase + 0xb8);
    float posY = *(float*)(charBase + 0xbc);
    float posZ = *(float*)(charBase + 0xc0);
    float rotW = *(float*)(charBase + 0xc4);
    if (*(int*)(charBase + 0x98) != 0) {
        int* dataBlock = (int*)(*(int*)(charBase + 0x9c) + 0x54);
        for (int i = 0; i < 2; i++) {
            *(dataBlock - 1) = posX;
            *dataBlock = posY;
            *(dataBlock + 1) = posZ;
            dataBlock += 4;
        }
        if (*(int*)(charBase + 0x98) != 0) {
            int* rotBlock = (int*)(*(int*)(charBase + 0x9c) + 0x5c);
            for (int i = 0; i < 2; i++) {
                *rotBlock = rotW;
                rotBlock += 4;
            }
        }
    }
    updateAudio(); // 0x0061ec50

    // Re-read flags; bit 5 and 6 trigger event dispatching
    flags = *(uint*)(charBase + 0xb0);
    if ((flags & 0x20) != 0) {
        // Dialogue mode: dispatch an event to start dialogue
        int uniqueId = generateUniqueId(); // 0x004b32e0
        dispatchEvent(*(int*)(screenData + 0x178), charBase, eventCallback1, 0,
                      ((flags & 0x80) != 0) ? 0x16 : 0x15, uniqueId);
                      // 0x00434750, event type codes
        return;
    }
    if ((flags & 0x40) == 0) {
        // No child mode: dispatch a different event
        dispatchEvent(*(int*)(screenData + 0x178), charBase, eventCallback1, 0,
                      ((flags & 0x200) != 0) ? 0x17 : 0x19, 0);
    } else {
        // Child mode: iterate over child objects
        uint childCount = *(uint*)(charBase + 0x6f8);
        if (childCount != 0) {
            int childBase = charBase + 0x138;
            for (uint i = 0; i < childCount; i++) {
                if (childBase != 0 && *(char*)(childBase + 0x18) != '\0') {
                    int* allocated = (int*)allocateMemory(8); // 0x009c8e50
                    *allocated = charBase;
                    *(char*)(allocated + 1) = (char)i;
                    uint8 pair = generateUniqueId();
                    dispatchEvent(*(int*)(screenData + 0x178), (int)(pair >> 0x20),
                                  eventCallback2, 0, 0x14, (int)pair);
                }
                childBase += 0x5c; // each 0x5c bytes
            }
        }
    }
    return;
}