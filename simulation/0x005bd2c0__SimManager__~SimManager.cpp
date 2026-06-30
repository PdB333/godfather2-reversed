// FUNC_NAME: SimManager::~SimManager

void __fastcall SimManager::~SimManager(SimManager* this)
{
    // Set initial vtable pointers (constructor-like but for destruction override)
    this->vtablePtr = &gSimManagerVtable;                    // +0x00: vtable
    this->field0x0C = &gSubManagerVtable1;                   // +0x0C: sub-manager vtable
    this->field0x10 = &gSubManagerVtable2;                   // +0x10: another sub-manager vtable

    unsigned int index = 0;
    if (gManagerListCount != 0) {
        int** listIterator = (int**)(gManagerList + 4);      // skip first? (maybe array of pairs)
        do {
            if (*listIterator == &this->field0x0C) {
                // Remove from global manager list (unregister)
                FUN_004f1530(&this->field0x0C);
                break;
            }
            index++;
            listIterator += 2;
        } while (index < gManagerListCount);
    }

    int ptrFirst = gFirstSubManager;                         // +0x??: some global pointer
    if (gFirstSubManager != 0) {
        FUN_005cf1e0(&gFirstSubManager);                    // likely cleanup of that sub-manager
        char result = FUN_005c43d0(ptrFirst);               // check if sub-manager is valid?
        if (result == '\0') {
            // Call virtual function at offset 4 of sub-manager's vtable (destructor?)
            (*(code**)(*(int*)gFirstSubManager + 4))(ptrFirst, 0);
        }
    }
    gFirstSubManager = 0;

    // Release two string/object resources
    FUN_004086d0(&gResourceA);                               // releases wchar_t string or object
    FUN_004086d0(&gResourceB);

    // Destroy another sub-object
    FUN_005bd6b0(this);                                      // likely sub-destructor

    // Destroy sub-object at offset 0x14 (this[5])
    FUN_00408310(&this->field0x14);

    // Unregister callback with function pointer
    FUN_00607d50(0, &handleCallbackFunc);

    // Some cleanup of input/system
    FUN_0059e100();

    // Decrement reference counts on two global objects (if present)
    if (gGlobalObjA != nullptr) {
        (*(code**)*gGlobalObjA)(1);                          // release ref
    }
    if (gGlobalObjB != nullptr) {
        (*(code**)*gGlobalObjB)(1);                          // release ref
    }

    int ptrSecond = gSecondSubManager;                       // another global subsystem pointer
    // Reset some global flags
    _GlobalFlag1 = 0;
    _GlobalFlag2 = 0;
    _GlobalFlag3 = 0;
    _GlobalFlag4 = 0;
    _GlobalFlag5 = 0;
    _GlobalFlag6 = 0;
    _GlobalFlag7 = 0;
    gSomeGlobal = 0;

    if (gSecondSubManager != 0) {
        FUN_005c37c0(&gSecondSubManager);                   // cleanup of second sub-manager
        char result2 = FUN_005c43d0(ptrSecond);
        if (result2 == '\0') {
            // Call virtual function at offset 4 of second sub-manager's vtable
            (*(code**)(*(int*)gSecondSubManager + 4))(ptrSecond, 0);
        }
    }
    gSecondSubManager = 0;

    // Decrement reference count on global object C
    if (gGlobalObjC != nullptr) {
        (*(code**)*gGlobalObjC)(1);
    }

    // Append data to a dynamic list (push operation)
    int dataValue = gSomeDataValue;                          // DAT_011260b4
    int* appendPtr = (int*)(gListBase + 0x14);               // +0x14: dynamic array pointer
    **(int**)(gListBase + 0x14) = &gListEndLabel;            // write end marker
    *appendPtr = *appendPtr + 4;                             // advance pointer
    *(int*)*appendPtr = dataValue;                           // store data value
    *appendPtr = *appendPtr + 4;                             // advance again

    // Release sub-object at offset 0x38 (this[0xe])
    if (this->field0x38 != 0) {
        FUN_009c8f10(this->field0x38);
    }

    // Change vtable to another one (final destruction stage)
    this->field0x10 = &gFinalVtablePtr;

    gGlobalSingleton = 0;                                    // DAT_012234f0

    // Final cleanup
    FUN_004083d0();
}