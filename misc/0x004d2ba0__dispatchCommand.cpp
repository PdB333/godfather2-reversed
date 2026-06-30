// FUNC_NAME: dispatchCommand
// Address: 0x004d2ba0
// Role: Dispatches command handling based on command ID (opcodes 1-8)
// ecx @contextPtr: game context or manager object
// edx @arg1: secondary argument (likely a packet or data buffer)
// stack @defaultReturn: return value used if no command handled
// stack @commandId: command opcode to dispatch
// stack @dataPtr: additional data (e.g., length or pointer)

// Forward declarations of command handler functions (addresses from callees)
uint32_t __fastcall handleCommand1(void* arg1, void* contextPtr);      // 0x004d2cb0
uint32_t __fastcall handleCommand2(void* arg1, void* contextPtr, void* dataPtr); // 0x004d2e10
uint32_t __fastcall handleCommand3(void* arg1, void* contextPtr, void* dataPtr); // 0x004d2f70
uint32_t __fastcall handleCommand4(void* arg1, void* contextPtr, void* dataPtr); // 0x004d30e0
uint32_t __fastcall handleCommand5(void* arg1, void* contextPtr, void* dataPtr); // 0x004d3250
uint32_t __fastcall handleCommand6(void* arg1, void* contextPtr, void* dataPtr); // 0x004d33d0
uint32_t __fastcall handleCommand7(void* arg1, void* contextPtr, void* dataPtr); // 0x004d3560
uint32_t __fastcall handleCommand8(void* arg1, void* contextPtr, void* dataPtr); // 0x004d36f0

uint32_t __fastcall dispatchCommand(void* contextPtr, void* arg1, uint32_t defaultReturn, int32_t commandId, void* dataPtr)
{
    if (dataPtr != nullptr && commandId != 0) {
        switch (commandId) {
        case 1:
            return handleCommand1(arg1, contextPtr);
        case 2:
            return handleCommand2(arg1, contextPtr, dataPtr);
        case 3:
            return handleCommand3(arg1, contextPtr, dataPtr);
        case 4:
            return handleCommand4(arg1, contextPtr, dataPtr);
        case 5:
            return handleCommand5(arg1, contextPtr, dataPtr);
        case 6:
            return handleCommand6(arg1, contextPtr, dataPtr);
        case 7:
            return handleCommand7(arg1, contextPtr, dataPtr);
        case 8:
            return handleCommand8(arg1, contextPtr, dataPtr);
        }
    }
    return defaultReturn;
}