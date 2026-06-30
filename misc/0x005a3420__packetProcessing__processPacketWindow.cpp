// FUNC_NAME: packetProcessing::processPacketWindow

#include <cstdint>

// External function prototypes (from the game's packet processing module)
void FUN_005a0a00(int srcPtr);   // Validates or processes a single packet entry
void FUN_005a1060();              // Finalizes packet processing (e.g., updates checksums)

// Function pointer at 0x0119caf4 – deallocates a temporary buffer (likely custom free)
extern void (*DAT_0119caf4)(void* ptr);

/**
 * Processes a sliding window of 32-byte packet entries.
 * 
 * @param srcStart  Pointer to the first source entry (passed in EAX).
 * @param srcEnd    Pointer to the end of the source window (exclusive).
 * @param dstStart  Pointer to the start of the destination buffer.
 * @return          The new destination pointer after processing all entries.
 *
 * The function iterates over source entries, copying a 4-byte field at offset +0x1c
 * to the corresponding destination entry. Additionally, it processes each entry via
 * FUN_005a0a00 and finalizes via FUN_005a1060. Temporary string buffers (e.g., for
 * logging sequence numbers) are freed if they are not on the stack.
 */
int processPacketWindow(int srcStart, int srcEnd, int dstStart) {
    int currentSrc = srcStart;   // in_EAX – source iterator
    int currentDst = dstStart;   // iVar2   – destination iterator

    // Stack-allocated 16-byte buffer for temporary string storage
    char tempBuffer[16];
    char* tempString = nullptr;  // local_14 – pointer to temporary string

    if (currentSrc == srcEnd) {
        return currentDst;
    }

    do {
        int nextDst = currentDst + 0x20;   // param_2 – next destination slot

        // Process the current source entry
        FUN_005a0a00(currentSrc);
        FUN_005a1060();

        // Free dynamically allocated temporary string if necessary
        if ((tempString != tempBuffer) && (tempString != nullptr)) {
            DAT_0119caf4(tempString);
            tempString = nullptr;
        }

        // Copy the 4-byte field at offset 0x1c (e.g., sequence number or timestamp)
        uint32_t* srcField = reinterpret_cast<uint32_t*>(currentSrc + 0x1c);
        *reinterpret_cast<uint32_t*>(currentDst + 0x1c) = *srcField;

        // Advance both pointers by 32 bytes (size of each entry)
        currentSrc += 0x20;
        currentDst = nextDst;
    } while (currentSrc != srcEnd);

    return currentDst;
}