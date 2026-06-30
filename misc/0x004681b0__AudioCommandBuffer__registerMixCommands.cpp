// FUNC_NAME: AudioCommandBuffer::registerMixCommands
void AudioCommandBuffer::registerMixCommands() {
    // +0x8: pointer to current stack pointer in command buffer
    // +0x40: pointer to temporary data buffer

    pushCommandName("SetMixValues");
    // Write a null marker and advance stack pointer by 8 bytes
    *reinterpret_cast<void**>(*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8)) = nullptr;
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) += 8;

    // Record the temporary data block (size 8 bytes) from stackPtr-0x10 to stackPtr-8
    int iVar1 = reinterpret_cast<int>(this) + 0x40;
    int stackPtr = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8);
    pushTempBlock(iVar1, stackPtr - 0x10, stackPtr - 8);
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) -= 0x10;

    pushCommandName("ApplyMix");
    *reinterpret_cast<void**>(*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8)) = nullptr;
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) += 8;

    stackPtr = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8);
    pushTempBlock(iVar1, stackPtr - 0x10, stackPtr - 8);
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) -= 0x10;

    pushCommandName("RemoveMix");
    *reinterpret_cast<void**>(*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8)) = nullptr;
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) += 8;

    stackPtr = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8);
    pushTempBlock(iVar1, stackPtr - 0x10, stackPtr - 8);
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) -= 0x10;

    pushCommandName("SetMasterVolume");
    *reinterpret_cast<void**>(*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8)) = nullptr;
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) += 8;

    stackPtr = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8);
    pushTempBlock(iVar1, stackPtr - 0x10, stackPtr - 8);
    *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 8) -= 0x10;
}