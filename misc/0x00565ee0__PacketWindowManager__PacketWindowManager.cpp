// FUNC_NAME: PacketWindowManager::PacketWindowManager

PacketWindowManager* __fastcall PacketWindowManager::PacketWindowManager(PacketWindowManager* this)
{
    // Store global pointer to this manager instance
    g_packetWindowManager = this;

    // Set vtable pointer
    this->vtable = &PacketWindowManager_VTable;

    // Call base or sub-initializer
    FUN_00ae9710();

    // Initialize sequence window: total sent count = 0
    this->totalSentPackets = 0;

    // Set window active flag (byte at offset +0x2012)
    this->windowActive = 1;

    // Set buffer size (typically 0x8000 = 32768 bytes)
    this->bufferSize = 0x8000;

    // Call another initialization function (e.g., reset window)
    FUN_00adbf50();

    // Initialize buffer pointer to start of inline data (just after vtable)
    this->buffer = reinterpret_cast<uint32_t*>(&this[1]); // +0x2004 offset: pointer stored at offset +0x8010

    // Initialize window slot count or something (offset +0x200f)
    this->windowSlotCount = 1;

    return this;
}