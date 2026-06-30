// FUNC_NAME: CoverHintNode::loadFromBinaryStream
// Function address: 0x006e9460
// Reads a CoverHintNode from a tagged binary stream (EARS binary serialization).
// The stream begins with block ID 0x5bc925cf, contains typed items (0-5), and ends with block ID 0xb390b11a.

#include <cstdint>

// Forward declarations for stream helper functions (from EARS engine).
// These are assumed to be __thiscall on the stream object.
bool __thiscall streamIsEmpty(void* stream);                 // FUN_0043b120
void* __thiscall streamReadNextItem(void* stream);           // FUN_0043b210 (no dest, returns pointer)
void __thiscall streamReadNextItemTo(void* stream, void* dest); // FUN_0043b210 with dest argument
uint32_t __thiscall streamGetTag(void* stream);              // FUN_0043ab70
void __thiscall streamProcessVector3(void* stream, void* vec); // FUN_0043ad10 (e.g., normalize, convert)
void __thiscall streamAdvance(void* stream);                 // FUN_0043b1a0
void __thiscall streamBeginBlock(void* stream, uint32_t id); // FUN_0043aff0
void __thiscall streamSetBlockType(void* stream, int type);  // FUN_0043af00 (type=1 likely marks end)
void __thiscall streamInit(void* stream);                    // FUN_0046c710

// Global constants
extern float g_worldScaleFactor; // DAT_00d5ef84 (multiplier for cover radius)
extern uint32_t g_worldMatrix;   // _DAT_00d5780c (likely identity matrix raw data)

class CoverHintNode {
public:
    // Offsets based on the deserialization pattern:
    // +0x54: m_navPosition (Vector3, 12 bytes)
    // +0x84: m_coverDirection (Vector3, 12 bytes)
    // +0x94: m_nodeId (uint32_t)
    // +0xA0: m_coverRadius (float)
    // +0xA4: m_coverSquareDist (float)
    // +0xA8: m_canStand (bool)

    void loadFromBinaryStream(void* stream); // __thiscall
};

void __thiscall CoverHintNode::loadFromBinaryStream(void* stream) {
    char cVar1;
    uint32_t tag;

    streamInit(stream);
    streamBeginBlock(stream, 0x5bc925cf);

    cVar1 = streamIsEmpty(stream);
    while (cVar1 == '\0') {
        void* dataPtr = streamReadNextItem(stream); // Fetch next item header
        tag = streamGetTag(stream);

        switch (tag) {
        case 0: {
            // Read a 32-bit value at offset 8 of the item data
            uint32_t val = *(uint32_t*)((char*)dataPtr + 8);
            *(uint32_t*)((char*)this + 0x94) = val;
            break;
        }
        case 1: {
            // Read a vector into m_coverDirection (+0x84)
            void* dest = (char*)this + 0x84;
            streamReadNextItemTo(stream, dest);
            streamProcessVector3(stream, dest);
            break;
        }
        case 2: {
            // Read a vector into m_navPosition (+0x54)
            void* dest = (char*)this + 0x54;
            streamReadNextItemTo(stream, dest);
            streamProcessVector3(stream, dest);
            break;
        }
        case 3: {
            // Read a float at offset 8 and store its square at +0xA4
            float f = *(float*)((char*)dataPtr + 8);
            *(float*)((char*)this + 0xA4) = f * f;
            break;
        }
        case 4: {
            // Read a float at offset 8, multiply by global scale, store at +0xA0
            float f = *(float*)((char*)dataPtr + 8);
            *(float*)((char*)this + 0xA0) = f * g_worldScaleFactor;
            break;
        }
        case 5: {
            // Read a boolean (1 byte) at offset 8, store at +0xA8
            char b = *(char*)((char*)dataPtr + 8);
            *(char*)((char*)this + 0xA8) = b;
            break;
        }
        }
        streamAdvance(stream);
        cVar1 = streamIsEmpty(stream);
    }

    streamBeginBlock(stream, 0xb390b11a);
    streamSetBlockType(stream, 1);

    cVar1 = streamIsEmpty(stream);
    if (cVar1 == '\0') {
        // Local buffer used to build a transform for subsequent operations (e.g., world matrix)
        char localBuf[12]; // placeholder for a matrix row or quaternion
        uint32_t local_b4 = 0;
        uint32_t local_a4 = 0;
        uint32_t local_94 = 0;
        uint32_t local_84 = g_worldMatrix;

        void* bufPtr = localBuf;

        // Read next item into the local buffer
        streamReadNextItemTo(stream, bufPtr);
        // Process the buffer (likely convert to a usable form)
        // FUN_0043ac60 expected to be streamReadRawData or similar
        streamReadRawData(stream, bufPtr); // placeholder name

        // Apply the resulting transform (e.g., convert to the cover node's local space)
        // FUN_006e8fd0 is called with the local buffer
        applyTransform(bufPtr); // placeholder name
    }
}