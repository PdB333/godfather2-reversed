// FUNC_NAME: populateGhostSlotUpdate
// Address: 0x00579870
// Description: Fills a ghost slot update structure based on connection state and slot data.
// Context: Called during packet/replication slot selection in networking code (EARS engine).
// Parameters: 
//   ECX - outInfo (pointer to GhostSlotUpdate output buffer)
//   EDX - slotData (pointer to input slot data)
// Uses global registers: unaff_ESI -> connection, unaff_EDI -> state

struct GhostSlotUpdate {
    int connectionPtr;        // +0x00 (set to connection)
    int slotDataPtr;          // +0x04 (set to slotData input)
    int someTimestampOrSeq;   // +0x08 (from connection->0x18)
    int slotIndex;            // +0x0C (selected slot index)
    int slotId;               // +0x10 (computed slot identifier, -1 if invalid)
    unsigned char flags;      // +0x14 (bit0: repFlag, bit1: state==3)
    int stateOr5;             // +0x18 (state if slotId invalid and state!=0, else 5)
};

void __fastcall populateGhostSlotUpdate(GhostSlotUpdate* outInfo, int* slotData)
{
    // Global state registers (not function parameters)
    void* connection = (void*)unaff_ESI;    // likely NetConnection or GhostManager
    int state = unaff_EDI;                  // current state/flag (0=idle, 3=some mode)

    int* piVar2;               // pointer used for slotId
    int selectedSlotIndex;     // output slot index (outInfo[3])
    int slotId;                // output slot ID (outInfo[4])

    // Fill first three fields
    outInfo->connectionPtr = (int)connection;
    outInfo->slotDataPtr = (int)slotData;
    outInfo->someTimestampOrSeq = *(int*)((char*)connection + 0x18);

    // Determine selectedSlotIndex (outInfo[3])
    if (((slotData[0xb] & 0x20) == 0) || (slotData[0] < 2)) {
        selectedSlotIndex = slotData[5];
    } else {
        selectedSlotIndex = slotData[7];
    }
    outInfo->slotIndex = selectedSlotIndex;

    // Compute slotId (outInfo[4])
    // Check bit9 of connection+0x10 (some flag)
    if ((*(unsigned int*)((char*)connection + 0x10) >> 9) & 1) {
        slotId = -1;
        goto set_slotId;
    }

    // Conditional slot ID selection based on slotData flags and count
    if (((slotData[0xb] & 0x20U) == 0) || (slotData[0] < 3)) {
        if (((slotData[0xb] & 0x20U) != 0) && (slotData[0] == 2)) {
            slotId = slotData[0x10];
            goto set_slotId;
        }
        if (slotData[0xc] == 0) {
            piVar2 = (int*)slotData[0xd];
            goto check_ptr;
        }
        // else fall through to slotId = -1
    } else {
        // bit set and count >= 3
        piVar2 = (int*)slotData[0xe];
check_ptr:
        if (piVar2 != (int*)0x0) {
            slotId = *piVar2;
            goto set_slotId;
        }
    }
    slotId = -1;

set_slotId:
    outInfo->slotId = slotId;

    // Compute flags (outInfo[5]) - byte at offset 0x14
    outInfo->flags = ((slotData[0xb] >> 2) & 1) | (state == 3);

    // Determine stateOr5 (outInfo[6])
    if ((outInfo->slotId != -1) && (state == 0)) {
        outInfo->stateOr5 = 5;
    } else {
        outInfo->stateOr5 = state;
    }

    return;
}