// FUNC_NAME: TNLConnection::buildPacketHeader
// Reconstructed from 0x006414d0
// This function prepares and sends a control packet header (likely ACK or state update) for the TNL connection.
// Accesses fields at offsets +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18, +0x1c from 'this'.
// Uses a pointer table from offset +0x1c (piVar2) which contains connection/packet manager state.

void __thiscall TNLConnection::buildPacketHeader(void)
{
    int* pPacketManager; // pointer to packet manager structure from +0x1c
    int* piVar2;         // copied from pPacketManager
    uint32_t uVar3;
    int iVar4, iVar5;
    int local_14, local_10; // likely reflect actual register usage from earlier calls
    uint32_t* puVar1;

    piVar2 = *(int**)(this + 0x1c); // pointer to packet manager struct (e.g., PacketManager)

    // Copy field_04 into field_08 (maybe sequence number backup)
    *(uint32_t*)(this + 0x08) = *(uint32_t*)(this + 0x04);

    // Packet state/type at +0x14: if already in 'magic' state 0x11f (287), encode/process the next field
    if (*(int*)(this + 0x14) == 0x11f) {
        uVar3 = FUN_00639c70(this + 0x10);  // likely htons(), convert to network byte order
        *(uint32_t*)(this + 0x0c) = uVar3;
    } else {
        // Transition to state 0x11f, saving previous fields
        *(uint32_t*)(this + 0x0c) = *(uint32_t*)(this + 0x14);
        *(uint32_t*)(this + 0x10) = *(uint32_t*)(this + 0x18);
        *(uint32_t*)(this + 0x14) = 0x11f;
    }

    iVar4 = FUN_0063fc10();  // Check connection state (returns 0 if connected, else something)
    if ((iVar4 == 0) && (extraout_ECX != 0x3b)) { // extraout_ECX might be a previous return or register artifact; 0x3b = 59
        iVar5 = FUN_0063f220(); // Get some flag (e.g., reliable flag or ack type)

        // local_14 and local_10 are most likely parameters or return values from earlier registers.
        // Based on usage: local_14 == 0xc indicates a specific packet type (12 decimal)
        if (local_14 == 0xc) {
            // Modify a bitmask in an array indexed by local_10
            puVar1 = (uint32_t*)(*(int*)(*piVar2 + 0xc) + local_10 * 4);
            *puVar1 &= 0xffff803f;  // Clear bits 6-13 (maybe sequence number or window)
            if (iVar5 == 1) {
                // Set bits 1-2 and 3-4 (value 0x1a = 11010 binary)
                *(uint32_t*)(*(int*)(*piVar2 + 0xc) + local_10 * 4) = 
                    (*(uint32_t*)(*(int*)(*piVar2 + 0xc) + local_10 * 4) & 0xffffffda) | 0x1a;
            }
            iVar4 = piVar2[0xd]; // possibly packet sequence number or window mask
            iVar5 = -1;
        } else if (iVar5 == 1) {
            iVar4 = FUN_00642f30(); // Process a special case (maybe reset ack)
        } else {
            FUN_00642ec0(); // Default processing (maybe clear pending ack)
            iVar4 = piVar2[0xd];
        }
    } else {
        iVar5 = 0;
        iVar4 = 0;
    }

    // Construct command word and send packet
    // Command = (iVar5+1)*0x8000 | (iVar4 << 0x18) | 0x1b
    // 0x1b = 27 (likely packet type for control/ack)
    // The second argument is from piVar2[3] + 8 (a buffer or sequence number)
    FUN_006438e0((iVar5 + 1) * 0x8000 | iVar4 << 0x18 | 0x1b, *(undefined4*)(piVar2[3] + 8));
    return;
}