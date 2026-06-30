extern "C" void __thiscall FUN_0040b900(std::uint32_t self)
{
    const float value = DAT_00e2b1a4;

    if ((*reinterpret_cast<std::int32_t*>(self + 0x14) != 0) ||
        (*reinterpret_cast<float*>(self + 0x2c) < *reinterpret_cast<float*>(self + 0x18))) {
        if ((*reinterpret_cast<std::uint8_t*>(self + 0x04) != 0) &&
            ((DAT_0110ae74 = 1), (*reinterpret_cast<std::int32_t*>(self + 0x28) == 0) &&
             (DAT_00e2b1a4 <= *reinterpret_cast<float*>(self + 0x08)))) {
            struct
            {
                std::uint32_t field_0;
                std::uint32_t field_4;
                std::uint8_t field_8;
            } local{DAT_01206840, 0, 0};

            FUN_00408a00(&local, 0);
        }

        *reinterpret_cast<std::uint8_t*>(self + 0x04) = 0;
    } else {
        if (*reinterpret_cast<std::uint8_t*>(self + 0x04) == 0) {
            DAT_0110ae74 = 0;
            *reinterpret_cast<std::uint32_t*>(self + 0x08) = 0;
            *reinterpret_cast<std::uint8_t*>(self + 0x04) = 1;
            return;
        }

        const std::int32_t state = *reinterpret_cast<std::int32_t*>(self + 0x28);
        const bool ready = (state == 0) && !(*reinterpret_cast<float*>(self + 0x08) < DAT_00e2b1a4);

        if (state == 0) {
            *reinterpret_cast<float*>(self + 0x08) =
                *reinterpret_cast<float*>(self + 0x08) + DAT_012067e8;
        }

        if (((!ready) && (state == 0)) && (value <= *reinterpret_cast<float*>(self + 0x08))) {
            FUN_00402050(&DAT_0120680c, 0);
            return;
        }
    }

    return;
}