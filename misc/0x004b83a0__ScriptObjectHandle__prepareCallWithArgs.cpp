// FUNC_NAME: ScriptObjectHandle::prepareCallWithArgs

// Reconstructed function at 0x004b83a0
// Writes a fixed function pointer and three arguments into a command buffer,
// advancing the buffer write pointer.
// The class uses a handle pattern: 'this' is a pointer to a pointer to the actual ScriptObject.

void __thiscall ScriptObjectHandle::prepareCallWithArgs(void* arg1, void* arg2, void* arg3)
{
    // Dereference handle to get the actual object (ScriptObject*)
    ScriptObject* obj = *reinterpret_cast<ScriptObject**>(this);

    // Write the fixed function pointer (likely a vtable entry or command ID) at the current write position
    // Offset +0x14: writePtr (uint32_t*) - pointer to next write location in command buffer
    *reinterpret_cast<void**>(obj->writePtr) = reinterpret_cast<void*>(0x011246cc);
    obj->writePtr++; // advance by 4 bytes

    // Write the first argument
    *reinterpret_cast<void**>(obj->writePtr) = arg1;
    obj->writePtr++; // advance

    // Write the second argument
    *reinterpret_cast<void**>(obj->writePtr) = arg2;
    obj->writePtr++; // advance

    // Write the third argument
    *reinterpret_cast<void**>(obj->writePtr) = arg3;
    obj->writePtr++; // advance
}

// Supporting definitions (assumed from offsets):
// struct ScriptObject {
//     // ... (other members) ...
//     uint32_t* writePtr; // offset 0x14
// };