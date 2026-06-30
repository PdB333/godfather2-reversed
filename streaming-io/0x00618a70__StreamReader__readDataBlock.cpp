// FUNC_NAME: StreamReader::readDataBlock
undefined4 __thiscall StreamReader::readDataBlock(void) {
    int in_EAX;
    int* piVar1;
    undefined4 uVar2;
    int unaff_ESI; // 'this' register
    undefined1* puVar3;
    int iVar4;
    undefined1 auStack_3c[24];
    undefined1 local_24[36];

    uVar2 = 0;
    if (*(int*)(unaff_ESI + 0x18) == 1) {
        uVar2 = 0x10;
    }
    if ((*(uint*)(unaff_ESI + 0xc) & 2) == 0) {
        piVar1 = *(int**)(in_EAX + 0x14);
        if ((*(uint*)(unaff_ESI + 0xc) & 4) == 0) {
            (**(code**)(*piVar1 + 0x44))(piVar1, *(undefined4*)(unaff_ESI + 0x1c), local_24);
            puVar3 = (undefined1*)0x0;
            piVar1 = (int*)&stack0xffffffbc;
            (**(code**)(**(int**)(in_EAX + 0x14) + 0x4c))(*(int**)(in_EAX + 0x14), *(undefined4*)(unaff_ESI + 0x1c), piVar1, 0, uVar2);
        } else {
            puVar3 = local_24;
            iVar4 = 0;
            (**(code**)(*piVar1 + 0x44))();
            (**(code**)(**(int**)(in_EAX + 0x14) + 0x4c))(*(int**)(in_EAX + 0x14), 0, auStack_3c, 0, uVar2);
            puVar3 = puVar3 + *(int*)(unaff_ESI + 0x1c) * iVar4;
        }
    } else {
        (**(code**)(**(int**)(in_EAX + 0x14) + 0x44))(*(int**)(in_EAX + 0x14), 0, local_24);
        puVar3 = (undefined1*)0x0;
        piVar1 = (int*)&stack0xffffffbc;
        (**(code**)(**(int**)(in_EAX + 0x14) + 0x4c))(*(int**)(in_EAX + 0x14), *(undefined4*)(unaff_ESI + 0x1c), 0, piVar1, 0, uVar2);
    }
    *(undefined1**)(unaff_ESI + 0x44) = puVar3;
    *(int**)(unaff_ESI + 0x28) = piVar1;
    *(int*)(unaff_ESI + 0x2c) = *(int*)(unaff_ESI + 0x40) * (int)piVar1;
    return 1;
}