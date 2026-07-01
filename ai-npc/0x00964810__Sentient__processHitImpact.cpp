// FUNC_NAME: Sentient::processHitImpact
// Address: 0x00964810
// Role: Process a hit/impact event on a sentient character, record damage info, update global hit statistics, and replicate to network (multiplayer).

void __fastcall Sentient::processHitImpact(void* thisPtr)
{
    // Global hit manager singleton
    int* hitMgr = (int*)DAT_01223484;
    if (!hitMgr) return;

    // Current character state (from offset +0xdc)
    int charState = *(int*)((char*)thisPtr + 0xdc);
    int hitListPtr;

    // Determine which list to use based on state (states 0xb/0xc redirect to alternative lists)
    if (charState == 0xb) {
        hitListPtr = *(int*)((char*)thisPtr + 0x588);
    }
    else if (charState == 0xc) {
        hitListPtr = *(int*)((char*)thisPtr + 0x6e8);
    }
    else {
        hitListPtr = charState;  // fallback, likely a small state ID
    }

    // Only process if we're in a valid hit-receiving state (5,7, or 6 with a flag)
    if (!(charState == 5 || charState == 7 ||
          (charState == 6 && *(char*)((char*)thisPtr + 0x1ad) != '\0')))
        return;

    int* container = (int*)DAT_0112b9b4;
    if (!container) return;

    // Get the hit data array from a helper
    int* hitArray = (int*)FUN_00963f80(*(int*)((char*)thisPtr + 0x1b8));
    if (!hitArray) return;

    // Index for current hit slot (offset +0x1b0)
    uint slotIndex = *(uint*)((char*)thisPtr + 0x1b0);
    if (slotIndex >= *(uint*)(hitArray + 8)) return;

    // Extract hit position (4 float vector) from the array element
    float* hitElem = *(float**)(*(int*)(hitArray + 4) + slotIndex * 4);
    struct { float x, y, z, w; } hitPos;
    hitPos.x = hitElem[0x20/4];
    hitPos.y = hitElem[0x24/4];
    hitPos.z = hitElem[0x28/4];
    hitPos.w = hitElem[0x2c/4];

    // Logging / debug section
    if (FUN_00445250()) {
        if (*(int*)(hitMgr + 8) != 0) { // Multiplayer: transform hit position to world space
            FUN_008a3d20(&hitPos);
        }

        // Build a formatted log string from two source strings
        char* logStr = 0;
        int logLen = 0, logCap = 0;
        void (*logFree)(void*) = 0;

        int* stringAHandle = 0;
        char* strA = *(char**)FUN_00963f60(&stringAHandle);
        if (!strA) strA = (char*)&DAT_0120546e;  // empty placeholder

        int* stringBHandle = 0;
        char* strB = *(char**)FUN_00963f40(&stringBHandle);
        if (!strB) strB = (char*)&DAT_0120546e;

        FUN_004d4ad0(&logStr, "%s %s", strB, strA);

        // Free temporary string handles (via stored function pointers in the handle arrays)
        if (stringBHandle) (*(void (*)(int*))((int*)stringBHandle + 3))(stringBHandle);
        if (stringAHandle) (*(void (*)(int*))((int*)stringAHandle + 3))(stringAHandle);

        char* msg = logStr ? logStr : (char*)&DAT_0120546e;
        FUN_00568200(msg);  // output log message

        // Process hit attachment data (weapons, damage modifiers, etc.)
        uint impactID = 0;
        uint otherImpactID = 0;
        char* namePtr = 0;

        if (*(char*)((char*)thisPtr + 500) != '\0') {  // flag at +0x1f4
            if (*(int*)(hitMgr + 8) == 0) {  // single player path
                int itemCount = *(int*)((char*)thisPtr + 0x3c8);
                int** itemList = *(int***)((char*)thisPtr + 0x3c4);
                for (uint i = 0; i < (uint)itemCount; i++) {
                    int* item = itemList[i];
                    int type = *(int*)((char*)item + 0x14);
                    if (type == 2) {
                        impactID = *(uint*)((char*)item + 0x5c);
                    }
                    else if (type == 1) {
                        namePtr = (char*)item + 0x20;
                        if (FUN_0089c630()) {
                            otherImpactID = *(uint*)((char*)item + 0x5c);
                        }
                    }
                }
            }
            else {  // multiplayer path
                int itemCount = *(int*)((char*)thisPtr + 0x33c);
                int** itemList = *(int***)((char*)thisPtr + 0x338);
                for (int i = 0; i < itemCount; i++) {
                    int* item = itemList[i];
                    int type = *(int*)((char*)item + 0x14);
                    if (type == 2) {
                        impactID = *(uint*)((char*)item + 0x5c);
                        otherImpactID = impactID;
                    }
                    else if (type == 1) {
                        namePtr = (char*)item + 0x20;
                    }
                }
            }
        }

        // Propagate hit data to global manager
        FUN_008a2a60(*(char*)((char*)thisPtr + 500));
        *(uint*)(hitMgr + 0x3ac) = otherImpactID;
        *(uint*)(hitMgr + 0x3b0) = impactID;
        if (!namePtr) namePtr = (char*)&DAT_00e2f044;
        FUN_004d3d90(namePtr);

        uint timeVal = *(uint*)((char*)thisPtr + 0x1e0);
        *(int*)(hitMgr + 0x398) = timeVal * 2;
        *(uint*)(hitMgr + 0x394) = timeVal;

        float absTime = FUN_0095c2c0();
        *(float*)(hitMgr + 0x39c) = absTime;
        uint extraTimeA = FUN_0095c2b0();
        *(uint*)(hitMgr + 0x3a0) = extraTimeA;
        *(uint*)(hitMgr + 0x3a4) = *(uint*)((char*)thisPtr + 0x1dc);
        uint extraTimeB = FUN_0095c2a0();
        *(uint*)(hitMgr + 0x3a8) = extraTimeB;

        FUN_008a3d30(0);
        *(uint*)(hitMgr + 0x37c) &= 0xffffdfff;
        *(int*)(hitMgr + 0x3b4) = -1;
        *(int*)((char*)thisPtr + 0x1e4) = 7;  // set state flag
        FUN_008a3be0((int*)((char*)thisPtr + 0x1a8));

        // Multiplayer replication section
        if (*(int*)(hitMgr + 8) != 0) {
            // Copy hit info struct (32 bytes at +0x1a8) for network sending
            char hitCopy[32];
            memcpy(hitCopy, (void*)((char*)thisPtr + 0x1a8), 32);
            FUN_00b1a890();
            FUN_00b22400((int)((char*)hitMgr + 0x38));
            uint netId = FUN_00ad9f90();
            FUN_008a3530(netId);

            // Temporary array for function pointer table (size 197*4? unused except first element)
            void* funcTable[197];
            FUN_008a2880(funcTable);

            // Count item types in multiplayer list
            int count1 = 0, count3 = 0;
            int itemCount = *(int*)((char*)thisPtr + 0x33c);
            int** itemList = *(int***)((char*)thisPtr + 0x338);
            for (int i = 0; i < itemCount; i++) {
                int type = *(int*)((char*)itemList[i] + 0x10);
                if (type == 1) count1++;
                else if (type == 3) count3++;
            }
            *(int*)((char*)container + 0x54) = count1;
            *(int*)((char*)container + 0x58) = count3;

            funcTable[0] = (void*)PTR_FUN_00e3a9cc;  // set up vtable?
            FUN_00ad9db0();
        }

        // Clear and set final flags
        *(uint*)((char*)thisPtr + 0x6f4) &= 0xffe7ffff;
        *(uint*)((char*)thisPtr + 0x6f4) |= 1;
        *(char*)(DAT_01129908 + 0x19) = 0;
        DAT_0112ff60 = 0;
        FUN_00565ff0();

        // Free the log string if allocated
        if (logStr) logFree(logStr);
    }
}