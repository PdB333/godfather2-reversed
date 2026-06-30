std::uint32_t FUN_004037c0()
{
    std::uint32_t flags = static_cast<std::uint32_t>(FUN_00402080(&DAT_01206794) != '\0');

    if (FUN_00402080(&DAT_01206760) != '\0') {
        flags = flags | 0x00000002u;
    }

    if (FUN_00402080(&DAT_01206780) != '\0') {
        flags = flags | 0x00000004u;
    }

    if (FUN_00402080(&DAT_01206778) != '\0') {
        flags = flags | 0x00000010u;
    }

    if (FUN_00402080(&DAT_012067b4) != '\0') {
        flags = flags | 0x00000020u;
    }

    if (FUN_00402080(&DAT_01206768) != '\0') {
        flags = flags | 0x00000040u;
    }

    if (FUN_00402080(&DAT_012067a4) != '\0') {
        flags = flags | 0x00000080u;
    }

    if (FUN_00402080(&DAT_0120678c) != '\0') {
        flags = flags | 0x00000100u;
    }

    return flags;
}