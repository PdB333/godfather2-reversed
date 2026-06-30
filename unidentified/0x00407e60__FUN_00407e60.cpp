extern "C" void __thiscall FUN_00407e60(void* param_1, int* param_2)
{
    static_cast<void>(param_1);

    ++reinterpret_cast<std::int16_t*>(param_2)[2];

    if (auto* node = FUN_00407da0(); node != nullptr) {
        std::uint16_t& value = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(node) + 0x14);
        value = static_cast<std::uint16_t>(
            ((((static_cast<std::int16_t>(static_cast<int>(static_cast<unsigned int>(value) * 2) >> 1) + 1U) ^ value) & 0x7fff) ^ value)
        );
        return;
    }

    FUN_004084d0(param_2, 0x8000);
}