// FUNC_NAME: ToBasePtr (global helper function: converts string or Base to pointer)
int __cdecl ToBasePtr(void* input)
{
    char cVar1;
    int* intPtr;
    int objPtr;
    int foundObj;
    // GUID structure (16 bytes) with magic values used as default/error indicator
    struct {
        int a; // 0xbadbadba
        int b; // 0xbeefbeef
        int c; // 0xeac15a55
        int d; // 0x91100911
    } guidStruct;

    // Try to resolve input as a string/object pointer using the global table (DAT_00e326c8)
    intPtr = (int*)resolveStringOrObject(input, &DAT_00e326c8);
    if (intPtr != (int*)0x0)
        goto LAB_0046ba53;

    // If that fails, try to get the current object context (likely a string name from a context)
    objPtr = getCurrentObjectContext(); // FUN_00625a70
    if (objPtr == 0) {
        // No context, try to initialize/reset it
        resetObjectContext(); // FUN_006281d0
        objPtr = getCurrentObjectContext(); // FUN_00625a70
        if (objPtr != 0)
            goto LAB_0046b9dc;
    }
    else {
LAB_0046b9dc:
        // If we have a string context, try to parse it as a GUID
        guidStruct.a = 0xbadbadba;
        guidStruct.b = 0xbeefbeef;
        guidStruct.c = 0xeac15a55;
        guidStruct.d = 0x91100911;

        cVar1 = parseStringToGuid(&guidStruct); // FUN_0046b4d0
        if (cVar1 != '\0') {
            // Found a valid GUID, now resolve it to a pointer
            foundObj = resolveGuidToObject(&guidStruct, 0); // FUN_00445ff0
            objPtr = 0;
            if ((foundObj != 0) && ((*(uint*)(foundObj + 0x14) & 0x8000000) != 0)) {
                objPtr = foundObj;
            }
            return objPtr;
        }
        // GUID parsing failed
        logError("ToBasePtr: Could not turn '%s' into a GUID.\n", objPtr);
    }

    // If input is a pointer to a valid object, return its base pointer
    intPtr = (int*)logError("ToBasePtr: 1st argument should be a string or Base.\n"); // note: this also may set intPtr
LAB_0046ba53:
    if (*intPtr != 0) {
        return *intPtr - 0x48; // offset for base pointer (likely 0x48 = sizeof some header)
    }
    return 0;
}