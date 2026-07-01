// FUNC_NAME: NetConnection::allocatePacket
// Function address: 0x008370e0
// Allocates a packet buffer and links it into the connection's packet list.
// Checks flags at +0x84 (bits 3-4) before allocation.
// Uses a custom allocator (FUN_004df330) with size 0x181 (385 bytes).
// The allocated block contains a pointer to the actual packet node at offset 0.
// The packet node has a next pointer at +0x8.
// The list head is stored at +0xdc.

void __fastcall NetConnection::allocatePacket(int thisPtr)
{
    int *pNewBlock;
    int *pListHead;
    int newNode;
    // Local struct used as allocation template (initialized with global data)
    // Size appears to be 0x181 bytes, but only first 64 bytes are shown.
    struct PacketTemplate {
        undefined4 field0;   // +0x00
        undefined4 field4;   // +0x04
        undefined4 field8;   // +0x08
        undefined4 fieldC;   // +0x0C
        undefined4 field10;  // +0x10
        undefined4 field14;  // +0x14
        undefined4 field18;  // +0x18
        undefined4 field1C;  // +0x1C
        undefined4 field20;  // +0x20
        undefined4 field24;  // +0x24
        undefined4 field28;  // +0x28
        undefined4 field2C;  // +0x2C
        undefined4 field30;  // +0x30
        undefined4 field34;  // +0x34
        undefined4 field38;  // +0x38
        undefined4 field3C;  // +0x3C
    } templateData;
    int local_54; // output parameter for allocation

    // Check if flags at +0x84 have bits 3 or 4 set (0x18)
    if ((*(byte *)(thisPtr + 0x84) & 0x18) == 0) {
        // Initialize template with global data and zeros
        templateData.field0 = _DAT_00d5780c;  // global constant
        templateData.field4 = 0;
        templateData.field8 = 0;
        templateData.fieldC = 0;
        templateData.field10 = 0;
        templateData.field14 = _DAT_00d5780c;
        templateData.field18 = 0;
        templateData.field1C = 0;
        templateData.field20 = 0;
        templateData.field24 = 0;
        templateData.field28 = _DAT_00d5780c;
        templateData.field2C = 0;
        templateData.field30 = 0;
        templateData.field34 = 0;
        templateData.field38 = 0;
        templateData.field3C = _DAT_00d5780c;

        // Allocate a new packet block (size 0x181) using custom allocator
        // Parameters: output pointer, size from this+0xc8, template, size, flags, etc.
        pNewBlock = (int *)FUN_004df330(&local_54, thisPtr + 200, &templateData, 0x181, 0, 0, 0xffffffff, 0);

        // Get pointer to list head at +0xdc
        pListHead = (int *)(thisPtr + 0xdc);

        // If list already has a head, clear its next pointer and reset head
        if (*pListHead != 0) {
            *(undefined4 *)(*pListHead + 8) = 0;  // clear next pointer of old head
            *pListHead = 0;                        // reset head to null
        }

        // The allocated block's first field contains the actual node address
        newNode = *pNewBlock;
        *pListHead = newNode;  // set new head

        if (newNode != 0) {
            // Set the new node's next pointer to point to the list head location
            *(int **)(newNode + 8) = pListHead;
            *pNewBlock = 0;  // clear the pointer in the allocated block
        }

        // Cleanup: if local_54 was set, clear its next pointer
        if (local_54 != 0) {
            *(undefined4 *)(local_54 + 8) = 0;
        }

        // Post-allocation cleanup/notification
        FUN_004df890(0);
        FUN_004df5c0();
    }
    return;
}