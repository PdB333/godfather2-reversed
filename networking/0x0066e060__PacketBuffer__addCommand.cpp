// FUNC_NAME: PacketBuffer::addCommand
uint __thiscall PacketBuffer::addCommand(void* thisPtr, uint16_t param2, uint16_t param3, uint16_t param4, uint16_t param5, uint32_t param6, uint32_t param7, uint32_t param8)
{
    // +0x10: Pointer to the active packet buffer (Packet*)
    Packet* packet = *(Packet**)((char*)thisPtr + 0x10);
    CommandSlot* slot;

    // If no active packet or packet command count exceeds capacity, bail
    if ((packet == nullptr) || (packet->commandCount > 0x3FF)) {
        goto exit;
    }

    // Try to reuse an existing slot with matching type and valid count
    slot = (CommandSlot*)packet->slotListHead;
    if (slot == nullptr) {
        goto allocateNewSlot;
    }
    // Reuse condition: slot count is exactly 0x40 (64?) or type mismatch
    if ((slot->count == 0x40) || (slot->type != param1)) {  // param1 is the type, passed via EAX earlier?  Actually in_EAX is used
        slot = nullptr;
        goto allocateNewSlot;
    }
    // continue with existing slot...
    // (falls through)

allocateNewSlot:
    // If we need a new slot, allocate from free list if available
    if (*(uint16_t*)((char*)thisPtr + 8) < 0x90) {  // Free slot count check
        CommandSlot* freeSlot = *(CommandSlot**)((char*)thisPtr + 0x14);
        if (freeSlot != nullptr) {
            // Pop from free list
            *(CommandSlot**)((char*)thisPtr + 0x14) = freeSlot->next;
            *(uint16_t*)((char*)thisPtr + 8) += 1;
            slot = freeSlot;
        }
        // Initialize new slot
        slot->next = 0;
        slot->type = param1; // in_EAX (type)
        slot->field2 = 0;
        slot->count = 0;

        // Insert into packet's command list
        CommandSlot* tail = *(CommandSlot**)((char*)packet + 0x18);
        if (tail == nullptr) {
            packet->head = slot;
        } else {
            tail->next = slot;
        }
        packet->tail = slot;
        packet->totalCommands++;
    }

    if (slot == nullptr) {
        goto exit;
    }

    // Add data to the slot (command entry)
    int oldCount = slot->count;
    slot->count = oldCount + 1;

    // Calculate destination pointer inside slot (each entry is 32 bytes)
    // slot layout: offset 0: next (4), 4: type (4), 8: field2 (4), 12: count (4), then 32-byte entries
    CommandDataEntry* entry = (CommandDataEntry*)((char*)slot + 16 + oldCount * 32);

    // Convert three coordinate pairs using context from thisPtr+0x20
    Context* ctx = (Context*)((char*)thisPtr + 0x20);
    // Each conversion produces two ints (e.g., fixed-point or compressed)
    convertTransform(ctx, param6, &entry->data0);
    convertTransform(ctx, param7, &entry->data1);
    convertTransform(ctx, param8, &entry->data2);

    // Write short fields
    entry->short1 = param2;
    entry->short2 = param3;
    entry->short3 = param4;
    entry->short4 = param5;

    // Increment packet's command entry count
    packet->totalCommandEntries++;

    return 1;
exit:
    return 0;
}