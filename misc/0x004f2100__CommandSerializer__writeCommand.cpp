// FUNC_NAME: CommandSerializer::writeCommand

// Reconstructed C++ for function at 0x004f2100
// This function serializes a command packet by writing a set of parameters into a buffer,
// using aligned writes (4-byte alignment with padding to next boundary after each write).
// The class has a write pointer at offset +0x14.

class CommandSerializer {
public:
    // Offset +0x14: current write pointer (mutable pointer into a buffer)
    // The buffer is managed externally; this method advances the pointer.
    void __thiscall writeCommand(void* param_2, void* param_3, void* param_4,
                                void* param_5, void* param_6, void* param_7) {
        int* base = reinterpret_cast<int*>(this); // this is assumed to be int* for offset access
        int* writePtrPtr = reinterpret_cast<int*>(base + 0x14); // +0x14: pointer to write cursor
        int writePtr = *writePtrPtr;

        // Store a function pointer (global vtable/dispatch)
        *reinterpret_cast<void**>(writePtr) = reinterpret_cast<void*>(&PTR_FUN_01124d8c); // global
        writePtr += 4;
        *writePtrPtr = writePtr;

        // Re-fetch base (unnecessary but preserved from binary)
        base = reinterpret_cast<int*>(this);
        writePtr = *reinterpret_cast<int*>(base + 0x14);
        *reinterpret_cast<void**>(writePtr) = param_2; // store param_2
        // Align to next 4-byte boundary (with padding of at least 7)
        writePtr = (writePtr + 7) & ~3;
        *reinterpret_cast<void**>(writePtr) = param_3; // store param_3
        writePtr = (writePtr + 7) & ~3;
        *reinterpret_cast<void**>(writePtr) = param_4; // store param_4

        // Align and store 8-byte combined value (param_6 as low word, param_7 as high)
        writePtr = (writePtr + 7) & ~3;
        *reinterpret_cast<uint64_t*>(writePtr) = (static_cast<uint64_t>(reinterpret_cast<uint32_t>(param_7)) << 32) |
                                                   static_cast<uint32_t>(reinterpret_cast<uint32_t>(param_6));
        writePtr += 8;

        // Store param_5 and advance by 4 (no alignment before this store)
        *reinterpret_cast<void**>(writePtr) = param_5;
        writePtr += 4;
        *writePtrPtr = writePtr; // update the write cursor
    }
};