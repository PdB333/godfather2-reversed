// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* thisPtr)
{
    int* ptr;
    int loopCount;
    int* arrayIter;
    void** debugStruct; // local_8
    void* debugNamePtr; // local_14
    void* someGlobal; // local_c
    int existingResource; // local_10
    char localPad; // local_4

    // Set vtable pointers – class has multiple bases/interfaces
    thisPtr->vtable0 = &PTR_FUN_00d5dca0;           // +0x00
    thisPtr->vtableF = &PTR_LAB_00d5dc90;           // +0x0F
    thisPtr->vtable12 = &PTR_LAB_00d5dc8c;          // +0x12
    thisPtr->vtable14 = &PTR_LAB_00d5dc88;          // +0x14
    thisPtr->vtable15 = &PTR_LAB_00d5dc28;          // +0x15
    thisPtr->vtable16 = &PTR_LAB_00d5dbc0;          // +0x16

    // Global class init (likely static initializer)
    globalInit_006b6eb0();

    // If previously allocated resources exist, free them before reinit
    if (thisPtr->field_0x60 != 0) {
        // Setup debug name for this instance
        debugStruct = &debugNamePtr;
        debugNamePtr = &PTR_LAB_00d5dbb0;          // +0x00 in debug struct
        someGlobal = DAT_0112a5b4;                  // global string table
        localPad = 0;
        existingResource = thisPtr->field_0x60;     // +0x60
        setupDebugName_00408a00(&someGlobal, 0);    // attach debug name
        resetResource_006b5b80(0);                  // free old resource
    }

    // Base class constructor
    baseClassConstructor_006b0890(thisPtr);

    // Register with global manager (type ID 0x14)
    registerWithManager_008f67c0(0x14, thisPtr);

    // Initialize many member sub-objects (simple types)
    initPrimitive_004086d0(&thisPtr->field_0x91);   // +0x244
    initPrimitive_004086d0(&thisPtr->field_0x93);   // +0x24C
    initPrimitive_004086d0(&thisPtr->field_0xab);   // +0x2AC
    initPrimitive_004086d0(&thisPtr->field_0x8f);   // +0x23C
    initPrimitive_004086d0(&thisPtr->field_0x97);   // +0x25C
    initPrimitive_004086d0(&thisPtr->field_0xa3);   // +0x28C
    initPrimitive_004086d0(&thisPtr->field_0xa5);   // +0x294

    // Initialize array-like members
    initPrimitiveArray_00408310(&thisPtr->field_0x77); // +0x1DC
    initPrimitiveArray_00408310(&thisPtr->field_0x91); // +0x244
    initPrimitiveArray_00408310(&thisPtr->field_0x93); // +0x24C
    initPrimitiveArray_00408310(&thisPtr->field_0x97); // +0x25C
    initPrimitiveArray_00408310(&thisPtr->field_0x95); // +0x254
    initPrimitiveArray_00408310(&thisPtr->field_0x9f); // +0x27C
    initPrimitiveArray_00408310(&thisPtr->field_0xa1); // +0x284
    initPrimitiveArray_00408310(&thisPtr->field_0x9d); // +0x274
    initPrimitiveArray_00408310(&thisPtr->field_0x9b); // +0x26C
    initPrimitiveArray_00408310(&thisPtr->field_0xab); // +0x2AC
    initPrimitiveArray_00408310(&thisPtr->field_0x8f); // +0x23C
    initPrimitiveArray_00408310(&thisPtr->field_0xa3); // +0x28C
    initPrimitiveArray_00408310(&thisPtr->field_0xa5); // +0x294
    initPrimitiveArray_00408310(&thisPtr->field_0xa7); // +0x29C
    initPrimitiveArray_00408310(&thisPtr->field_0xa9); // +0x2A4

    // Global static member init
    initPrimitiveArray_00408310(&DAT_0112a588);
    initPrimitive_004086d0(&DAT_0120e93c);

    // Another global init call
    globalCleanupPart_006b6d90();

    // Free an array of 4 pointers (offsets 0x73, 0x71, 0x6F, 0x6D)
    arrayIter = &thisPtr->field_0x75;               // +0x1D4
    loopCount = 4;
    do {
        ptr = arrayIter - 2;                         // move back 8 bytes
        arrayIter = arrayIter - 2;
        if (*ptr != 0) {
            freeMemory_004daf90(arrayIter);          // free pointer at this offset
        }
        loopCount = loopCount - 1;
    } while (-1 < loopCount);

    // Free additional resource if non-null (offset +0x66)
    if (thisPtr->field_0x66 != 0) {
        freeResource_009c8f10(thisPtr->field_0x66);  // +0x198
    }

    // Final global shutdown hook
    globalShutdown_0046ea20();
}