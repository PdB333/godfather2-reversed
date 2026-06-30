// FUNC_NAME: Logger::writeStructuredLog

class Logger {
public:
    // Non-zero indicates this instance has been registered in the global sink list.
    // +0x0c: registration flag
    char registered;

    // +0x04: Some identifier (source ID, log level, or function pointer)
    int sourceId;

    // +0x08: Additional context data (maybe timestamp or category)
    int contextData;

    // Offset 0x00: vtable pointer? Not used here.
};

// Global list of registered logger instances (head pointer stored at DAT_01206880+0x14)
// The structure is a linked list of ints? Actually in the init code it builds a vtable-like list.

void Logger::writeStructuredLog(
    Logger* this,
    int arg1,             // param_2: First numeric argument
    int arg2,             // param_3
    int arg3,             // param_4
    int arg4,             // param_5
    int arg5,             // param_6
    const char* format,   // param_7: Format string (may be null)
    int arg6,             // param_8
    int arg7,             // param_9
    byte extraByte,       // param_10: A single byte value
    int* data1,           // param_11: Optional pointer to 2 ints (set flag bit 1)
    int* data2,           // param_12: Optional pointer to 2 ints (set flag bit 2)
    int* data3,           // param_13: Optional pointer to 2 ints (set flag bit 3)
    byte flags,           // param_14: Additional flags (bit 4 gets XORed with extraByte)
    int* eaxPointer       // in_EAX: Optional pointer passed through EAX (used for 2 ints, flag bit 0)
)
{
    // First-time registration: add this->sourceId to the global logger list
    if (this->registered == '\0') {
        int src = this->sourceId;
        int* listPtr = (int*)(DAT_01206880 + 0x14); // pointer to list head
        **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_01123d28; // set up vtable? 
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = src;
        *listPtr = *listPtr + 4;
        this->registered = 1;
    }

    // Stack buffer for structured log data (64 bytes)
    int logBuffer[16]; // 16 * 4 = 64 bytes
    memset(logBuffer, 0, 0x40);

    // Fill buffer with numeric arguments
    logBuffer[0] = arg1;
    logBuffer[1] = arg2;
    logBuffer[2] = arg3;
    logBuffer[3] = arg4;
    logBuffer[4] = arg5;
    logBuffer[5] = arg6;
    logBuffer[6] = arg7;

    // Handle optional data pointers and set flag bits in the last byte of buffer
    // Flag layout: bit0 = eaxPointer present, bit1 = data1 present, bit2 = data2 present, bit3 = data3 present, bit4 = from flags^extraByte
    unsigned char flagsByte = 0;

    if (data1 == nullptr) {
        flagsByte &= ~0x02;
    } else {
        logBuffer[7] = data1[0];
        logBuffer[8] = data1[1];
        flagsByte |= 0x02;
    }

    if (eaxPointer == nullptr) {
        flagsByte &= ~0x01;
    } else {
        logBuffer[9] = eaxPointer[0];
        logBuffer[10] = eaxPointer[1];
        flagsByte |= 0x01;
    }

    if (data2 == nullptr) {
        flagsByte &= ~0x04;
    } else {
        logBuffer[11] = data2[0];
        logBuffer[12] = data2[1];
        flagsByte |= 0x04;
    }

    if (data3 == nullptr) {
        flagsByte &= ~0x08;
    } else {
        logBuffer[13] = data3[0];
        logBuffer[14] = data3[1];
        flagsByte |= 0x08;
    }

    // Compute final flags: bit4 from source (param_14 ^ extraByte)
    flagsByte = (flagsByte & ~0x10) | ((flags << 4 ^ flagsByte) & 0x10);

    // Store byte at specific offset? Actually local_8 is the last byte of the buffer? In the original stack layout, the byte ends up in the last position of the 64-byte block.
    // For simplicity, we store it at logBuffer[15] (offset 60)
    // But the original code places it as local_8 which is after the 12 dwords? Need to map exactly.
    // The stacking: local_44[0..3] = arg1-arg4? Actually copy to auStack_94 which is 64 bytes.
    // We'll assume the buffer structure is: 7 ints, then optional data blocks, then flags byte.

    // Then pack the local variables into the final 64-byte buffer (auStack_94)
    int finalBuffer[16];
    memcpy(finalBuffer, logBuffer, 0x40);

    // Calculate length of format string
    int formatLen = 0;
    if (format != nullptr) {
        formatLen = strlen(format);
    }

    // Call the core output function
    FUN_0048d240(format, formatLen, 1, this->sourceId, this->contextData);
}