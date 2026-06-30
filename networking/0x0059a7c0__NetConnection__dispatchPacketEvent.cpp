// FUNC_NAME: NetConnection::dispatchPacketEvent
void __fastcall NetConnection::dispatchPacketEvent(void *thisPtr)
{
    // +0x08: pointer to packet header
    PacketHeader *header = *(PacketHeader **)((char *)thisPtr + 0x08);

    // Check packet header type (likely expected type == 0x18)
    if (header->type != 0x18) {
        // Error handler: call assertion/logger (stored at static address DAT_01205590 + 4)
        (**(void (__fastcall **)())(*(int *)0x01205590 + 4))();
    }

    // Reconstruct 4-byte object ID from big-endian bytes in header
    uint32_t objectId = (header->byte0 << 24) | (header->byte1 << 16) | (header->byte2 << 8) | header->byte3;

    // Look up object by ID (calls FUN_00599aa0, likely ObjectManager::findById)
    Object *target = FIND_OBJECT_BY_ID(thisPtr, objectId);
    if (target == nullptr) {
        // Object not found, error
        (**(void (__fastcall **)())(*(int *)0x01205590 + 4))();
        return;
    }

    // Dispatch based on sub-type field (+0x14)
    switch (header->subType) {
        case 0:
            // Call virtual function at index 100 (0x64) on target
            target->vtable[100]();
            break;
        case 1:
            // Call virtual function at index 0x4c (76) on target
            target->vtable[76]();
            break;
        default:
            // Unknown sub-type, ignore
            break;
    }
}