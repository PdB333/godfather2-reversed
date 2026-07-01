extern "C" int __fastcall FUN_00658230(
    std::uint16_t* inEAX,
    int param_1,
    int param_2,
    int param_3,
    int param_4)
{
    if (DAT_01205a68 == 2) {
        if (DAT_0120589a != '\0') {
            if ((_DAT_01225d84 & 1U) == 0) {
                _DAT_01225d84 = _DAT_01225d84 | 1U;
                _DAT_01225d78 = "Socket::sendto";
                _DAT_01225d7c = -1;
                _DAT_01225d80 = DAT_01205a84;
                DAT_01205a84 = &DAT_01225d78;
            }

            FUN_0065f6b0(&DAT_01225d78);
            DAT_01205a80 = DAT_01205a80 + 1;

            if ((DAT_01205a7c != 0) && (DAT_01205a7c <= DAT_01205a80)) {
                auto* const pcVar1 = reinterpret_cast<int (*)()>(swi(3));
                const int iVar2 = (*pcVar1)();
                return iVar2;
            }

            if ((DAT_01127d3c == '\0') && (DAT_01127d38 < DAT_01205a6c)) {
                return 0;
            }

            auto* const pcVar1 = reinterpret_cast<int (*)()>(swi(3));
            const int iVar2 = (*pcVar1)();
            return iVar2;
        }
    }
    else if ((DAT_01205a68 == 1) && (DAT_0120589a != '\0')) {
        if ((_DAT_01225d84 & 2U) == 0) {
            _DAT_01225d84 = _DAT_01225d84 | 2U;
            _DAT_01225d6c = "Socket::sendto";
            _DAT_01225d70 = -1;
            _DAT_01225d74 = DAT_01205a84;
            DAT_01205a84 = &DAT_01225d6c;
        }

        FUN_0065f6b0(&DAT_01225d6c);
        FUN_0065fab0();
    }

    if (static_cast<std::uint32_t>(*inEAX) != *reinterpret_cast<std::uint32_t*>(param_1 + 4)) {
        return 1;
    }

    param_1 = 0;
    FUN_00657f80(&param_1);

    const int iVar2 = FUN_00657f00(param_2, param_3, param_1, param_4);

    if (-1 < iVar2) {
        return 0;
    }

    return (iVar2 != 0x2733) + 2;
}