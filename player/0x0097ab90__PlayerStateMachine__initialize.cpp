// FUNC_NAME: PlayerStateMachine::initialize
void __fastcall PlayerStateMachine::initialize(void* thisPtr) {
    uint32_t* flags = (uint32_t*)((int)thisPtr + 0x60);
    *flags &= 0xFFFFFBFF; // Clear bit 10?

    if (((*flags >> 8) & 1) == 0) {
        initializeGameGlobals(); // FUN_00911fd0
        *flags |= 0x100; // Set bit 8
        *(uint32_t*)(DAT_011298d4 + 0x10) |= 4; // Set game state flag
    }

    if (*(void**)((int)thisPtr + 0x120) == nullptr) {
        Utf8String tempString;
        tempString.data = nullptr;
        tempString.len = 0;
        tempString.capacity = 0;
        tempString.deleter = nullptr;
        resolveStringHash(0xfb297791, &tempString); // FUN_00603330 - likely hash for "default" or something
        void* newBlock = allocateMemory(0x30, 0x10); // FUN_004eb390
        if (newBlock != nullptr) {
            // Initialize a vtable-based object
            uint32_t* obj = (uint32_t*)newBlock;
            obj[0] = &PTR_FUN_00d8f978; // vtable pointer
            obj[1] = 0;
            obj[8] = 0;
            uint32_t defaultVal = _DAT_00d5780c; // Likely 0xFFFFFFFF or zero
            obj[4] = defaultVal;
            obj[5] = defaultVal;
            obj[6] = defaultVal;
            obj[7] = defaultVal;
        }
        *(void**)((int)thisPtr + 0x120) = newBlock;

        const char* strData = tempString.data;
        if (strData == nullptr) {
            strData = &DAT_0120546e; // Fallback default string
        }
        setString(strData); // FUN_004ec1c0 - likely copies string into the allocated object?
        // Destroy temp string
        if (tempString.data != nullptr) {
            tempString.deleter(tempString.data);
        }
    }

    if (DAT_0112a638 != 0) {
        playSound((int)thisPtr + 0x50, &DAT_0112a638, 0x8000); // FUN_00408900 - start audio stream
    }

    // Initialize multiple Vector4 fields at offsets 0x170 to 0x1ac
    uint32_t vecVal = _DAT_00d5780c;
    *(uint32_t*)((int)thisPtr + 0x170) = vecVal;
    *(uint32_t*)((int)thisPtr + 0x174) = 0;
    *(uint32_t*)((int)thisPtr + 0x178) = 0;
    *(uint32_t*)((int)thisPtr + 0x17c) = 0;
    *(uint32_t*)((int)thisPtr + 0x180) = 0;
    *(uint32_t*)((int)thisPtr + 0x184) = vecVal;
    *(uint32_t*)((int)thisPtr + 0x188) = 0;
    *(uint32_t*)((int)thisPtr + 0x18c) = 0;
    *(uint32_t*)((int)thisPtr + 400) = 0;
    *(uint32_t*)((int)thisPtr + 0x194) = 0;
    *(uint32_t*)((int)thisPtr + 0x198) = vecVal;
    *(uint32_t*)((int)thisPtr + 0x19c) = 0;
    *(uint32_t*)((int)thisPtr + 0x1a0) = 0;
    *(uint32_t*)((int)thisPtr + 0x1a4) = 0;
    *(uint32_t*)((int)thisPtr + 0x1a8) = 0;
    *(uint32_t*)((int)thisPtr + 0x1ac) = vecVal;

    // Initialize state-related fields
    *(uint32_t*)((int)thisPtr + 0x138) = 0;
    *(uint32_t*)((int)thisPtr + 0x148) = 0;
    *(uint32_t*)((int)thisPtr + 0x144) = 0;
    *(uint32_t*)((int)thisPtr + 0x13c) = 0;
    *(uint32_t*)((int)thisPtr + 0x140) = 0;
    *(uint32_t*)((int)thisPtr + 0x154) = 0;
    *(uint32_t*)((int)thisPtr + 0x150) = 0;
    *(uint32_t*)((int)thisPtr + 0x14c) = 0;

    int someValue = *(int*)(DAT_0112a66c + 8);
    *(int*)((int)thisPtr + 0x148) = someValue;
    *(int*)((int)thisPtr + 0x144) = someValue;
    *(int*)((int)thisPtr + 0x13c) = someValue;
    *(int*)((int)thisPtr + 0x140) = someValue;

    if (someValue == 0) {
        int* ptr = *(int**)(DAT_0112a66c + 0x10);
        if (ptr != nullptr) {
            *(int*)((int)thisPtr + 0x140) = *(int*)(*(int*)ptr + 0x50);
        }
    }

    int globalConfig = DAT_012233ac;
    *(uint32_t*)((int)thisPtr + 0x74) = *(uint32_t*)(globalConfig + 0x68);
    *(uint32_t*)((int)thisPtr + 0x78) = *(uint32_t*)(globalConfig + 0x6c);

    void* callbackList = (void*)((int)thisPtr + 0x14);
    if (*(int*)((int)thisPtr + 0x90) == 0 || *(int*)((int)thisPtr + 0x148) == *(int*)((int)thisPtr + 0x90)) {
        // First set of state callbacks
        registerStateCallback(callbackList, &stateEntryA, 0); // LAB_00979a80
        registerStateCallback(callbackList, &stateUpdateA, 0); // LAB_009775f0
        registerStateCallback(callbackList, &stateExitA, 0);   // LAB_00978dc0
        registerStateCallback(callbackList, &stateEventA, 0); // LAB_0097ab70
        registerStateCallback(callbackList, stateUpdateB, 0);  // FUN_00977610
        void** nextCallback = &stateEntryB; // LAB_00976780
    } else {
        if (*(int*)((int)thisPtr + 0x158) != 1) {
            *(int*)((int)thisPtr + 0x158) = 1;
            registerStateCallback(callbackList, &stateEntryC, 0); // LAB_00978e00
        }
        *(int*)((int)thisPtr + 0x144) = *(int*)((int)thisPtr + 0x90);
        registerStateCallback(callbackList, &stateEntryA, 0);
        registerStateCallback(callbackList, &stateUpdateA, 0);
        registerStateCallback(callbackList, &stateExitA, 0);
        registerStateCallback(callbackList, &stateEventA, 0);
        void** nextCallback = stateUpdateB; // FUN_00977610
    }
    registerStateCallback(callbackList, nextCallback, 0);

    float randomVal = getRandomFloat(); // FUN_0040c390
    if (DAT_00e44598 < randomVal) {
        int* somePtr = **(int***)(DAT_012233a0 + 4);
        if (somePtr != nullptr && somePtr != (int*)0x1f30) {
            if ((*(byte*)((int)somePtr - 0x164a) & 1) != 0) {
                *(uint32_t*)((int)thisPtr + 0x60) |= 0x80; // Set flag bit 7
                int props = DAT_01223394;
                if (*(char*)(props + 0x24) != '\0') {
                    *(int*)(props + 0x40) = 0;
                    *(uint32_t*)(props + 0x2c) = _DAT_00d5780c;
                    *(int*)(props + 0x28) = 1;
                    *(char*)(props + 0x25) = 0;
                }
            }
        }
    }

    registerStateCallback(callbackList, &stateCleanup, 0); // LAB_00977650
    return;
}