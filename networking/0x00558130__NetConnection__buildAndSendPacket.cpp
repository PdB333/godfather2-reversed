// FUNC_NAME: NetConnection::buildAndSendPacket
// Function at 0x00558130: Builds and sends a network packet via the EARS TNL layer.
// This function allocates a packet structure (size 0x2C), initializes it,
// derives source and sequence info from the given packet header, and sends it.
// Returns handle (pointer) to packet on success, 0 on failure.
int __thiscall NetConnection::buildAndSendPacket(void* this, uint packetId, uint flags, PacketHeader* header)
{
    int packetObj;          // iVar1: allocated packet object
    int sendResult;         // iVar5: from connection data
    PacketInitData initData; // local_20: size/type for allocation
    uint sourceId;          // uVar4: derived from flags
    uint packetSeq;         // local_14: sequence number for this packet

    // allocation descriptor for 0x2C bytes, type 2? (Maybe memory pool)
    initData.size = 2;             // local_20 = 2
    initData.alignment = 0x10;     // local_1c = 0x10
    initData.flags = 0;            // local_18 = 0

    // Allocate packet object (0x2C bytes)
    packetObj = allocatorAllocate(0x2C, &initData); // FUN_009c8ed0
    if (packetObj == 0) {
        return 0;
    }

    // Initialize the packet object (constructor)
    packetConstructor(packetObj); // FUN_005582d0

    // Derive source identifier from header flags
    uint headerFlags = header->flags; // param_3[1]
    uint flagCategory = headerFlags & 0xC0000000;

    if (flagCategory == 0) {
        // Use global connection array lookup
        uint index = headerFlags & 0x1F;
        sourceId = *(uint*)(*(int*)(gConnectionManager + 0x54) + 0x34 + index * 4); // DAT_01223480 + 0x54 -> connections table
    }
    else if (flagCategory == 0x40000000) {
        // Use direct pointer from header (low bits indicate source?)
        sourceId = *(uint*)(headerFlags * 4 + 4) | 1;
    }
    else if (flagCategory == 0xC0000000) {
        // Another indexed reference
        sourceId = *(uint*)(headerFlags * 4 + 0x50) | 1;
    }
    else {
        sourceId = 0xFFFFFFFF; // invalid
    }

    // Get system timestamp for packet sequencing (probably low-resolution time)
    uint timestamp = getSystemTimeMs(); // FUN_0043b490
    // Build packet sequence field: combination of timestamp, source ID bits, and constant 0x3E0
    packetSeq = ((timestamp & 0xFFF) << 0x10) | (headerFlags & 0x1F) | 0x3E0;

    // Prepare send parameters (local_c = -1, local_8 = 0, local_4 = 0 seem unused/stub)
    // Call to actually send the packet
    sendPacketInternal(packetObj, header->id, &packetSeq); // FUN_00558020

    // Check if there is pending data in the output queue (offset +0x1C)
    int queueHead = *(int*)(packetObj + 0x1C);
    int queueEntry = 0;
    if (queueHead != 0) {
        queueEntry = *(int*)(queueHead + 0x10); // vtable entry? Maybe function pointer
    }

    // Evaluate if we need to clean up if no data was sent
    int connectionRetVal = *(int*)(*(int*)(packetObj + 4) + 4); // iVar5
    if (queueEntry != 0) {
        // Call vtable function at +0x10(+4) (likely virtual function)
        int vtableRet = (*(code**)(*(int*)(queueEntry + 0x10) + 4))();
        connectionRetVal += vtableRet;
    }

    if (connectionRetVal == 0) {
        // No data to send; abort the packet
        clearPacketData(); // FUN_00558360
        allocatorFree(packetObj); // FUN_009c8eb0
        return 0;
    }

    return packetObj;
}