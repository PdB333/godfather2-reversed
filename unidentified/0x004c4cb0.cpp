// FUN_004c4cb0: SlotManager::initializeSlot
// Function address: 0x004c4cb0
// Initializes a slot in the slot manager with given packet pointer, key, flags, and extra data.
// Parameters:
//   slotIndex - index into slot arrays
//   packetPtr - pointer to a packet or ghost object
//   flags - short flags (stored at +0x2a of packet)
//   extraData - some integer value
//   key - pointer to 16-byte key (UUID or similar)
// Uses 'this' (EDI) as the SlotManager object.

#include <cstdint>

// Forward declarations for called functions
uint32_t FUN_004c4ae0(); // generates some unique ID or timestamp
bool FUN_00441b10(uint32_t param_1, int* param_2); // likely a callback or validation

class SlotManager {
public:
    // Offset: +0x00 - vtable? (not used directly)
    // Offset: +0x04 - pointer to array of 16-byte keys (undefined8[2] per index)
    // Offset: +0x08 - pointer to array of bytes (1 per index)
    // Offset: +0x0C - pointer to array of shorts (2 bytes per index)
    // Offset: +0x10 - pointer to array of slot data structures (each 0x20 = 32 bytes)

    void initializeSlot(int slotIndex, void* packetPtr, uint16_t flags, uint32_t extraData, const uint64_t* key) {
        int iVar1;
        char cVar2;
        uint32_t uVar3;
        uint64_t* puVar4;
        int iVar5;

        iVar1 = packetPtr; // Note: param_2 is used as int but actually a pointer
        // Store slotIndex as short at packetPtr + 0x2a
        *(uint16_t*)((uint8_t*)packetPtr + 0x2a) = (uint16_t)slotIndex;

        iVar5 = slotIndex * 0x20; // offset into slot data array

        // Store packetPtr into slot data array at offset +0
        *(void**)(*(uint8_t**)((uint8_t*)this + 0x10) + 0x10 + iVar5) = packetPtr; // +0x10 is base of slot data array? Wait: actually *(int*)(this+0x10) is a pointer, then +0x10 + iVar5 is an offset inside that pointer? Let's recalc.
        // The decompiled: *(int *)(*(int *)(unaff_EDI + 0x10) + 0x10 + iVar5) = param_2;
        // So *(int*)(this+0x10) gets a pointer P. Then *(int*)(P + 0x10 + iVar5) = packetPtr.
        // That suggests the slot data structure has its own base pointer and offsets.
        // But iVar5 = slotIndex*0x20, so the total offset is 0x10 + slotIndex*0x20.
        // Probably the structure at this+0x10 is a pointer to an array of slot data, each 0x20 bytes.
        // Then each slot data starts with some fields.
        // For simplicity, we'll treat the slot data as a struct.

        // Let's define a local struct for readability
        struct SlotData {
            void* ptr;        // +0x00 (4 bytes)
            uint32_t field4;  // +0x04 (4 bytes)
            uint32_t field8;  // +0x08 (4 bytes)
            uint32_t fieldC;  // +0x0C (4 bytes)
            uint32_t field10; // +0x10 (4 bytes)
            uint32_t field14; // +0x14 (4 bytes)
            uint32_t field18; // +0x18 (4 bytes)
            uint32_t field1C; // +0x1C (4 bytes)
        }* slotData;

        // Get pointer to slot data array
        slotData = (SlotData*)(*(uint8_t**)((uint8_t*)this + 0x10));

        // Store packetPtr at slotData[slotIndex].ptr (offset 0)
        slotData[slotIndex].ptr = packetPtr;

        // Call FUN_00441b10 with two arguments: something from packet->+0x54->+0x30 and &packetPtr
        cVar2 = FUN_00441b10(
            *(uint32_t*)(*(uint32_t*)((uint8_t*)packetPtr + 0x54) + 0x30),
            (int*)&packetPtr
        );

        if (cVar2 == 0) {
            // If first call returns false, call again with different parameter
            FUN_00441b10(
                *(uint32_t*)(*(uint32_t*)((uint8_t*)packetPtr + 0x54) + 0x34),
                (int*)&packetPtr
            );
        }

        // Store something into slotData[slotIndex].field4 (offset +4)
        slotData[slotIndex].field4 = (uint32_t)packetPtr; // Actually the same packetPtr? The decompiled: *(int *)(*(int *)(unaff_EDI + 0x10) + 4 + iVar5) = param_2; So offset 4 from base, but iVar5 includes 0x10? Let's re-examine.
        // The original: *(int *)(*(int *)(unaff_EDI + 0x10) + 4 + iVar5) = param_2;
        // If we consider slotData pointer as base, then slotData[slotIndex].field4 is at base + 4 + slotIndex*0x20.
        // But earlier we used base + 0x10 + slotIndex*0x20 for the first store. So the offsets within each slot are 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C.
        // So first store went to slotData[slotIndex].ptr (offset 0x00). This store goes to slotData[slotIndex].field4 (offset 0x04).
        slotData[slotIndex].field4 = (uint32_t)packetPtr; // reassigning after possible modification? The function might modify packetPtr? But it's passed by address.

        // Store something from packet->+0x54->+0x30 into slotData[slotIndex].field8 (offset 0x08)
        slotData[slotIndex].field8 = *(uint32_t*)(*(uint32_t*)((uint8_t*)packetPtr + 0x54) + 0x30);

        // Store something from packet + 100? (0x64) into slotData[slotIndex].field18 (offset 0x18)
        slotData[slotIndex].field18 = *(uint32_t*)((uint8_t*)packetPtr + 100); // +100 decimal = 0x64

        // Store extraData into slotData[slotIndex].fieldC (offset 0x0C)
        slotData[slotIndex].fieldC = extraData;

        // Call FUN_004c4ae0 to get a unique ID
        uVar3 = FUN_004c4ae0();
        // Store that ID into slotData[slotIndex].field14 (offset 0x14)
        slotData[slotIndex].field14 = uVar3;

        // Clear slotData[slotIndex].field1C (offset 0x1C)
        slotData[slotIndex].field1C = 0;

        // Now handle the key array (this+4)
        uint64_t* keyArray = *(uint64_t**)((uint8_t*)this + 4);
        // Copy the 16-byte key into keyArray[slotIndex*2] and keyArray[slotIndex*2+1]
        // Actually puVar4 = (undefined8 *)(param_1 * 0x10 + *(int *)(unaff_EDI + 4));
        // So keyArray[slotIndex*2] is the 8-byte aligned index.
        keyArray[slotIndex * 2] = key[0];
        keyArray[slotIndex * 2 + 1] = key[1];

        // Store 0xFF into byte array (this+8) at slotIndex
        uint8_t* byteArray = *(uint8_t**)((uint8_t*)this + 8);
        byteArray[slotIndex] = 0xFF;

        // Store flags into short array (this+0xC) at slotIndex
        uint16_t* shortArray = *(uint16_t**)((uint8_t*)this + 0xC);
        shortArray[slotIndex] = flags;
    }
};