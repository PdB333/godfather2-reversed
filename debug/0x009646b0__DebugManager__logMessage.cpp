// FUNC_NAME: DebugManager::logMessage
// Function address: 0x009646b0
// Reconstructed from Ghidra decompilation: writes a timestamped log message to a debug stream

// Global debug manager singleton (gDebugManager at 0x01223484)
// +0x0C: enabled flag (int32)

// Assumed class hierarchy:
// DebugManager (vtable at +0x00)
//   +0x34: getDebugOutput() -> DebugOutput*
// DebugOutput
//   +0x24: getFormatter() -> DebugFormatter*
// DebugFormatter
//   +0x18: getStream(uint32 channel) -> DebugStream*
// DebugStream
//   +0x2C: write(uint8* buffer, uint32 length, uint32 flags)

// Forward declarations
class DebugManager;
class DebugOutput;
class DebugFormatter;
class DebugStream;

// External functions (names guessed from usage)
extern DebugManager* gDebugManager;                       // 0x01223484
void DebugBuffer_Init(uint8_t* buffer);                   // 0x008a3680
uint32_t GetTimestamp(void);                              // 0x008b5c10
void AppendTimestampToBuffer(uint32_t timestamp);         // 0x00b21d90
void FinalizeBuffer(uint8_t* buffer);                     // 0x00b21ed0
void DebugOutputFlush(void);                              // 0x00b19550
DebugManager* DebugManager_getInstance(void);             // 0x00ad8d40

// __cdecl global function
void FUN_009646b0(uint32_t param_1) {
    // Check if debug manager exists and logging is enabled
    if ((gDebugManager != nullptr) &&
        (*(int32_t*)((uint8_t*)gDebugManager + 0x0C) != 0)) {
        DebugManager* mgr = DebugManager_getInstance();
        if (mgr != nullptr) {
            DebugOutput* output = mgr->getDebugOutput();   // vtable+0x34
            if (output != nullptr) {
                DebugFormatter* formatter = output->getFormatter(); // vtable+0x24
                if (formatter != nullptr) {
                    DebugStream* stream = formatter->getStream(param_1); // vtable+0x18
                    if (stream != nullptr) {
                        uint8_t buffer[1064];               // stack buffer for formatting
                        DebugBuffer_Init(buffer);
                        uint32_t timestamp = GetTimestamp();
                        AppendTimestampToBuffer(timestamp);
                        FinalizeBuffer(buffer);
                        stream->write(buffer, 1, 0);         // vtable+0x2C
                        DebugOutputFlush();
                    }
                }
            }
        }
    }
}