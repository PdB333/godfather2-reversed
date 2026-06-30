// FUNC_NAME: CommandDispatcher::dispatchCommand
// Address: 0x0049a560
// Role: Dispatches a command based on a byte index extracted from the high byte of param4.
//       Looks up in a table of handlers and associated data; calls the handler with (source, extra1, extra2, data, this).
//       The table arrays are stored as byte arrays; each entry occupies 2 bytes (probably because the original data is
//       stored as 2-byte relative offsets or indices, but reinterpreted as a 4-byte function pointer and data pointer).
//       The exact layout is unclear from decompilation, but we follow the pointer arithmetic shown.

// Note: The function subtracts 1 from the high byte with signed wrap, so command byte 0 becomes index 0xFF.
// If the index is >= g_handlerCount, no dispatch occurs.

extern int g_handlerCount;               // DAT_01217d80: number of entries in the handler table
extern uint8_t g_handlerFuncTable[];     // DAT_01217d84: table of function pointers (each 4 bytes stored at offset index*2)
extern uint8_t g_handlerDataTable[];     // DAT_01217d88: table of associated data (each 4 bytes stored at offset index*2)

class CommandDispatcher {
public:
    // __thiscall: this is implicit
    int dispatchCommand(void* source, void* /*unused*/, uint32_t commandData, void* extraArg1, void* extraArg2);
};

int CommandDispatcher::dispatchCommand(void* source, void* /*unused*/, uint32_t commandData, void* extraArg1, void* extraArg2) {
    // Extract the high byte of commandData (e.g., request/opcode)
    uint8_t highByte = (commandData >> 8) & 0xFF;

    // Subtract 1 with signed char wrapping (allows skipping a reserved command, e.g., 0xFF for invalid)
    int8_t signedVal = (int8_t)highByte - 1;
    uint8_t indexByte = (uint8_t)signedVal; // wraps if signedVal negative
    int32_t index = (int32_t)indexByte;

    // Check bounds
    if (index < g_handlerCount) {
        // Recover function pointer from byte table (each entry at index*2 offset)
        // The table is stored as bytes, so we read a 4-byte function pointer starting there.
        typedef void (__thiscall *HandlerFunc)(void*, void*, void*, void*, void*); // (source, extra1, extra2, data, this)
        HandlerFunc func = *(HandlerFunc*)(g_handlerFuncTable + index * 2);

        // Recover associated data from the parallel table
        void* data = *(void**)(g_handlerDataTable + index * 2);

        // Call the handler: pass source, extra args, data, and this as last argument
        func(source, extraArg1, extraArg2, data, this);
        return 1;
    }
    return 0;
}