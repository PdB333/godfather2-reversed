void FUN_00402920(uint16_t* param_1, uint16_t param_2)
{
    const uint16_t uVar1 = *param_1;
    const uint16_t uVar3 = FUN_004028f0();

    if (uVar3 == 0xFFFF) {
        const uint32_t uVar4 = static_cast<uint32_t>(DAT_0110ae8c);

        if (DAT_0110ae8c != 0xFFFF) {
            const uint16_t uVar2 = (&DAT_01161380)[uVar4 * 4];

            (&DAT_01161380)[uVar4 * 4] = uVar1;
            *reinterpret_cast<uint32_t*>((&DAT_01161384) + uVar4 * 8) = in_EAX;
            *reinterpret_cast<uint16_t*>((&DAT_01161382) + uVar4 * 8) = param_2;
            *param_1 = DAT_0110ae8c;
            DAT_0110ae8c = uVar2;

            return;
        }
    } else {
        *reinterpret_cast<uint16_t*>((&DAT_01161382) + static_cast<uint32_t>(uVar3) * 8) =
            *reinterpret_cast<uint16_t*>((&DAT_01161382) + static_cast<uint32_t>(uVar3) * 8) | param_2;
    }

    return;
}