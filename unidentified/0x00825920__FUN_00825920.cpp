// FUNC_NAME: Unknown::loadFromStream

#include <cstdint>

// Forward declarations of external functions (assumed from EARS streaming library)
static void* streamBeginChunk(uint32_t chunkId);
static bool streamIsEnd();
static void* streamReadNode();
static uint32_t streamReadOpcode();
static uint32_t streamReadSubValue();
static void setSomeGlobal(uint32_t value);
static void setNameField(void* dest, uint32_t value); // sets string or ID at +0x50
static float* getInitialTransform(); // returns pointer to 4 floats

// External bounds for float field clamping
extern float g_floatMin;  // _DAT_00d577a0
extern float g_floatMax;  // DAT_00d5e288

// This class likely holds parsed data from a binary stream chunk
// Offsets (relative to 'this'):
// +0x50: uint32_t? (name/ID)
// +0x68: uint16_t fieldA
// +0x6A: uint16_t fieldB
// +0x6C: uint8_t fieldC
// +0x6D: uint8_t fieldD
// +0x6E: uint8_t fieldE
// +0x70: int32_t fieldF
// +0x74: float fieldG (clamped to [g_floatMin, g_floatMax])
// +0x78-0x84: float[4] transform (e.g., bounding box or quaternion)

void __thiscall FUN_00825920(int this, void* streamParam)
{
    // Step 1: Load initial 4-float transform
    float* initialData = (float*)getInitialTransform();
    *(float*)(this + 0x78) = initialData[0];
    *(float*)(this + 0x7C) = initialData[1];
    *(float*)(this + 0x80) = initialData[2];
    *(float*)(this + 0x84) = initialData[3];

    // Step 2: Initialize chunk reading with magic 0x61857316
    streamBeginChunk(0x61857316);

    // Step 3: Parse tagged data blocks until end
    bool done = false;
    while (!done)
    {
        void* node = streamReadNode();
        uint32_t opcode = streamReadOpcode();
        switch (opcode)
        {
            case 0: // Complex: sets two values
            {
                streamReadNode(); // consume extra node?
                uint32_t val1 = streamReadSubValue();
                setSomeGlobal(val1); // likely sets a module-level variable
                streamReadNode(); // consume another node?
                uint32_t val2 = streamReadSubValue();
                setNameField((void*)(this + 0x50), val2); // store name/ID at +0x50
                break;
            }
            case 1: // uint16_t at +0x68
            {
                *(uint16_t*)(this + 0x68) = *(uint16_t*)((uint8_t*)node + 8);
                break;
            }
            case 2: // uint16_t at +0x6A
            {
                *(uint16_t*)(this + 0x6A) = *(uint16_t*)((uint8_t*)node + 8);
                break;
            }
            case 3: // uint8_t at +0x6C
            {
                *(uint8_t*)(this + 0x6C) = *(uint8_t*)((uint8_t*)node + 8);
                break;
            }
            case 4: // uint8_t at +0x6D
            {
                *(uint8_t*)(this + 0x6D) = *(uint8_t*)((uint8_t*)node + 8);
                break;
            }
            case 5: // uint8_t at +0x6E
            {
                *(uint8_t*)(this + 0x6E) = *(uint8_t*)((uint8_t*)node + 8);
                break;
            }
            case 6: // int32_t at +0x70
            {
                *(int32_t*)(this + 0x70) = *(int32_t*)((uint8_t*)node + 8);
                break;
            }
            case 7: // float at +0x74 with clamping
            {
                float val = *(float*)((uint8_t*)node + 8);
                if (val >= g_floatMin && val <= g_floatMax)
                {
                    *(float*)(this + 0x74) = val;
                }
                // else ignore (keep previous value?)
                break;
            }
            default:
                // Unknown opcode, ignore?
                break;
        }
        // Advance to next chunk element (stream read position update)
        // (implied by streamReadNode calls within loop)
        // Check if we've reached end of chunk
        done = streamIsEnd();
    }
    return;
}