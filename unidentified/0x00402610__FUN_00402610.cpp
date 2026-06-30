uint32_t FUN_00402610(int param_1)
{
    const uint32_t entryValue = FUN_004025a0(param_1);

    if (entryValue != 0) {
        return *reinterpret_cast<const uint32_t*>(entryValue + 0x24);
    }

    return 0xFFFFFFFF;
}