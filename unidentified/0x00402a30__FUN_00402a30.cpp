void FUN_00402a30(uint16_t* param_1)
{
    uint16_t current = *param_1;

    while (current != 0xFFFF) {
        const uint16_t next = (&DAT_01161380)[static_cast<uint32_t>(current) * 4];
        (&DAT_01161380)[static_cast<uint32_t>(current) * 4] = DAT_0110ae8c;
        DAT_0110ae8c = current;
        current = next;
    }

    *param_1 = 0xFFFF;
}