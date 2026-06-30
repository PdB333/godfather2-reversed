void FUN_00403720(std::uint32_t flags)
{
    if ((flags & 0x00000001u) != 0u) {
        FUN_004086d0(&DAT_01206794);
    }

    if ((flags & 0x00000002u) != 0u) {
        FUN_004086d0(&DAT_01206760);
    }

    if ((flags & 0x00000004u) != 0u) {
        FUN_004086d0(&DAT_01206780);
    }

    if ((flags & 0x00000010u) != 0u) {
        FUN_004086d0(&DAT_01206778);
    }

    if ((flags & 0x00000020u) != 0u) {
        FUN_004086d0(&DAT_012067b4);
    }

    if ((flags & 0x00000040u) != 0u) {
        FUN_004086d0(&DAT_01206768);
    }

    if (static_cast<std::int8_t>(flags) < 0) {
        FUN_004086d0(&DAT_012067a4);
    }

    if ((flags & 0x00000100u) != 0u) {
        FUN_004086d0(&DAT_0120678c);
    }
}