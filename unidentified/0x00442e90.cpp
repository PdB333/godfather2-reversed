// FUN_00442e90: ScriptObject::invokeMethod (script method dispatcher through indexed table)
int __thiscall ScriptObject::invokeMethod(void* pMethodToken) {
    // Copy the method token (the ID/name) to a local variable for resolution
    int methodToken = *(int*)pMethodToken;

    // Look up the method index via external resolver
    // FUN_00443b40: ResolveMethodIndex (takes pointer to 4-byte token, returns index >=0 on success)
    int methodIndex = ResolveMethodIndex(&methodToken);

    if (methodIndex >= 0) {
        // +0x58: pointer to method table (array of 8-byte entries: {int padding, void* func})
        uint8_t* tableBase = *(uint8_t**)(this + 0x58);
        // Each entry: offset 0 = int (unused?), offset 4 = function pointer
        // Address of function pointer for methodIndex: tableBase + 4 + methodIndex * 8
        void** funcPtrPtr = (void**)(tableBase + 4 + methodIndex * 8);
        if (funcPtrPtr != nullptr) {
            // Call the member function with 'this' still in ECX (implicit __thiscall)
            // The function pointer is stored as a raw address
            using MethodFunc = int (__thiscall*)(ScriptObject*);
            return ((MethodFunc)(*funcPtrPtr))(this);
        }
    }
    return 0;
}