// FUNC_NAME: StateSync::updateState

// Function address: 0x00586740
// Copies state data between two state structures based on flags.
// The object (this) contains a flag and two data buffer pointers.
// param_1 and param_2 are pointers to SourceState structures (flag + buffer ptrs).
// The function checks param_2's flag first: if it's 2, use param_2 as source.
// Otherwise, if param_1's flag is 2, use param_1 as source.
// If neither flag is 2, set this->flag to 0 and return.
// When a source is selected, copies 8 dwords from source->buffer1 to this->buffer1,
// and 4 dwords from source->buffer2 to this->buffer2.

#include <cstdint>

// Forward declaration of the state structure used by both parameters and this object.
struct StateData {
    uint8_t flag;          // +0x00: flag (0 or 2)
    uint32_t* buffer1;     // +0x04: pointer to 8 dwords (32 bytes)
    uint32_t* buffer2;     // +0x08: pointer to 4 dwords (16 bytes)
};

// The class that contains this method.
class StateSync {
public:
    // +0x00: m_flag (uint8_t)
    // +0x04: m_buffer1 (uint32_t*)
    // +0x08: m_buffer2 (uint32_t*)

    void __thiscall updateState(StateData* param_1, StateData* param_2);
};

void __thiscall StateSync::updateState(StateData* param_1, StateData* param_2) {
    uint8_t localFlag = param_1->flag;    // cVar1
    uint8_t* thisFlagPtr = reinterpret_cast<uint8_t*>(this); // offset 0

    if (param_2->flag == 2) {
        *thisFlagPtr = 2;
        if (localFlag != 2) {
            // Copy from param_2's buffers to this
            uint32_t* srcBuf1 = param_2->buffer1;
            uint32_t* dstBuf1 = this->m_buffer1; // this+0x04
            uint32_t* srcBuf2 = param_2->buffer2;
            uint32_t* dstBuf2 = this->m_buffer2; // this+0x08

            // Copy 8 dwords from srcBuf1 to dstBuf1
            for (int i = 0; i < 8; ++i) {
                dstBuf1[i] = srcBuf1[i];
            }
            // Copy 4 dwords from srcBuf2 to dstBuf2
            for (int i = 0; i < 4; ++i) {
                dstBuf2[i] = srcBuf2[i];
            }
            return;
        }
    } else {
        if (localFlag != 2) {
            *thisFlagPtr = 0;
            return;
        }
        *thisFlagPtr = 2;
    }

    // Copy from param_1's buffers to this
    uint32_t* srcBuf1 = param_1->buffer1;
    uint32_t* dstBuf1 = this->m_buffer1;
    uint32_t* srcBuf2 = param_1->buffer2;
    uint32_t* dstBuf2 = this->m_buffer2;

    // Copy 8 dwords
    for (int i = 0; i < 8; ++i) {
        dstBuf1[i] = srcBuf1[i];
    }
    // Copy 4 dwords
    for (int i = 0; i < 4; ++i) {
        dstBuf2[i] = srcBuf2[i];
    }
}