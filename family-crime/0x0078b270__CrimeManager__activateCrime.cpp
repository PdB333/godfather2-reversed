// FUNC_NAME: CrimeManager::activateCrime
void __thiscall CrimeManager::activateCrime(uint crimeId)
{
    int objFromOffset1C; // pointer to some object (e.g., mission data) at +0x1c
    char isHostOrLocal;

    // Check various flags and conditions:
    // - flags at (*(param_1+0x5c)->0x1f98) have bits 0x50c (some global state)
    // - object at +0x1c exists
    // - object at +0x1c != 0x3c (maybe a state value)
    // - bit 0 at +0x3c is clear (not already pending)
    // - crimeId matches object->crimeId at +0xec
    // - object->crimeId != 0
    if ((((*(uint32*)(*(int32*)(this + 0x5c) + 0x1f98) & 0x50c) != 0) &&
         (objFromOffset1C = *(int32*)(this + 0x1c), objFromOffset1C != 0) &&
         (objFromOffset1C != 0x3c)) &&
        ((((*(uint8*)(this + 0x3c) & 1) == 0 &&
          (crimeId == *(uint32*)(objFromOffset1C + 0xec))) &&
         (*(uint32*)(objFromOffset1C + 0xec) != 0)))) {

        // Set flag bit 0: activation pending
        *(uint32*)(this + 0x3c) = *(uint32*)(this + 0x3c) | 1;

        // Format a string using crimeId (lower 16 bits)
        // local_20 is a buffer for the formatted string
        char* formattedStr;
        eaSprintf(&formattedStr, 1, &DAT_00d69a2c, crimeId & 0xffff); // e.g. "crime_%hu"

        // Use default string if formatting returned null
        char* msg = (formattedStr != nullptr) ? formattedStr : &DAT_0120546e;

        // Send a packet with IDs 0x53504750 and 0x574b5350 (PGSP and WKSP?)
        eaSendPacket(0x53504750, 0x574b5350, msg);

        isHostOrLocal = eaIsHost(); // or eaIsMultiplayerSession()
        if (isHostOrLocal == 0) {
            // Local activation (not multiplayer? not server?)
            *(uint32*)(this + 0x3c) = *(uint32*)(this + 0x3c) | 2; // set bit 1

            // Play sound index 0x2f (47)
            playSound(0x2f);

            uint32 zero = 0;
            uint32 eventHandle = beginEvent(0, 0);           // start an event
            createEvent(0xd38628d8, 0x74, eventHandle, zero); // event with hash
            endEvent();
            someFunction(); // cleanup/transition

            // Call this method a second way?
            callInternalMethod(this, 0); // FUN_0093ae10(this,0)

            // If additional object at +0xf0 exists, call its method
            if (*(int32*)(objFromOffset1C + 0xf0) != 0) {
                callOtherMethod(*(int32*)(objFromOffset1C + 0xf0), 0, 0, 0, 0);
            }
        }

        // Free the formatted string if allocated
        if (formattedStr != nullptr) {
            eaFree(formattedStr);
        }
    }
}