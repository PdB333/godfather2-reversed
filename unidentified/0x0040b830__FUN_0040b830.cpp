extern "C" void __fastcall FUN_0040b830(std::uint32_t* self)
{
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f2c0);
    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d0);

    if (*reinterpret_cast<std::uint8_t*>(self + 4) != 0) {
        *reinterpret_cast<std::uint8_t*>(self + 4) = 0;
        FUN_004086d0(&DAT_012069c4);
        FUN_004086d0(&DAT_012069b4);
        FUN_004086d0(&DAT_01206970);
    }

    DAT_01194780 = 0;
    DAT_011947e0 = 0;

    FUN_00408310(&DAT_0120685c);
    FUN_00408310(&DAT_0120680c);
    FUN_00408310(&DAT_01206840);

    self[0x36] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d8);
    self[0x2a] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d8);
    self[0x1e] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d8);
    self[0x11] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d8);
    self[5] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d8);

    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f2d4);

    DAT_01223394 = 0;
    FUN_004083d0();
}