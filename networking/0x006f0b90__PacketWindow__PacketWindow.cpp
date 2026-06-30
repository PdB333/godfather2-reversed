// FUNC_NAME: PacketWindow::PacketWindow
void __fastcall PacketWindow::PacketWindow(PacketWindow *this)
{
    int *pBuffer = reinterpret_cast<int *>(this + 1); // offset +0x04, pointer to allocated buffer

    this->mSequence = 0;          // offset +0x00
    if (*pBuffer != 0) {
        freeBuffer(pBuffer);      // FUN_004daf90 – deallocate buffer
        *pBuffer = 0;
    }

    this->mNextSendSeq = 0;       // offset +0x0C
    this->mAckSeq = 0;            // offset +0x10

    // Get default window descriptor (static global)
    PacketWindowDesc *pDefaultDesc = getDefaultWindowDesc(0, 0); // FUN_006fbc40

    // If the default descriptor is not stored inline at this+0x14, copy it
    if (this + 5 != pDefaultDesc) {
        this->mWindowSize = pDefaultDesc->size;    // offset +0x14
        this->mMask = pDefaultDesc->mask;           // offset +0x18
    }

    initWindowFlags();           // FUN_006fbc70

    this->mState = 0;            // offset +0x24 (int, e.g., state flags)
    this->mFlags.byte0 = 0;      // offset +0x28 (byte)
    this->mFlags.byte1 = 0;      // offset +0x29 (byte)
}