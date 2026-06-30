// FUNC_NAME: Apt::Runtime::createOrGetObject
// Function address: 0x0059fb30
// Role: Creates or retrieves an Apt display object, ensures correct type, returns a property, and calls a virtual constructor method.

void Apt::Runtime::createOrGetObject(uint param_1, uint *outResult)
{
    int *pDebugger;
    uint result;
    uint *pObject;
    uint *pAllocation;
    uint propVal;

    // Check if Apt is already initialized
    if (g_aptInitialized != 0) goto L_MAIN_BODY;

    // Assertion details (from debug build)
    const char *assertMessage = "bAptIsInitialized";
    const char *assertFile = "..\\source\\Apt\\Apt.cpp";
    int assertLine = 0x2cd; // 717
    int assertLevel = 2;
    char *assertFlag = &g_aptDebugFlag; // DAT_01128f53

    if (*assertFlag == 0) goto L_MAIN_BODY; // Skipped if diagnostic flag disabled

    // Retrieve debugger/assert handler
    pDebugger = *(int**)(**(int**)(__readfsdword(0x2c)) + 0x30);
    result = 1;
    if (pDebugger == nullptr) {
L_DEBUG_CHECK:
        if ((result & 2) != 0) {
            *assertFlag = 0;
        }
    } else {
        result = pDebugger->vtable->checkAssert(&assertMessage, "bAptIsInitialized");
        if (assertFlag != nullptr) goto L_DEBUG_CHECK;
    }
    // If assertion fails, trigger debug break
    if ((pDebugger != nullptr) || (assertLevel != 4)) {
        if ((result & 1) || (assertLevel == 0) || (assertLevel == 1)) {
            ((void(*)(void))software_breakpoint(3))();
            return;
        }
    }

L_MAIN_BODY:
    // Allocate and create the object
    pAllocation = (uint*)aptAllocObject(0, param_1, 1, 1); // FUN_0059e2f0
    pObject = (uint*)aptGetObject(pAllocation, 0, param_1, 1, 1); // FUN_005aea60

    // If the object differs from the global singleton, check type compatibility
    if (pObject != g_aptSingletonPtr) {
        uint type = *pObject & 0x7fff;
        if (type != 0x19) { // Not the expected primary type?
            uint highBit = (*pObject >> 0xf) & 1;
            if ((highBit == 0) || ((type != 0xb) && (type != 0x18) && (type != 0x17))) {
                // Destroy this incompatible object
                aptDestroyObject(pObject); // FUN_0059c230
            }
        }
    }

    // Get the property value to return
    propVal = aptGetPropertyValue(); // FUN_005a8fe0
    *outResult = propVal;

    // Call virtual finalizer/constructor via vtable dispatch
    uint vtableIndex = *pObject & 0x7fff;
    ((void(*)(uint*))aptVtableArray[vtableIndex])(pObject); // Call through jump table
    return;
}