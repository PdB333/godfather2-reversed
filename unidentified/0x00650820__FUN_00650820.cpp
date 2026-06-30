extern "C" void __thiscall FUN_00650820(std::int32_t* this_, std::uint32_t packetArg)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);

    if (*reinterpret_cast<std::int32_t*>(self + 0x210) == 0) {
        FUN_00653080("Invalid packet.");
        return;
    }

    (*reinterpret_cast<void(__thiscall***)(std::int32_t*)>(this_))[0x16](this_);
    FUN_00650930(this_, packetArg);
}