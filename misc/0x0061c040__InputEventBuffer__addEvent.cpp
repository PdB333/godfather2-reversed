// FUNC_NAME: InputEventBuffer::addEvent
// Address: 0x0061c040
// Role: Stores input events (two sets of data) into a global buffer; flushes when buffer reaches 512 entries.

// Global buffer for storing events (512 entries * 0x60 bytes each)
extern uint8_t gEventBuffer[512 * 0x60]; // base at DAT_011f7540
extern int gEventCount; // DAT_0120596c
extern void* gContext; // unaff_ESI (some context pointer, e.g., device or session)

// Forward declarations of helper functions
void beginCriticalSection(void* section); // FUN_00612210
void* getGlobalString(const char* name); // FUN_0060a580
void setGlobal(void* globals, void* value); // FUN_0060a460
void applyLodBias(void* globals, void* lodBias, float bias); // FUN_0060aa90
void processEvents(); // FUN_00619950
void finalizeEvents(); // FUN_00619650
void sendEventData(int type, int size, void* data, int flags); // FUN_0060cc10
void resetEventSystem(); // FUN_00612e00

void __fastcall addEvent(uint32_t* param1, uint32_t* param2)
{
    int offset = gEventCount * 0x60; // offset into buffer for this entry

    // Store param1 data (12 DWORDs) and param2 data (8 DWORDs) into the buffer
    // Offsets relative to entry start:
    // +0x00: param1[0]
    // +0x04: param1[1]
    // +0x08: param1[2]
    // +0x0C: gContext (unaff_ESI)
    // +0x10: param2[0]
    // +0x14: param2[1]
    // +0x18: param1[3]
    // +0x1C: param1[4]
    // +0x20: param1[5]
    // +0x24: gContext
    // +0x28: param2[2]
    // +0x2C: param2[3]
    // +0x30: param1[6]
    // +0x34: param1[7]
    // +0x38: param1[8]
    // +0x3C: gContext
    // +0x40: param2[4]
    // +0x44: param2[5]
    // +0x48: param1[9]
    // +0x4C: param1[10]
    // +0x50: param1[11]
    // +0x54: gContext
    // +0x58: param2[6]
    // +0x5C: param2[7]

    *(uint32_t*)(gEventBuffer + offset + 0x00) = param1[0];
    *(uint32_t*)(gEventBuffer + offset + 0x04) = param1[1];
    *(uint32_t*)(gEventBuffer + offset + 0x08) = param1[2];
    *(uint32_t*)(gEventBuffer + offset + 0x0C) = (uint32_t)gContext;
    *(uint32_t*)(gEventBuffer + offset + 0x10) = param2[0];
    *(uint32_t*)(gEventBuffer + offset + 0x14) = param2[1];
    *(uint32_t*)(gEventBuffer + offset + 0x18) = param1[3];
    *(uint32_t*)(gEventBuffer + offset + 0x1C) = param1[4];
    *(uint32_t*)(gEventBuffer + offset + 0x20) = param1[5];
    *(uint32_t*)(gEventBuffer + offset + 0x24) = (uint32_t)gContext;
    *(uint32_t*)(gEventBuffer + offset + 0x28) = param2[2];
    *(uint32_t*)(gEventBuffer + offset + 0x2C) = param2[3];
    *(uint32_t*)(gEventBuffer + offset + 0x30) = param1[6];
    *(uint32_t*)(gEventBuffer + offset + 0x34) = param1[7];
    *(uint32_t*)(gEventBuffer + offset + 0x38) = param1[8];
    *(uint32_t*)(gEventBuffer + offset + 0x3C) = (uint32_t)gContext;
    *(uint32_t*)(gEventBuffer + offset + 0x40) = param2[4];
    *(uint32_t*)(gEventBuffer + offset + 0x44) = param2[5];
    *(uint32_t*)(gEventBuffer + offset + 0x48) = param1[9];
    *(uint32_t*)(gEventBuffer + offset + 0x4C) = param1[10];
    *(uint32_t*)(gEventBuffer + offset + 0x50) = param1[11];
    *(uint32_t*)(gEventBuffer + offset + 0x54) = (uint32_t)gContext;
    *(uint32_t*)(gEventBuffer + offset + 0x58) = param2[6];
    *(uint32_t*)(gEventBuffer + offset + 0x5C) = param2[7];

    gEventCount++;

    // When buffer is full (512 entries), flush
    if (gEventCount == 512)
    {
        if (gEventCount != 0)
        {
            beginCriticalSection(&gEventMutex); // FUN_00612210(&DAT_00f15640)
            // Set global variables for LOD bias processing
            gGlobalLodBias = gGlobalLodBias2; // DAT_01127774 = DAT_01127878
            gLodBiasPtr = getGlobalString(gGlobalLodBias2, "lodBias"); // DAT_01127868 = FUN_0060a580(DAT_01127878,"lodBias")
            if (gGlobalLodBias == &gLodBiasBase) // DAT_012058e8 == &PTR_PTR_01127760
            {
                setGlobal(gGlobalLodBias); // FUN_0060a460(DAT_01127774)
                applyLodBias(gGlobalLodBias, gLodBiasPtr, gLodBiasValue); // FUN_0060aa90(DAT_01127774,DAT_01127868,DAT_01127840)
            }
            processEvents(); // FUN_00619950
            finalizeEvents(); // FUN_00619650
            // Send event data: type 0xD, size = count*4, buffer, flags 0x18
            sendEventData(0xD, gEventCount * 4, gEventBuffer, 0x18); // FUN_0060cc10(0xd,DAT_0120596c * 4,&DAT_011f7540,0x18)
            resetEventSystem(); // FUN_00612e00
            // Clear global state
            gSomeGlobal1 = 0; // _DAT_01127804
            gSomeGlobal2 = 0; // _DAT_01127808
            gSomeGlobal3 = 0; // _DAT_0112780c
            gSomeGlobal4 = 0; // _DAT_01127810
            gSomeGlobal5 = 0; // _DAT_01127814
            gSomeGlobal6 = 0; // _DAT_01127818
            gSomeGlobal7 = 0; // _DAT_0112781c
            beginCriticalSection(&gEventMutex2); // FUN_00612210(&DAT_011f6b70)
            gEventCount = 0;
        }
    }
}