// FUNC_NAME: EARSObject::vtableDispatch
int EARSObject::vtableDispatch(int operationId) {
    // Get the global vtable/interface object (likely a singleton)
    int* vtablePtr = (int*)getVtableObject();

    // If operationId is 0, call the default handler (offset 0x04 in vtable)
    if (operationId == 0) {
        // Call via vtable entry +4: default operation
        ((void (__thiscall*)(EARSObject*))(*vtablePtr + 4))(this);
        return 0;
    }

    // Otherwise, call the parameterized handler (offset 0x18) with a zero flag
    int result = ((int (__thiscall*)(EARSObject*, int, int))(*vtablePtr + 0x18))(this, operationId, 0);
    return result;
}