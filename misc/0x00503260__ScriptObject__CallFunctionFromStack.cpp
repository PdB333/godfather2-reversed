// FUNC_NAME: ScriptObject::CallFunctionFromStack
// Address: 0x00503260
// Reads arguments from an internal stack and calls a function pointer.
// Offsets:
//   +0x18: stack pointer (char*)

class ScriptObject {
public:
    void CallFunctionFromStack(void** funcPtrTable) {
        // Read first 32-bit value from current stack pointer
        uint32_t firstArg = **(uint32_t**)((uint8_t*)this + 0x18);

        // Align stack pointer to next 4-byte boundary
        uint8_t* alignedPtr = (uint8_t*)(((uint32_t)*(uint32_t**)((uint8_t*)this + 0x18) + 7) & ~3);
        *(uint8_t**)((uint8_t*)this + 0x18) = alignedPtr;

        // Read two 64-bit values
        uint64_t arg2 = *(uint64_t*)alignedPtr;
        uint64_t arg3 = *(uint64_t*)(alignedPtr + 8);
        *(uint8_t**)((uint8_t*)this + 0x18) = alignedPtr + 16;

        // Read third 64-bit value
        uint64_t arg4 = *(uint64_t*)(alignedPtr + 16);
        *(uint8_t**)((uint8_t*)this + 0x18) = alignedPtr + 24;

        // Split last value into two 32-bit arguments
        uint32_t arg4_low  = (uint32_t)arg4;
        uint32_t arg4_high = (uint32_t)(arg4 >> 32);

        // Call the target function
        typedef void (*TargetFunc)(uint32_t, uint64_t, uint64_t, uint32_t, uint32_t);
        TargetFunc func = (TargetFunc)(*funcPtrTable);
        func(firstArg, arg2, arg3, arg4_low, arg4_high);
    }
};