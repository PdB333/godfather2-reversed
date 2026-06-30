// FUNC_NAME: Animated::updateAttachments
uint __thiscall Animated::updateAttachments(Animated *this, void *rootTransformData) {
    byte count;
    bool toggleFlag;
    uint result;
    void **attachmentIter;
    void *attachment;

    result = (uint)this & 0xffffff00;
    if ((rootTransformData != nullptr) && (this != nullptr)) {
        count = *(byte *)(this + 0x6f);
        toggleFlag = false;
        attachmentIter = (void **)(this + 0xc);
        for (int i = 0; i < count; ++i, ++attachmentIter) {
            attachment = *attachmentIter;
            if ((attachment != nullptr) && (attachment != nullptr)) {
                // Call to transform bone based on root transform and attachment type
                FUN_005dbc10(*(float *)(this + 0x5c), *(float *)(rootTransformData + 0x3c),
                             *(float *)(this + 0x50), *(float *)(rootTransformData + 0x4c),
                             *(byte *)(attachment + 0x1c));

                // Set attachment world position/handle
                *(uint *)(attachment + 0xc) = *(uint *)(rootTransformData + 4);

                // Update internal state
                FUN_005f2680();

                // Conditional clear of a flag based on alternating iteration and some bit
                if (toggleFlag) {
                    if (((*(byte *)(this + 0x6c) & 4) != 0) &&
                        ((*(ushort *)(attachment + 0x10) & 0x100) != 0)) {
                        *(ushort *)(attachment + 0x10) &= 0xfeff;  // Clear bit 8
                        *(byte *)(attachment + 0x1d) = 1;
                    }
                } else {
                    if (((*(byte *)(this + 0x6c) & 4) == 0) &&
                        ((*(ushort *)(attachment + 0x10) & 0x100) != 0)) {
                        *(ushort *)(attachment + 0x10) &= 0xfeff;
                        *(byte *)(attachment + 0x1d) = 1;
                    }
                }

                uint result2 = FUN_005f37b0();
                FUN_005f1400(result2);
            }
            toggleFlag = !toggleFlag;
        }
        // Combine high bytes of the last pointer and a constant 1
        result = ((uint)((uint)attachmentIter >> 8) << 8) | 1;
    }
    return result;
}