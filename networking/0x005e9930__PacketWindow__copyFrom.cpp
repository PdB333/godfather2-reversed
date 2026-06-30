// FUNC_NAME: PacketWindow::copyFrom
void PacketWindow::copyFrom(const PacketWindow& other)
{
    // Copy first field at offset 0x00
    this->sequence = other.sequence;

    // Copy last field at offset 0x8C (0x23 * 4)
    this->ackField = other.ackField;

    // Copy 32 dwords from offsets 0x04 to 0x80 (1..0x20)
    // This is done in two blocks of 16 dwords each
    for (int i = 0; i < 2; i++)
    {
        // Copy 16 dwords starting from source offset (1 + i*16) to destination offset (1 + i*16)
        // The first element of each block is copied via relative offset, then the rest sequentially
        int destBase = 1 + i * 16;
        int srcBase = 1 + i * 16;
        this->windowSlots[destBase] = other.windowSlots[srcBase];
        for (int j = 1; j < 16; j++)
        {
            this->windowSlots[destBase + j] = other.windowSlots[srcBase + j];
        }
    }

    // Copy fields at offsets 0x84 (0x21 * 4) and 0x88 (0x22 * 4)
    this->field0x21 = other.field0x21;
    this->field0x22 = other.field0x22;
}