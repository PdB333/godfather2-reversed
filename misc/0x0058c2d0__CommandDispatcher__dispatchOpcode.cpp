// FUNC_NAME: CommandDispatcher::dispatchOpcode
// Address: 0x0058c2d0
// Dispatches an opcode from a command buffer, applying scale factors to the result if not suppressed.

struct CommandHeader {
    char unknown1;          // +0x00
    char count;             // +0x01 (must be >= 1 to proceed)
    float scaleFactors[3];  // +0x04 (scale for x, y, z)
    byte* opcodePtr;        // +0x0c (pointer to opcode byte)
};

// Global jump table for opcode handlers (0x0103afc0)
// Each entry is a function pointer taking (void* context, byte* data, ...)
extern void* g_opcodeHandlers[64]; // only low 6 bits used

class CommandDispatcher {
public:
    // Returns a pointer to a created object, or 0 on failure.
    int dispatchOpcode(CommandHeader* cmd, int param3, int param4, int param5, uint flags, int param7) {
        if (cmd->count < 1) {
            return 0;
        }

        byte opcode = *cmd->opcodePtr;
        byte index = opcode & 0x3F; // low 6 bits

        if (index < 0x23) { // max valid index? (0x23 = 35)
            // Call the handler for this opcode
            typedef int (*OpcodeHandler)(void*, byte*, int, int, int, uint, int);
            OpcodeHandler handler = (OpcodeHandler)g_opcodeHandlers[index];
            int result = handler(this, cmd->opcodePtr, param3, param4, param5, flags, param7);

            if (result != 0) {
                // Apply scale factors if not suppressed (bit 3 of flags)
                if ((flags & 8) == 0) {
                    float* obj = (float*)result;
                    obj[8]  *= cmd->scaleFactors[0]; // offset 0x20 = x
                    obj[9]  *= cmd->scaleFactors[1]; // offset 0x24 = y
                    obj[10] *= cmd->scaleFactors[2]; // offset 0x28 = z
                }
                return result;
            }
        }
        return 0;
    }
};