// FUNC_NAME: SimNpc::deserializeProperties
// Address: 0x008fd7c0
// Role: Deserializes a network snapshot of NPC properties from a stream. Reads tokens for various fields (integers, vector, string handles) and updates the SimNpc instance.

#include <cstdint>

class SimNpc {
public:
    // Offsets relative to this pointer (from decompilation):
    // +0x54: int32_t m_propertyA;          // Property A (some integer)
    // +0x58: int32_t m_propertyB;          // Property B
    // +0x5c: int32_t m_propertyC;          // Property C
    // +0x60: int32_t m_propertyD;          // Property D
    // +0x6c: int32_t m_propertyE;          // Property E
    // +0x70: int32_t m_propertyF;          // Property F
    // +0x74: int32_t m_propertyG;          // Property G (maybe weapon index)
    // +0x78: int32_t m_handle1;            // Non-zero indicates active resource handle
    // +0x80: int32_t m_handle2;            // Another resource handle
    // +0x88: int32_t m_handle3;            // Another resource handle
    // +0x90..0x9c: float m_orientation[4]; // Quaternion orientation (16 bytes)
    // +0xa0: uint32_t m_stringId1;         // String/ID handle (via FUN_00408980)
    // +0xa8: uint32_t m_stringId2;         // Another string handle
    // +0xb0: uint32_t m_stringId3;         // Another string handle (via FUN_004089b0)
    // +0xb8: uint32_t m_stringId4;         // Another string handle
    // +0xc0: uint32_t m_stringId5;         // Another string handle
    // +0x64: int16_t m_activeCount;        // Short counter incremented if handles are active

    // Forward declarations for engine functions (likely from EARS serialization library)
    void streamBegin(void* stream);                    // FUN_0046c710
    void streamSetType(void* stream, uint32_t type);   // FUN_0043aff0 (type = 0x6b2fbd39)
    bool streamHasMore(void);                          // FUN_0043b120 (returns cVar1)
    void* streamReadValue(void);                       // FUN_0043b210 (returns pointer to value data, +8 is actual value)
    int32_t streamGetToken(void);                      // FUN_0043ab70 (returns token type)
    void* streamReadVector(void);                      // FUN_0043abc0 (returns pointer to 4 floats)
    uint32_t streamReadHandle(void);                   // FUN_0043ab90 (returns handle/ID)
    void setStringId(uint32_t& dest, uint32_t id);     // FUN_00408980 (assigns id to dest)
    void setStringIdAlt(uint32_t& dest, uint32_t id);  // FUN_004089b0 (similar assignment, maybe for different type)
    void streamNext(void);                             // FUN_0043b1a0 (advance to next token?)
};

void __thiscall SimNpc::deserializeProperties(void* param_1, void* stream) {
    char cVar1;
    int32_t uVar2;
    void* puVar3;
    int32_t iVar4;
    int32_t token;

    // Initialize stream and verify type
    streamBegin(stream);
    streamSetType(stream, 0x6b2fbd39); // Class identifier for SimNpc properties

    cVar1 = streamHasMore();
    do {
        if (cVar1 != '\0') {
            // Stream has finished reading all tokens.
            // If certain resource handles are non-zero, increment active count.
            if (*(int32_t*)((char*)param_1 + 0x78) != 0) {
                *(int16_t*)((char*)param_1 + 0x64) = *(int16_t*)((char*)param_1 + 0x64) + 1;
            }
            if (*(int32_t*)((char*)param_1 + 0x80) != 0) {
                *(int16_t*)((char*)param_1 + 0x64) = *(int16_t*)((char*)param_1 + 0x64) + 1;
            }
            if (*(int32_t*)((char*)param_1 + 0x88) != 0) {
                *(int16_t*)((char*)param_1 + 0x64) = *(int16_t*)((char*)param_1 + 0x64) + 1;
            }
            return;
        }

        streamNext(); // Prepare for next token
        token = streamGetToken();
        switch (token) {
            case 0: // Integer property A
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x54) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 1: // Quaternion orientation (16 bytes)
                streamReadValue(); // Consume the token value? Actually streamReadVector is used directly
                puVar3 = (void*)streamReadVector();
                *(int32_t*)((char*)param_1 + 0x90) = *(int32_t*)puVar3;
                *(int32_t*)((char*)param_1 + 0x94) = *(int32_t*)((char*)puVar3 + 4);
                *(int32_t*)((char*)param_1 + 0x98) = *(int32_t*)((char*)puVar3 + 8);
                *(int32_t*)((char*)param_1 + 0x9c) = *(int32_t*)((char*)puVar3 + 12);
                break;
            case 2: // Integer property B
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x58) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 3: // Integer property E
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x6c) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 4: // Integer property C
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x5c) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 5: // Integer property D
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x60) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 6: // Integer property F
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x70) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 7: // Integer property G
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x74) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 8: // Resource handle 1
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x78) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 9: // Resource handle 2
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x80) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 10: // Resource handle 3
                iVar4 = (int32_t)streamReadValue();
                *(int32_t*)((char*)param_1 + 0x88) = *(int32_t*)((char*)iVar4 + 8);
                break;
            case 11: // String ID 1 (via setStringId)
                streamReadValue();
                uVar2 = streamReadHandle();
                setStringId(*(uint32_t*)((char*)param_1 + 0xa0), uVar2);
                break;
            case 12: // String ID 2 (via setStringId)
                streamReadValue();
                uVar2 = streamReadHandle();
                setStringId(*(uint32_t*)((char*)param_1 + 0xa8), uVar2);
                break;
            case 13: // String ID 3 (via setStringIdAlt)
                streamReadValue();
                uVar2 = streamReadHandle();
                {
                    int32_t dest = (int32_t)((char*)param_1 + 0xb0);
                    setStringIdAlt(*(uint32_t*)dest, uVar2);
                }
                break;
            case 14: // String ID 4 (via setStringIdAlt)
                streamReadValue();
                uVar2 = streamReadHandle();
                {
                    int32_t dest = (int32_t)((char*)param_1 + 0xb8);
                    setStringIdAlt(*(uint32_t*)dest, uVar2);
                }
                break;
            case 15: // String ID 5 (via setStringIdAlt)
                streamReadValue();
                uVar2 = streamReadHandle();
                {
                    int32_t dest = (int32_t)((char*)param_1 + 0xc0);
                    setStringIdAlt(*(uint32_t*)dest, uVar2);
                }
                break;
        }
        // streamNext is called at the start of each iteration, not at end.
        cVar1 = streamHasMore();
    } while (true);
}