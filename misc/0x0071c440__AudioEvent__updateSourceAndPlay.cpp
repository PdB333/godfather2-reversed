// FUNC_NAME: AudioEvent::updateSourceAndPlay
// Function address: 0x0071c440
// Role: Initializes/updates an audio event, links it into a list, checks for specific audio events by hash,
// and conditionally triggers a sound based on game state.

void __thiscall AudioEvent::updateSourceAndPlay(
    AudioEvent* thisPtr,
    AudioManager* manager,      // param_2: likely AudioManager or SoundManager with vtable
    GameObject* source,         // param_3: source object (may be null)
    float volume,               // param_4: volume or playback parameter
    AudioSourceID* sourceInfo)  // param_5: pointer to 12 bytes (source ID hash + sub ID)
{
    char cVar1;
    int* listNode;
    int result;
    int hashResult;
    int* sourceData;
    int temp;
    int obj;
    unsigned int soundID;
    unsigned int param;

    // Clear bit 11 (0x400) of flags at +0x3c (sound flags)
    *(unsigned short*)(thisPtr + 0x3c) &= 0xF7FF;

    // Copy source info (12 bytes) into local storage
    *(unsigned long long*)(thisPtr + 0x10) = *sourceInfo;          // +0x10: source hash (8 bytes)
    *(unsigned int*)(thisPtr + 0x18) = *(unsigned int*)(sourceInfo + 1); // +0x18: sub ID (4 bytes)

    // Get pointer to list node at +0x08 (likely linked list of active events)
    int* pList = (int*)(thisPtr + 8);
    int* sourceNode;
    if (source == nullptr) {
        sourceNode = nullptr;
    } else {
        sourceNode = (int*)((char*)source + 0x48); // +0x48 is offset to some master node?
    }

    // Insert this event into the list (if not already)
    if (*pList != sourceNode) {
        if (*pList != nullptr) {
            // Remove old node
            FUN_004daf90(pList);
        }
        *pList = (int)sourceNode;
        if (sourceNode != nullptr) {
            *(int*)(thisPtr + 0xc) = sourceNode[1]; // store back link
            sourceNode[1] = (int)pList;             // link list
        }
    }

    // If the event hasn't been initialized with a source type yet (bit 0 of +0x3d)
    if ((*(unsigned char*)(thisPtr + 0x3d) & 1) == 0) {
        // Try to find a specific audio event by hash 0x383225a1 (e.g., "DONOR_WARNING" or similar)
        sourceInfo = nullptr;
        cVar1 = (*(code**)(*(int*)source + 0x10))(0x383225a1, &sourceInfo); // virtual call to source object
        if (cVar1 == '\0' || sourceInfo == nullptr) {
            // If not found, try hash 0x55859efa
            sourceInfo = nullptr;
            cVar1 = (*(code**)(*(int*)source + 0x10))(0x55859efa, &sourceInfo);
            if (cVar1 != '\0' && sourceInfo != nullptr) {
                // Set bit 9 (0x200) to indicate second event found
                *(unsigned short*)(thisPtr + 0x3c) |= 0x200;
            }
        } else {
            // Found first event, set bits 9 and 10 (0x200 and 0x80)
            *(unsigned short*)(thisPtr + 0x3c) |= 0x280;
        }
        // Mark as initialized (bit 8)
        *(unsigned short*)(thisPtr + 0x3c) |= 0x100;
    }

    // If volume is negative, stop here
    if (volume < 0.0f) {
        return;
    }

    // Check if volume has just become zero from negative? Actually condition: current volume <= 0 and != 0
    if (*(float*)(thisPtr + 0x1c) <= 0.0f && *(float*)(thisPtr + 0x1c) != 0.0f) {
        // Get the source node's data (if any)
        int* data = (int*)*pList;
        if (data == nullptr) {
            obj = 0;
        } else {
            obj = (int)data - 0x48; // adjust offset
        }

        // If bit 9 (0x200) is set and we have an object
        if (((*(unsigned short*)(thisPtr + 0x3c) >> 9) & 1) != 0 && obj != 0) {
            // Try to get a data pointer from manager by hash 0x369ac561
            sourceInfo = nullptr;
            cVar1 = (*(code**)(*(int*)manager + 0x10))(0x369ac561, &sourceInfo);
            hashResult = (int)sourceInfo;
            if (cVar1 != '\0' && sourceInfo != nullptr) {
                // Get the game object from DAT_01131040? This might be a global singleton
                int* globalObj = (int*)FUN_0043b870(DAT_01131040);
                // If global object exists and can provide a state (via virtual at +0x1c with 0x100) or world state is not 4
                if ((globalObj == nullptr) ||
                    (cVar1 = (*(code**)(*globalObj + 0x1c))(0x100), cVar1 == '\0') ||
                    (result = FUN_00800b60(), result != 4))
                {
                    // Normal path
                    obj = *(int*)(hashResult + 0x2584);
                    if (obj == 0 || obj == 0x48 || (*(unsigned char*)(obj + 0x38) & 1) == 0) {
                        goto endCheck;
                    }

                    cVar1 = FUN_00690150(1); // Check if in menu or game?
                    param = 0;
                    if (cVar1 == '\0') {
                        soundID = FUN_006fbc40(0, 0);
                        // Use static sound hash 0x9aa8b68f
                        FUN_007f96a0(0x9aa8b68f, 0, soundID, param);
                    } else {
                        soundID = FUN_006fbc40(0, 0);
                        FUN_007f96a0(0x16554726, 0, soundID, param);
                    }
                } else {
                    // State is 4 (maybe "in game" vs menu)
                    cVar1 = FUN_00690150(1);
                    param = 0;
                    if (cVar1 == '\0') {
                        soundID = FUN_006fbc40(0, 0);
                        FUN_007f96a0(0xb1e47ca8, 0, soundID, param);
                    } else {
                        soundID = FUN_006fbc40(0, 0);
                        FUN_007f96a0(0xef8ff94d, 0, soundID, param);
                    }
                }
                // Stop any previous sound?
                FUN_006fbc70();
            }
        }
    }

endCheck:
    // Set bit 6 (0x40) in flags if not already set
    if ((*(unsigned char*)(thisPtr + 0x3c) >> 5 & 1) == 0) {
        *(unsigned short*)(thisPtr + 0x3c) |= 0x40;
    }

    // Store the new volume/parameter
    *(float*)(thisPtr + 0x1c) = volume;
    return;
}