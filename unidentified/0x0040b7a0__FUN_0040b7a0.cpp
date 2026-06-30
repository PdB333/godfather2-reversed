extern "C" void __fastcall FUN_0040b7a0(std::uint32_t self)
{
    if (*reinterpret_cast<std::uint8_t*>(self + 0x10) == 0) {
        *reinterpret_cast<std::uint8_t*>(self + 0x10) = 1;

        if (DAT_012069c4 != 0) {
            FUN_00407e60(self, &DAT_012069c4);
        }

        if (DAT_012069b4 != 0) {
            FUN_00407e60(self, &DAT_012069b4);
        }

        if (DAT_01206970 != 0) {
            FUN_00407e60(self, &DAT_01206970);
        }
    }
}