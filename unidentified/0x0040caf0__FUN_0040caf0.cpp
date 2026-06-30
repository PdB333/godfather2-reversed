extern "C" void FUN_0040caf0()
{
    int* unaff_ESI; // corresponds to ESI register (caller-provided)

    undefined4* puVar1;

    while ((puVar1 = reinterpret_cast<undefined4*>(*unaff_ESI)) != nullptr) {
        if (reinterpret_cast<undefined4*>(unaff_ESI[1]) == puVar1) {
            unaff_ESI[1] = 0;
        }

        *unaff_ESI = static_cast<int>(puVar1[7]);

        if (puVar1 == nullptr) {
            break;
        }

        // thiscall: puVar1 is expected in ECX, single argument (1)
        reinterpret_cast<void(__thiscall*)(int)>(*reinterpret_cast<void**>(puVar1))(1);
    }

    while (true) {
        puVar1 = reinterpret_cast<undefined4*>(unaff_ESI[2]);
        if (puVar1 == nullptr) {
            return;
        }

        if (reinterpret_cast<undefined4*>(unaff_ESI[3]) == puVar1) {
            unaff_ESI[3] = 0;
        }

        unaff_ESI[2] = static_cast<int>(puVar1[7]);

        if (puVar1 == nullptr) {
            break;
        }

        // thiscall: puVar1 is expected in ECX, single argument (1)
        reinterpret_cast<void(__thiscall*)(int)>(*reinterpret_cast<void**>(puVar1))(1);
    }

    return;
}