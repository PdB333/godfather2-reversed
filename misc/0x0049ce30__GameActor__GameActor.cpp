// FUNC_NAME: GameActor::GameActor
void __thiscall GameActor::GameActor(void *this, uint32_t param1, uint32_t param2, uint32_t param3,
                                     uint32_t param4, uint32_t param5, uint32_t param6, uint16_t param7)
{
    // Set vtable pointer (known offset +0x00)
    *(void **)this = (void *)&PTR_FUN_00e35238;

    // Call base/sub-object initialization (vtable or other base constructor)
    FUN_0060ffd0(this);

    // Zero out fields at offsets +0xA0 and +0xA4 (size 4 bytes each)
    *(uint32_t *)((uint8_t *)this + 0xA0) = 0;
    *(uint32_t *)((uint8_t *)this + 0xA4) = 0;

    // Store the 16-bit parameter at offset +0xB0
    *(uint16_t *)((uint8_t *)this + 0xB0) = param7;

    // Modify byte at offset +0xB2: clear bit 1, set bit 0 (enable flag)
    uint8_t *flagByte = (uint8_t *)this + 0xB2;
    *flagByte = (*flagByte & 0xFD) | 0x01;

    // Call another constructor or initialization with the first six parameters + an extra undefined (EDX)
    // The last argument is likely a leftover register; passing 0 as placeholder.
    FUN_004bfc80(param1, param2, param3, param4, param5, param6, 0);

    // Call final construction step (e.g., post-init or virtual setup)
    FUN_0049ceb0(this);
}