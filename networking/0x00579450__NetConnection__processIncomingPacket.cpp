// FUNC_NAME: NetConnection::processIncomingPacket
// Address: 0x00579450
// This function processes an incoming packet from the network layer.
// It validates the packet, updates timers, copies data into a ring buffer,
// and invokes a callback if registered.

typedef unsigned char undefined1;
typedef unsigned int undefined4;
typedef long double float10; // 80-bit float

// Packet descriptor structure (param_2)
struct PacketDescriptor {
    int* pObject;          // +0x00: pointer to some object (e.g., ghost)
    int* pData;            // +0x04: pointer to packet data buffer
    int field_0x08;        // +0x08: some ID or type
    int field_0x0C;        // +0x0C: another ID
    int sequence;          // +0x10: sequence number (-1 means use field_0x0C)
    char flag;             // +0x14: flag (0 or 1)
    int packetType;        // +0x18: packet type (3,4, etc.)
};

// Forward declarations of called functions
undefined1 FUN_005890e0(int slotAddr, int* pData); // compare/copy data into slot?
undefined1 FUN_00581b30(int thisPtr, int sequence); // validate packet?
float10 FUN_00586a30(undefined4 timestamp); // convert timestamp to float?
void FUN_00586c00(int param, int thisPtr, int* pData); // callback for special packets

undefined1 __thiscall NetConnection::processIncomingPacket(int thisPtr, PacketDescriptor* pDesc)
{
    int* pData;
    int slotIndex;
    int slotAddr;
    undefined4 uVar1;
    int iVar7;
    undefined4 uVar14;
    float fVar2;
    float* pfVar6;
    int iVar9;
    char cVar4;
    char cVar5;
    float10 fVar13;
    int* piVar11;
    int* piVar12;
    int iVar8;

    // Compute slot index in ring buffer (circular increment)
    // +0x2e8: current write index, +0x2e4: window size, +0x2ec: base address of slot array
    iVar8 = (*(int*)(thisPtr + 0x2e8) + 1 + *(int*)(thisPtr + 0x2e4)) % *(int*)(thisPtr + 0x2e4);
    pData = pDesc->pData; // +0x04
    slotAddr = iVar8 * 0xe0 + *(int*)(thisPtr + 0x2ec); // slot size = 0xe0 (224 bytes)

    // Compare/copy data into slot? Returns non-zero if data matches?
    cVar4 = FUN_005890e0(slotAddr, pData);

    uVar1 = *(undefined4*)(thisPtr + 0x1c); // some timestamp or ID
    iVar7 = pDesc->sequence; // +0x10
    uVar14 = *(undefined4*)(thisPtr + 0x24); // another timestamp

    if (iVar7 == -1) {
        iVar7 = pDesc->field_0x0C; // +0x0C
    }

    fVar2 = *(float*)(thisPtr + 0x78); // timer decrement value
    pfVar6 = (float*)(thisPtr + 0xc0); // array of 16 timers (e.g., channel cooldowns)
    iVar9 = 0x10;
    do {
        if (*pfVar6 < fVar2) {
            *pfVar6 = 0.0f;
        } else {
            *pfVar6 = *pfVar6 - fVar2;
        }
        pfVar6++;
        iVar9--;
    } while (iVar9 != 0);

    *(float*)(thisPtr + 0x78) = 0.0f; // reset timer

    // Validate packet sequence
    cVar5 = FUN_00581b30(thisPtr, iVar7);
    if (cVar5 != '\0') {
        // Packet is valid, process it
        *(int*)(thisPtr + 0x2e0) = *(int*)(thisPtr + 0x18); // save previous state

        if (pDesc->sequence == -1) {
            if ((pDesc->packetType == 4) || (pDesc->packetType == 3)) {
                iVar7 = pDesc->field_0x08; // +0x08
            } else {
                iVar7 = *(int*)(*pDesc->pObject + 0x18); // dereference object's field
            }
        } else {
            iVar7 = pDesc->field_0x0C; // +0x0C
        }
        *(int*)(thisPtr + 0x18) = iVar7; // update state

        fVar13 = (float10)FUN_00586a30(uVar1); // convert timestamp to float

        // Check flag bit 0 in pData+0x0B (byte at offset 0x0B)
        if ((*(byte*)(pData + 0x0B) & 1) != 0) {
            *(int*)(thisPtr + 0x10) |= 0x8000000; // set flag
        }

        *(undefined4*)(thisPtr + 0x1c) = uVar14;
        *(undefined4*)(thisPtr + 0x20) = uVar14;

        if (pDesc->flag == '\0') {
            if (cVar4 != '\0') {
                *(byte*)(slotAddr + 0x70) = 1; // mark slot as used?
            }
            *(int*)(thisPtr + 0x2e8) = iVar8; // update write index
        }

        // Copy 20 ints (80 bytes) from pData to internal buffer at +0x2f4
        piVar11 = pData;
        piVar12 = (int*)(thisPtr + 0x2f4);
        for (iVar7 = 0x14; iVar7 != 0; iVar7--) {
            *piVar12 = *piVar11;
            piVar11++;
            piVar12++;
        }
        *(int**)(thisPtr + 0x2f0) = (int*)(thisPtr + 0x2f4); // pointer to copy

        // Callback if registered
        if (*(void**)(thisPtr + 0x3a4) != (void*)0x0) {
            (*(void(__thiscall*)(int, int*, float, int))(*(int*)(thisPtr + 0x3a4)))
                (*(int*)(thisPtr + 0x3a8), pData, (float)fVar13, pDesc->packetType);
        }

        // Check flag bit 5 in pData+0x0B
        if (((*(byte*)(pData + 0x0B) & 0x20) != 0) && (*(int*)pData > 2) && (*(int*)(pData + 0x0F) != 0)) {
            FUN_00586c00(*(int*)(pData + 0x0F), thisPtr, pData);
        }

        return 1;
    }
    return 0;
}