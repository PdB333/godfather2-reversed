void FUN_00403620(std::uint32_t flags, std::uint32_t param_2, std::uint32_t param_3)
{
    if (((flags & 0x00000001u) != 0u) && (DAT_01206794 != 0)) {
        FUN_00408900(param_2, &DAT_01206794, param_3);
    }

    if (((flags & 0x00000002u) != 0u) && (DAT_01206760 != 0)) {
        FUN_00408900(param_2, &DAT_01206760, param_3);
    }

    if (((flags & 0x00000004u) != 0u) && (DAT_01206780 != 0)) {
        FUN_00408900(param_2, &DAT_01206780, param_3);
    }

    if (((flags & 0x00000010u) != 0u) && (DAT_01206778 != 0)) {
        FUN_00408900(param_2, &DAT_01206778, param_3);
    }

    if (((flags & 0x00000020u) != 0u) && (DAT_012067b4 != 0)) {
        FUN_00408900(param_2, &DAT_012067b4, param_3);
    }

    if (((flags & 0x00000040u) != 0u) && (DAT_01206768 != 0)) {
        FUN_00408900(param_2, &DAT_01206768, param_3);
    }

    if ((static_cast<std::int8_t>(flags) < 0) && (DAT_012067a4 != 0)) {
        FUN_00408900(param_2, &DAT_012067a4, param_3);
    }

    if (((flags & 0x00000100u) != 0u) && (DAT_0120678c != 0)) {
        FUN_00408900(param_2, &DAT_0120678c, param_3);
    }
}