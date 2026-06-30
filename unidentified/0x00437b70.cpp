// ControllerManager::processAssignmentPacket
int ControllerManager::processAssignmentPacket()
{
    int* current = *(int**)(this + 0x0C); // +0x0C: current read pointer in packet queue
    int* end = *(int**)(this + 0x08);     // +0x08: end pointer of packet queue

    // Check first packet: must be type 3, or type 4 with validation via FUN_00636850
    if (current >= end || current == nullptr)
        return 0;
    if (*current != 3 && (*current != 4 || !FUN_00636850(&this)))
        return 0;

    // Advance to next packet (assuming each packet is 8 bytes)
    current = (int*)(*(int*)(this + 0x0C) + 8);
    if (current >= end || current == nullptr)
        return 0;
    if (*current != 4 && *current != 3)
        return 0;

    // Now we have two consecutive packets of appropriate types; assign controller
    float playerIndexFloat = FUN_006259b0(this, 1); // likely get assigned player index (0 or 1)
    uint playerIndex = (uint)(playerIndexFloat + 0.5f); // round to nearest integer

    if (playerIndex >= 2)
        return 0;

    char* playerName = FUN_00625a70(this, 2); // get player name string
    if (playerName == nullptr || *playerName == '\0')
        return 0;

    // Check length < 0x40 (64) to fit in slot
    size_t len = strlen(playerName);
    if (len >= 0x40)
        return 0;

    // Access global controller array: at DAT_012233f0, skip 8 byte header, then index * 0x44
    // Slot structure: first 4 bytes are controller pointer (this), next 0x40 bytes are name
    int* slotBase = (int*)(*(int*)DAT_012233f0 + 8 + playerIndex * 0x44);
    slotBase[0] = this; // store this controller object pointer
    strncpy((char*)(slotBase + 1), playerName, 0x3F); // copy name with limit

    FUN_00458cd0(FUN_00437a80); // schedule callback (likely to finalize assignment)
    return 0;
}