// Xbox PDB: EARS_Modules_Sentient_InitializeAttackCollision
// FUNC_NAME: Animated::setupBoneAttachments
void __fastcall Animated::setupBoneAttachments(Animated* thisPtr)
{
    void* tlsData; // from TlsGetValue
    int unknownAlloc; // from FUN_00aa2680
    void* allocator; // from FUN_00a64b00
    int boneHash; // from FUN_0043b490
    ModelHandle modelHandle; // from FUN_00540bc0
    int boneArrayId; // from FUN_00540cc0
    bool validFlag;
    char* boneName;
    int i;

    // Get thread-local storage (likely for class registry)
    tlsData = TlsGetValue(DAT_01139810); // DAT_01139810 is TLS index

    // Allocate some structure (maybe an array of bone IDs?)
    unknownAlloc = FUN_00aa2680(); // returns pointer to some buffer
    *(short*)(unknownAlloc + 4) = 0x20; // set size to 32

    // Get allocator from TLS?
    allocator = FUN_00a64b00();

    // Zero out 10 dwords on stack (maybe for root bone transform)
    int rootMatrix[10] = {0}; // uStack_28..uStack_4

    // Virtual call at vtable+0x94: first call with rootMatrix (maybe to get root bone ID)
    (thisPtr->vtable[0x94 / 4])(rootMatrix);

    // Now call the same virtual for named bones, passing a buffer for each bone's transform
    // The buffer addresses are stored in apcStack_70[4], [2], [0], etc.
    // But the decompiled shows separate calls with different arguments.
    // We'll reconstruct based on the pattern: each call takes a string and a buffer.
    // The strings: "r_wrist", "l_ankle", "r_ankle", "l_knee", "r_knee", "eye_R", "l_elbow", "r_elbow"
    char* boneNames[10] = {"r_wrist", "l_ankle", "r_ankle", "l_knee", "r_knee", "eye_R", "l_elbow", "r_elbow"};
    // The buffers on stack: auStack_2c, auStack_30, acStack_34, auStack_38, auStack_3c, auStack_40, stack0xffffffbc, stack0xffffffb8
    // We'll assume they are local arrays (but stack offsets tricky)
    int boneTransforms[8][4]; // dummy representation

    // Actually the decompiled shows calls: 
    // first: (**(code **)(*thisPtr + 0x94))(auStack_2c, "r_wrist")
    // second: (**(code **)(*thisPtr + 0x94))(auStack_30, "l_ankle")
    // etc.
    // We'll just loop conceptually
    // For simplicity, we note that the loop later uses apcStack_70 as an array of 10 elements,
    // but only 8 bones are explicitly retrieved? The first call with rootMatrix might be the 9th?
    // The loop iVar5 from 0 to 9 uses apcStack_70[iVar5] to get a string pointer.
    // The strings are set in apcStack_70[3]="r_wrist", [2]="l_ankle", [1]="r_ankle", [0]="l_knee"? Notably, the array indexing is reused.

    // Actually, apcStack_70 is repurposed. We'll piece it together.

    // After the root matrix call, the code sets apcStack_70[5] = "r_wrist", apcStack_70[4] = auStack_2c
    // then calls virtual: (**(code **)(*thisPtr + 0x94))(); // but with the args set on stack via previous assignments?
    // This is confusing. Given the decompiled is messy, we simplify by writing the intent:

    // We'll assume the following pattern: for each bone, call the virtual method that stores bone data into the given buffer.
    // The buffers are local variables, and the strings are the bone names.

    float unknownBuffer[10]; // stack buffers used
    (thisPtr->vtable[0x94 / 4])(unknownBuffer, "r_wrist");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 4, "l_ankle"); // approximate, since stack addresses are reused
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 8, "r_ankle");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 12, "l_knee");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 16, "r_knee");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 20, "eye_R");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 24, "l_elbow");
    (thisPtr->vtable[0x94 / 4])(unknownBuffer + 28, "r_elbow");

    // Get some bone hash or ID
    boneHash = FUN_0043b490();
    thisPtr->field_0x22d = boneHash; // stored at offset 0x22d (relative to thisPtr)

    // Load model resource (likely a .model file)
    modelHandle = FUN_00540bc0(0x74340, 0x7f0000, &thisPtr->field_0x22d, 1);
    *(uint64*)(thisPtr + 0x232) = modelHandle.low; // two 8-byte values
    *(uint64*)(thisPtr + 0x234) = modelHandle.high;
    *(int*)(thisPtr + 0x236) = modelHandle.extra; // maybe a 4-byte component

    // Get bone array ID from the model handle
    boneArrayId = FUN_00540cc0(thisPtr + 0x232);

    // Now set up 10 bone attachment slots (at offset 0x453, each 0x48 bytes)
    BoneSlot* slotBase = (BoneSlot*)(thisPtr + 0x453);
    for (i = 0; i < 10; i++) {
        // Check if bone name (from apcStack_70 array) is valid (aligned to 4)
        // The apcStack_70 array was actually filled with strings earlier
        // We'll assume it contains the 8 bone names plus possibly root
        validFlag = ((uint)boneNames[i] & 0xfffffffc) != 0;
        if (validFlag) {
            // Increase reference count? (puVar3 = allocator)
            FUN_00549cf0(allocator);
            // Store this pointer and bone name in the slot
            slotBase->object = thisPtr;
            slotBase->boneName = boneNames[i];
        }
        // Store bone array ID at slotBase[-0xc] (i.e., slotBase->baseId = boneArrayId)
        slotBase[-0xc].something = boneArrayId;
        slotBase += 0x48 / sizeof(int); // increment by 0x48 bytes (18 ints?)
    }

    // Reference counting cleanup (allocator)
    if (*(short*)((char*)allocator + 2) != 0) {
        *(short*)((char*)allocator + 6) -= 1;
        if (*(short*)((char*)allocator + 6) == 0) {
            (*(void (**)(int))(*(int*)allocator))(1); // call destructor? arg=1
        }
    }
}