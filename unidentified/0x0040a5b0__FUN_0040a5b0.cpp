extern "C" std::uint32_t* __thiscall FUN_0040a5b0(std::uint32_t* self, std::uint8_t flags)
{
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f1bc);
    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f1cc);

    FUN_004086d0(&DAT_01206940);

    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f1d0);
    DAT_01223390 = 0;

    FUN_004083d0();

    if ((flags & 1) != 0) {
        FUN_009c8eb0(self);
    }

    return self;
}