// FUNC_NAME: StreamManager::startStream
int __thiscall StreamManager::startStream(int categoryIndex, const char* soundName, int startTime, int sourceHandle)
{
    // Get pointer to category entry in the category array (at offset +0x206f)
    int* categoryPtr = &this->categoryArray[categoryIndex];

    // Call virtual function at vtable+0xa0 (likely PreprocessSound or something)
    (*(void(__thiscall**)(int))(this->vtable + 0x28))(categoryIndex); // +0xa0 /4 = 0x28

    // Check if audio engine is present
    if (this->audioEngine != nullptr && *categoryPtr != 10) { // 10 might be an invalid category
        int nextSlot = this->nextSlotIndex; // +0x241c
        int attempt = 0;
        do {
            // Check if this slot is free (state == -1)
            if (this->slots[nextSlot].state == -1) { // slot state at +0x20ab
                char* slotNameBuffer = this->slots[nextSlot].nameBuffer; // +0x2084
                this->nextSlotIndex = (nextSlot + 1) % 10;

                byte slotFlags = this->slots[nextSlot].flags; // +0x20d0

                LOCK();
                *this->atomicCounter += 1; // probably a thread-safe counter
                UNLOCK();

                int soundId = this->totalSoundCount; // +0x241d
                this->totalSoundCount = soundId + 1;

                this->slots[nextSlot].soundId = soundId;       // +0x20ac
                this->slots[nextSlot].state = categoryIndex;   // +0x20ab

                _strncpy(slotNameBuffer, soundName, 0x80);

                this->slots[nextSlot].someValue1 = 0x1000; // +0x20a6
                this->slots[nextSlot].someValue2 = 0x1000; // +0x20a7

                // Clear bit 0 of flags
                this->slots[nextSlot].flags = slotFlags & 0xFFFFFFFE;

                // Set slot state byte to 3 (maybe "initializing")
                this->slots[nextSlot].initState = 3; // +0x20c3

                // Clear three bytes in a separate array (maybe per-slot flags)
                this->slotInfoArray[nextSlot].byte0 = 0; // +0x830d
                this->slotInfoArray[nextSlot].byte1 = 0; // +0x830e
                this->slotInfoArray[nextSlot].byte2 = 0; // +0x830f

                this->slots[nextSlot].someInt1 = 0;   // +0x20c4
                this->slots[nextSlot].someInt2 = 0x20; // +0x20c5
                this->slots[nextSlot].someInt3 = 0;   // +0x20c6

                // Clear two pairs of shorts
                this->slots[nextSlot].shortPair1[0] = 0;
                this->slots[nextSlot].shortPair1[1] = 0; // +0x20c7
                this->slots[nextSlot].shortPair2[0] = 0;
                this->slots[nextSlot].shortPair2[1] = 0; // +0x20c9

                // If startTime is negative, set a default start time from a global constant
                if (startTime < 0) {
                    this->slots[nextSlot].startTime = DAT_00e2af58; // +0x20a4
                }

                // Determine the target audio object based on sourceHandle
                int* audioTarget = nullptr;
                // FUN_005dc670 likely converts sourceHandle to an object pointer
                int* sourceObj = (int*)FUN_005dc670(sourceHandle); // returns a pointer or null
                int sourceObjType = 0;
                if (sourceObj != nullptr) {
                    sourceObjType = sourceObj[0xAE]; // +0x2b8? Actually offset 0x2b8 /4 = 0xAE
                }

                // Compare source type to known types stored in the manager
                if (sourceObjType == this->type1) { // +0x100
                    audioTarget = (int*)((char*)this + categoryIndex * 0x30 + 0x1a4);
                } else if (sourceObjType == this->type2) { // +0xa5
                    audioTarget = (int*)((char*)this + categoryIndex * 0xC + 0x2A8); // wrong? Wait, recalc: +0xaa*4 = 0x2A8
                } else if (sourceObjType == this->type3) { // +0x116
                    audioTarget = (int*)((char*)this + categoryIndex * 0xC + 0x46C); // +0x11b*4 = 0x46C
                } else {
                    audioTarget = (int*)((char*)this + categoryIndex * 0x30 + 0xA0);
                }

                // If audioTarget pointer is null, return soundId
                if (audioTarget == nullptr) {
                    return soundId;
                }

                // Now set up the audio playback
                if (audioTarget[1] == 0) { // +4 maybe "isPlaying" flag
                    // Not playing, so start new sound
                    if (audioTarget[6] != 0) { // +0x18 maybe a different pointer
                        audioTarget[6] = 0;
                    }
                    if (startTime >= 0) {
                        // Set start time from current audio engine time
                        double engineTime = *(double*)(this->audioEngine + 8); // +8 in engine
                        this->slots[nextSlot].startTime = (double)startTime * DAT_00e446c8 + engineTime;
                    }
                    // Initialize sound via audio engine calls
                    FUN_00c9eac0(); // Probably "Sound::Start" or similar
                    double* dptr = (double*)&this->slots[nextSlot].someDouble;
                    *dptr = engineTime;
                    FUN_00c9eae0();
                } else {
                    // Already playing, add this as a second instance? Set up auxiliary sends
                    int* alloc1 = (int*)FUN_005e9d10(); // Allocate voice?
                    if (alloc1 != nullptr) {
                        this->slots[nextSlot].voiceHandle1 = alloc1; // +0x20de
                    }

                    FUN_00c9eac0();
                    int* alloc2 = (int*)FUN_005e9d10();
                    if (alloc2 != nullptr) {
                        FUN_00ca4e90(0, 1.0f); // Set aux send 0 to 1.0
                    }

                    int* alloc3 = (int*)FUN_005e9d10();
                    if (alloc3 != nullptr) {
                        FUN_00ca4e90(0, 1.0f);
                    }

                    int* alloc4 = (int*)FUN_005e9d10();
                    if (alloc4 != nullptr) {
                        FUN_00ca4e90(0, DAT_00e4459c); // Some float constant
                    }

                    // Set up AuxSend1
                    float aux1Value;
                    int aux1Var = FUN_004dafd0("AuxSend1", &aux1Value);
                    int* aux1Obj = (int*)FUN_005e9d90(aux1Var, &aux1Value);
                    if (aux1Obj != nullptr) {
                        FUN_00ca4e90(0, 0.0f);
                    }

                    // AuxSend2
                    float aux2Value;
                    int aux2Var = FUN_004dafd0("AuxSend2", &aux2Value);
                    int* aux2Obj = (int*)FUN_005e9d90(aux2Var, &aux2Value);
                    if (aux2Obj != nullptr) {
                        FUN_00ca4e90(0, 0.0f);
                    }

                    // AuxSend3
                    float aux3Value;
                    int aux3Var = FUN_004dafd0("AuxSend3", &aux3Value);
                    int* aux3Obj = (int*)FUN_005e9d90(aux3Var, &aux3Value);
                    if (aux3Obj != nullptr) {
                        FUN_00ca4e90(0, 0.0f);
                    }

                    // SendToMaster
                    double masterValue;
                    int masterVar = FUN_004dafd0("SendToMaster", &masterValue);
                    int* masterObj = (int*)FUN_005e9d90(masterVar, &masterValue);
                    if (masterObj != nullptr) {
                        FUN_00ca4e90(0, 0.0f);
                    }

                    // Allocate additional voices and set parameters
                    int* alloc5 = (int*)FUN_005e9d10();
                    if (alloc5 != nullptr) {
                        FUN_00ca4e90(0, 0.0f);
                        FUN_00ca4e90(1, 0.0f);
                        FUN_00ca4e90(2, 1.0f);
                        FUN_00ca4e90(3, 0.0f);
                        FUN_00ca4e90(4, 1.0f);
                    }

                    // Set start time for this instance
                    double engineTime = *(double*)(categoryPtr[0x160] + 8); // wait, categoryPtr? Actually at the beginning we had piVar1 = this + categoryIndex*4 + 0x206f, so piVar1 is the category entry. But here it uses piVar1[0x160]. That seems off. Possibly it's supposed to be this->audioEngine? Let's reinterpret: The original code: adStack_14[0] = *(double *)(piVar1[0x160] + 8); but piVar1 is the category entry, which is likely a pointer to an audio engine? That would mean the category entry contains an engine pointer at offset 0x160. Hmm. Let's revise based on original: piVar1 = param_1 + param_2 * 4 + 0x206f; so piVar1 is an int pointer to a member of the "this" class. Then code later uses piVar1[0x160] as a pointer. That would be (this + categoryIndex*4 + 0x206f)[0x160] = *(this + categoryIndex*4 + 0x206f + 0x160*4). That's a valid offset into the same object. So the category entry likely contains an index to the audio engine? Actually it's more likely that piVar1 is a pointer to a structure that itself contains an offset 0x160 (which is a pointer to the audio engine). But that seems convoluted. Alternatively, maybe the decompiler misinterpreted the array indexing; piVar1 might be just a pointer within the object, and [0x160] accesses the audio engine pointer from the object. Given typical patterns, the sound function often stores the engine pointer at a fixed offset in the manager. So I'll assume that adStack_14 is set to this->audioEngine->currentTime (offset +8). Then later it's used to set the start time if startTime>=0. So I'll use this->audioEngineTime at offset +8.

                    // Actually in the "already playing" branch, after all the allocations, it sets:
                    // adStack_14[0] = *(double *)(piVar1[0x160] + 8);
                    // and then calls FUN_00c9eae0(); and then FUN_005ebfa0(piVar1, sourceHandle, audioTarget);
                    // I'll simplify: set start time from engine
                    double engineTimeNow = this->audioEngine->currentTime; // assuming
                    this->slots[nextSlot].startTime = engineTimeNow;
                    FUN_00c9eae0();
                    FUN_005ebfa0(categoryPtr, sourceHandle, audioTarget);
                }

                // If startTime >= 0, set the actual start time (converted)
                if (startTime >= 0) {
                    this->slots[nextSlot].startTime = (double)startTime * DAT_00e446c8 + this->slots[nextSlot].startTime;
                }

                // If slot flags bit 0 was not set, call a notification function
                if ((slotFlags & 1) == 0) {
                    FUN_00ac2870(&DAT_00e2aea0); // Some global event
                }

                // Mark slot as active
                this->slots[nextSlot].active = 1; // +0x20ad

                // Set up a timer or callback for when the sound finishes
                FUN_00ac41a0(slotNameBuffer, 0, FUN_005f37f0, slotNameBuffer, 0);

                return soundId;
            }

            nextSlot = (nextSlot + 1) % 10;
            attempt++;
        } while (attempt < 10);
    }

    return -1; // Failed to find a free slot
}