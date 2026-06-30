// FUNC_NAME: GodfatherGameManager::update
void __thiscall GodfatherGameManager::update(GodfatherGameManager* this) {
    char isGameActive;
    int iResult;
    int* transformPtr;
    int objIndex;
    int objCount;
    float deltaTimeFloat;
    float10 extendedTime; // 80-bit extended precision

    // Check if game is active (not paused/menu)
    isGameActive = isGameActive(); // FUN_007f47a0
    if (isGameActive == 0) {
        // Check if game is paused
        iResult = isGamePaused(); // FUN_007ff880
        if (iResult == 0) {
            // Check flag at offset +0x1F58 bit 25 (0x2000000 = 1<<25)
            if ((((uint)this->flags1 >> 25) & 1) == 0) {
                // Check if update is needed (e.g., dirty flag)
                isGameActive = isUpdateNeeded(); // FUN_007f4800
                if (isGameActive != 0) {
                    preUpdate(this); // FUN_0081cf20 - e.g., prepare state
                }
            }
            // Set bit 25 in flags1 to indicate update started
            this->flags1 |= 0x2000000;

            // Copy world transform from global (cam/matrix?)
            transformPtr = (int*)getTransform(); // FUN_004a45c0 - returns 4 ints (maybe 4x4 matrix)
            this->transform[0] = transformPtr[0]; // +0x213C
            this->transform[1] = transformPtr[1]; // +0x2140
            this->transform[2] = transformPtr[2]; // +0x2144
            this->transform[3] = transformPtr[3]; // +0x2148

            // Get current frame number
            this->frameCount = getFrameCount(); // FUN_0045eea0, +0x2170

            // Get delta time (float) and store as int (e.g., milliseconds)
            extendedTime = (float10)getDeltaTime(); // FUN_0045fa40
            this->time = (int)(float)extendedTime; // +0x2174

            // If animation component exists, update it
            if (this->animComponent != NULL) { // +0x2F0
                updateAnimation(); // FUN_0099a7d0
            }

            // Global engine update
            globalUpdate(); // FUN_00460d90

            // Call virtual function at vtable+0x128 (e.g., updateDerived)
            (this->vtable->updateAt128)();

            // Send network state update with object hash
            sendNetworkUpdate(0x369ac561, this); // FUN_008e9cb0

            // Send network data (possibly reliable)
            sendNetworkData(this); // FUN_008ec4d0

            // Loop through managed objects
            objCount = this->objectCount; // +0x744
            for (int i = 0; i < objCount; i++) {
                objIndex = getObjectByIndex(i); // FUN_00704110
                if (objIndex != 0) {
                    updateObject(); // FUN_004719e0 - update each child object
                }
            }

            // Finalize update
            finalUpdate(this); // FUN_004e0640

            // Set debug logging level
            setDebugLog(2); // FUN_005512c0

            // Call virtual function at vtable+0x18 (e.g., postUpdate)
            (this->vtable->postUpdate)();

            return;
        }
    } else {
        // Game is inactive: set bit 0x2000 (13) in flags2 at +0x1F5C
        this->flags2 |= 0x2000;
    }
    return;
}