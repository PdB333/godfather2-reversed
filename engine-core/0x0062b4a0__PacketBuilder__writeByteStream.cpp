// FUNC_NAME: PacketBuilder::writeByteStream
// Function address: 0x0062b4a0
// Reconstructed from Ghidra decompilation of The Godfather 2 (2008, EARS engine)

#include <cstdint>

// Forward declarations for helper functions called
int FUN_006259b0(PacketBuilder* this, int index);          // Get serialized value as float (returns int? actually used as float)
void FUN_00627ac0(const char* msg);                         // Print error
int FUN_00636850(uint8_t* buffer);                         // Some condition check (returns 0 if pass)
int FUN_00628940();                                        // Check buffer overflow?
void FUN_006289a0(uint8_t** bufPtr);                       // Grow/advance buffer?
int FUN_00627290();                                        // Lock packet buffer
void FUN_00626f80(PacketBuilder* this, int arg);           // Start/prepare packet
void FUN_00626fd0(int type);                               // Set packet type
void FUN_00627010(int handle);                             // Attach data
void FUN_006270e0();                                       // Commit/close
int FUN_00638920(PacketBuilder* this, uint8_t* data, int len); // Copy data to packet buffer, returns handle
void FUN_00626460();                                       // Unlock

// Assumed structure layout (offsets relative to this pointer)
struct PacketBuilder {
    // +0x00: vtable or other
    // +0x08: uint8_t* dataEnd;        // End pointer of serialized data array (8-byte entries)
    // +0x0C: uint8_t* dataStart;      // Start pointer of serialized data array
    // +0x10: void* ghostList;         // Pointer to some ghost/connection list structure
    // +0x40: int dummyValue;          // Placeholder for special index -0x2711
};

// Assumed ghost list entry (offsets used: +0x2c and byte at +7)
struct GhostListNode {
    // +0x2c: int someField;           // Used for index -10000
    // +0x07: uint8_t length;          // Length of this node's serialized data?
};

int PacketBuilder::writeByteStream() {
    uint8_t localBuffer[512];            // Stack buffer for the data to write
    uint8_t* bufPtr = localBuffer;       // Current write position
    int entryCount = 0;                  // How many times we wrote a buffer (not used except local?)
    int savedThis = (int)this;           // Used later

    // Compute number of entries from the difference of pointers (each entry 8 bytes)
    int numEntries = (*(int*)((uint8_t*)this + 0x8) - *(int*)((uint8_t*)this + 0xC)) >> 3;

    int index = 1;                       // Start at index 1 (0-based by the array)
    int currentIndex = index;
    if (numEntries > 0) {
        do {
            // Get float value for this index (likely returns an integer stored as float)
            float value = (float)FUN_006259b0(this, index);
            if (value == 0.0f) {
                // Special handling: if value is zero, find the actual data pointer for this index
                int* dataPtr = nullptr;
                if (index < -9999) {
                    // Very negative indices: special cases
                    if (index == -0x2711) {
                        dataPtr = (int*)((uint8_t*)this + 0x40); // Points to this+0x40
                    } else if (index == -10000) {
                        dataPtr = (int*)(*(int*)((uint8_t*)this + 0x10) + 0x2c); // Ghost list node field
                    } else {
                        // General case: get previous entry base
                        int base = *(int*)(*(int*)((uint8_t*)this + 0xC) - 4); // Deref from dataStart-4
                        int adjustedIndex = -0x2711 - index; // Convert to positive offset?
                        if ((uint8_t)(*(uint8_t*)(base + 7)) < adjustedIndex) {
                            dataPtr = nullptr;
                        } else {
                            dataPtr = (int*)(base + 8 + adjustedIndex * 8);
                        }
                    }
                } else {
                    // Normal index: direct offset into the main array
                    dataPtr = (int*)(*(int*)((uint8_t*)this + 0x8) + index * 8);
                }

                // Skip this entry if dataPtr is null or if the entry type is not suitable
                if (dataPtr != nullptr) {
                    if (*dataPtr != 3) {
                        if (*dataPtr != 4 || (FUN_00636850(nullptr), currentIndex = numEntries, 0)) {
                            // If condition fails, loop continues
                        }
                    }
                }
            }

            // Ensure the float value fits in a byte
            if ( ((int)value & 0xFF) != (int)value ) {
                FUN_00627ac0("invalid value");
                // Trigger a software interrupt (assert)
                void(*panic)() = (void(*)())(3);
                panic();
                return 0; // Unreachable
            }

            // Check for buffer overflow; if localBuffer plus written so far is near stack end, grow
            if ( (uint8_t*)localBuffer <= bufPtr ) {
                int overflowCheck = FUN_00628940();
                currentIndex = numEntries;
                if (overflowCheck != 0) {
                    FUN_006289a0(&bufPtr);  // Could advance the buffer pointer
                }
            }

            // Write the integer part of the float as a byte
            *bufPtr = (uint8_t)(int)value;
            bufPtr++;
            index++;
        } while (index <= currentIndex);
    }

    // If we wrote any bytes
    int dataLength = (int)(bufPtr - localBuffer);
    if (dataLength != 0) {
        // Check if there's space in the packet buffer (compare sizes at offsets +0x20 and +0x24)
        if (*(uint32_t*)(*(int*)(savedThis + 0x10) + 0x20) <= *(uint32_t*)(*(int*)(savedThis + 0x10) + 0x24)) {
            int handle = FUN_00627290();
            FUN_00626f80(this, 0);
            FUN_00626fd0(0);
            FUN_00626f80(this, 0);
            FUN_00627010(handle);
            FUN_006270e0();
        }

        // Write packet header: type = 4
        int* packetPtr = *(int**)(savedThis + 0x8);  // Current write position in packet
        *packetPtr = 4;
        int dataHandle = FUN_00638920(this, localBuffer, dataLength);
        *(packetPtr + 1) = dataHandle;
        *(int*)(savedThis + 0x8) += 8;  // Advance packet write pointer by 2 ints

        // Reset local buffer pointer
        bufPtr = localBuffer;
        entryCount++;
    }

    FUN_00626460();  // Finalize/unlock
    return 1;
}