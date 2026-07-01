// FUNC_NAME: GameObject::updateStateAndNotify

void __thiscall GameObject::updateStateAndNotify(GameObject* thisPtr, void* context)
{
    // Copy the 12-byte state from local buffer at +0x8c to output buffer at +0x98
    // The data layout: a 64-bit value (likely two ints or a double) and a 32-bit value
    *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(thisPtr) + 0x98) =
        *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(thisPtr) + 0x8c);
    *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(thisPtr) + 0xa0) =
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(thisPtr) + 0x94);

    // Initialize / reset the local state buffer at +0x8c
    void* stateBuffer = reinterpret_cast<char*>(thisPtr) + 0x8c;
    FUN_00819200(stateBuffer);  // likely initSubObject() or resetSubObject()

    // Get the callback table from the context structure
    // context->+0x18 points to a sub-structure that holds a function pointer at +0xc
    void* contextTable = *reinterpret_cast<void**>(reinterpret_cast<char*>(context) + 0x18);
    if (contextTable != nullptr)
    {
        // Extract the callback function pointer
        typedef void (*CallbackFunc)(void* derivedThis, void* stateBuffer);
        CallbackFunc callback = *reinterpret_cast<CallbackFunc*>(reinterpret_cast<char*>(contextTable) + 0xc);

        // Determine the derived class 'this' pointer from context->+0x8
        // If context->+0x8 is non-null, adjust it by subtracting 0x48 to get the base of the derived object
        char* derivedThis = *reinterpret_cast<char**>(reinterpret_cast<char*>(context) + 8);
        if (derivedThis != nullptr)
        {
            callback(derivedThis - 0x48, stateBuffer);
        }
        else
        {
            callback(nullptr, stateBuffer);
        }
    }
}