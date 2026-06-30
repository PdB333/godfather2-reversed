// FUNC_NAME: CommandBuffer::readAudioEvent
#include <cstdint>

// Assumed class layout:
// +0x00: (unknown)
// +0x08: uint8_t* m_pBufferEnd   (pointer to one past last byte of buffer)
// +0x0C: uint8_t* m_pReadPtr     (current read position)
// +0x??: function pointer m_pCallback (callback for non-zero result)

class CommandBuffer {
public:
    uint8_t* m_pReadPtr;      // +0x0C
    uint8_t* m_pBufferEnd;    // +0x08
    // ... other members, including possibly m_pCallback at some offset

    // This function processes audio commands from the buffer.
    // It reads a command header (type 3 or 4) followed by float parameters.
    // If the command type is 4, an additional validity check is performed.
    // After reading, it calls a sound playback function with flags and a float value.
    // Returns always 0.
    uint32_t readAudioEvent();
};

// External functions (not defined here)
extern uint32_t g_soundChannelID;  // DAT_012233fc
extern uint32_t g_someGlobalFlag;  // _DAT_00e44970
extern int isCommandValid();       // FUN_00636850
extern float readEventFloat(CommandBuffer* pBuf, int index); // FUN_006259b0
extern void skipEventField(CommandBuffer* pBuf, int index); // FUN_00625a70
extern void audioEnginePrepare();  // FUN_004d3bc0
extern void playSoundEvent(uint32_t channelID, uint32_t flags, float param, uint32_t extraFlag); // FUN_00458d10

uint32_t CommandBuffer::readAudioEvent()
{
    uint32_t* pCurrentWord = reinterpret_cast<uint32_t*>(m_pReadPtr);
    uint32_t* pEndWord = reinterpret_cast<uint32_t*>(m_pBufferEnd);

    // Check if we have space for at least one command dword
    if (pEndWord <= pCurrentWord) {
        return 0;
    }
    // First dword must be non-null and be type 3 or 4
    if (pCurrentWord == nullptr) {
        return 0;
    }
    uint32_t commandType = *pCurrentWord;
    if (commandType != 3) {
        if (commandType != 4) {
            return 0;
        }
        // For type 4, perform additional validity check
        if (!isCommandValid()) {
            return 0;
        }
    }

    // Move read pointer past the command header (2 words = 8 bytes)
    pCurrentWord = reinterpret_cast<uint32_t*>(m_pReadPtr + 8);
    if (pEndWord <= pCurrentWord) {
        return 0;
    }
    if (pCurrentWord == nullptr) {
        return 0;
    }

    // Check the second word (offset +8) for type 3 or 4
    uint32_t secondType = *pCurrentWord;
    if (secondType != 4 && secondType != 3) {
        return 0;
    }

    // Read first float parameter from the data block (index 1)
    float firstFloat = readEventFloat(this, 1);

    // Build flags: start with a base value (simulated FPU control word manipulation)
    uint32_t flags = 0xC00;  // Bits 10-11 set (model for original code)
    // In the original, the flags were built using FPU control word bits.
    // For reconstruction, we use a constant based on the observed pattern.

    // Skip the field at index 2 (advance read pointer)
    skipEventField(this, 2);

    // Prepare for optional second float
    uint32_t* nextWord = reinterpret_cast<uint32_t*>(m_pReadPtr + 0x10);
    float secondFloat = 0.0f;
    // Check if there is a third data word at offset +0x10
    if ((nextWord < pEndWord) && (nextWord != nullptr)) {
        uint32_t thirdType = *nextWord;
        if (thirdType == 3 || (thirdType == 4 && isCommandValid())) {
            // If present, set flag bit 8 and read the second float
            flags |= 0x100; // Bit 8 set
            secondFloat = readEventFloat(this, 3);
        }
    }

    // Call audio preparation function
    audioEnginePrepare();

    // Play the sound event with gathered parameters
    playSoundEvent(g_soundChannelID, flags, secondFloat, g_someGlobalFlag);

    // Round the first float to integer (used for callback trigger)
    int32_t roundedValue = static_cast<int32_t>(firstFloat + 0.5f);
    if (roundedValue != 0) {
        // Callback function pointer – assumed to be a member variable
        // WARNING: In the original decompiled code, this pointer (local_44) was not initialized.
        // It may be a local that should have been set earlier, or a member of the class.
        // For safety, assume it's a member at some offset not shown.
        if (m_pCallback != nullptr) {
            m_pCallback();
        }
    }
    return 0;
}