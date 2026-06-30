// FUNC_NAME: SoundEffect::playFromEvent
void __thiscall SoundEffect::playFromEvent(int *this, int *eventData) {
    int currentSound;
    int *newSound;
    undefined4 *allocatedVector;

    // If a sound is already playing, stop it via virtual function at vtable+0x128
    if (this[0x4c] != 0) {
        (**(code **)(*this + 0x128))();
    }

    if (eventData != 0) {
        // eventData->someObject->typeID (offset +0x18 points to an object, +8 is type)
        int typeID = *(int *)(*(int *)(eventData + 0x18) + 8);
        if (typeID == 0x1961bed) { // Event type: play new sound by ID
            int soundID = *(int *)(eventData + 0x14);
            int manager = FUN_0044b8b0(); // Get sound resource manager
            if (manager == 0) {
                newSound = (int *)0x0;
            } else {
                newSound = (int *)FUN_004a4070(soundID); // Create/shared sound object
            }
            this[0x4c] = (int)newSound;
            // If +0x161 byte is clear (not muted?), start the sound
            if (*(char *)((int)this + 0x161) == '\0') {
                (**(code **)(*newSound + 0x24))(); // virtual start/play
            }
            currentSound = this[0x4c];
            allocatedVector = (undefined4 *)FUN_009c8e50(0x10); // malloc 16 bytes
            if (allocatedVector == (undefined4 *)0x0) {
                *(undefined4 *)(currentSound + 4) = 0; // clear position pointer
            } else {
                // Copy 4 floats from eventData offsets 0x1c,0x20,0x24,0x28 into vector
                *allocatedVector = *(undefined4 *)(eventData + 0x1c);
                allocatedVector[1] = *(undefined4 *)(eventData + 0x20);
                allocatedVector[2] = *(undefined4 *)(eventData + 0x24);
                allocatedVector[3] = *(undefined4 *)(eventData + 0x28);
                // Store vector pointer in the sound object at +4 (position data)
                *(undefined4 **)(currentSound + 4) = allocatedVector;
            }
        } else if (typeID == -0xc0deffc) { // Another event type (e.g., stop or update)
            int param = *(int *)(eventData + 0x14);
            int manager = FUN_0044b8b0();
            if (manager == 0) {
                newSound = (int *)0x0;
            } else {
                newSound = (int *)FUN_004a3da0(manager, param, 0); // Find sound object by ID
            }
            this[0x4c] = (int)newSound;
            if (*(char *)((int)this + 0x161) == '\0') {
                (**(code **)(*newSound + 0x24))(); // Start/update it
            }
        } else {
            goto SOUND_END_CHECK;
        }
        FUN_0046ed10(); // Post-event processing
    }

SOUND_END_CHECK:
    // If no sound is active or the sound's isValid virtual function (+0x14) returns false
    if (((int *)this[0x4c] == (int *)0x0) ||
        ((**(code **)(*(int *)this[0x4c] + 0x14))() == '\0')) {
        // Stop both sound handles if they are running
        if ((*(byte *)(this + 0x58) & 1) != 0) {
            FUN_004086d0(&DAT_01206970); // Stop sound handle 1
            *(byte *)(this + 0x58) = *(byte *)(this + 0x58) & 0xfe; // Clear bit 0
        }
        if ((*(byte *)(this + 0x58) & 2) != 0) {
            FUN_004086d0(&DAT_01206980); // Stop sound handle 2
            *(byte *)(this + 0x58) = *(byte *)(this + 0x58) & 0xfd; // Clear bit 1
        }
        return;
    }
    // Sound is active and valid: ensure both handles are playing
    if ((*(byte *)(this + 0x58) & 2) == 0) {
        if (DAT_01206980 != 0) {
            FUN_00407e60(this + 0xf, &DAT_01206980); // Start sound handle 2 with this as source
        }
        *(byte *)(this + 0x58) = *(byte *)(this + 0x58) | 2; // Set bit 1
    }
    if ((*(byte *)(this + 0x58) & 1) != 0) {
        return; // Handle 1 already running
    }
    if (DAT_01206970 != 0) {
        FUN_00407e60(this + 0xf, &DAT_01206970); // Start sound handle 1
    }
    *(byte *)(this + 0x58) = *(byte *)(this + 0x58) | 1; // Set bit 0
    return;
}