extern "C" void __thiscall FUN_00453440(void* this_, std::uint32_t param_1)
{
    auto* const self = static_cast<std::uint32_t*>(this_);

    self[1] = 0;
    self[2] = 0;
    self[4] = 0;
    self[3] = 1;
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e317dc);
    self[6] = 0;

    FUN_00452df0(param_1);

    self[9] = 1;
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e318cc);
    self[10] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e318f8);
    self[11] = reinterpret_cast<std::uint32_t>(&LAB_004556a0);
    self[5] = reinterpret_cast<std::uint32_t>(self + 10);
}