// FUNC_NAME: ScriptContext::resolveVariable
// Address: 0x00633500
// Role: Resolves a variable by ID into a typed pointer (local, global, field, method).
// Uses a metadata structure accessed via the object’s vtable to locate the variable table.
// Returns a string literal indicating the variable's storage type, or NULL on failure.

char* __thiscall ScriptContext::resolveVariable(uint variableId, int* outValue) {
    byte flagByte; // low byte of flags at +0x08
    int localVarTable; // from class metadata
    int localIndex;
    int result;

    flagByte = *(byte*)(this + 2); // flagByte = *(byte*)((int*)this + 2) = low byte of flags

    while ((flagByte & 1) == 0) {
        // Access class metadata: vtable at *this, then subtract 4 to get class descriptor, then 0xC for local var table
        localVarTable = *(int*)(*(int*)(*this - 4) + 0xC); // +0xC is some table pointer

        if ((this[2] & 1U) == 0) { // same as flagByte & 1? but using the full int
            if ((this[2] & 2U) != 0) {
                this[3] = *(int*)this[4]; // copy stack pointer? +0x10 -> +0x0C
            }
            // compute local index: (current frame pointer - base of local var table) / 4 - 1
            localIndex = ((this[3] - *(int*)(*(int*)(*(int*)(*this - 4) + 0xC) + 0xC)) >> 2) - 1;
        } else {
            localIndex = -1;
        }

        result = FUN_006384a0(variableId + 1); // some allocation/check function
        *outValue = result;
        if (result != 0) {
            return "local";
        }

        uint packedResult = FUN_00633100(localVarTable, localIndex, variableId); // look up variable
        switch(packedResult & 0x3F) {
        case 0: {
            // scope chain – move to next scope
            uint newVarId = (packedResult >> 0xF) & 0x1FF;
            if ((packedResult >> 0x18) <= newVarId) {
                return (char*)0; // out of scope
            }
            variableId = newVarId;
            flagByte = *(byte*)(this + 2); // refresh flag byte
            break; // continue loop
        }
        default:
            goto switchDefault; // return NULL
        case 5: {
            // global variable
            int globalTable = *(int*)(localVarTable + 8); // +8: global table base
            int index = (packedResult >> 6) & 0x3FFFF;
            *outValue = *(int*)(globalTable + 4 + index * 8) + 0x10;
            return "global";
        }
        case 6: {
            // field access
            *outValue = FUN_006334e0(); // resolve field address
            return "field";
        }
        case 0xB: {
            // method access
            *outValue = FUN_006334e0(); // resolve method address
            return "method";
        }
        }
    }

switchDefault:
    return (char*)0;
}