// FUNC_NAME: ActionOptions::initOptionValues
void __fastcall ActionOptions::initOptionValues(int this)
{
    undefined4 uVar1;
    
    if ((*(int *)(this + 0x58) == 1) &&
       (*(undefined4 *)(this + 0x54) = 0, *(int *)(this + 0x60) != 0)) {
        do {
            switch(*(undefined4 *)(this + 0x54)) {
            case 0:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x6c);
                break;
            case 1:
                uVar1 = *(undefined4 *)(this + 0x70);
                goto LAB_00987d34;
            case 2:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x74);
                break;
            case 3:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x78);
                break;
            case 4:
                uVar1 = *(undefined4 *)(this + 0x7c);
                goto LAB_00987d34;
            case 5:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x80);
                break;
            case 6:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x84);
                break;
            case 7:
                uVar1 = *(undefined4 *)(this + 0x88);
                goto LAB_00987d34;
            case 8:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x8c);
                break;
            case 9:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x90);
                break;
            case 10:
                uVar1 = *(undefined4 *)(this + 0x94);
                goto LAB_00987d34;
            case 0xb:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x98);
                break;
            case 0xc:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x9c);
                break;
            case 0xd:
                uVar1 = *(undefined4 *)(this + 0xa0);
                goto LAB_00987d34;
            case 0xe:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0xa4);
                break;
            case 0xf:
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0xa8);
                break;
            case 0x10:
                uVar1 = *(undefined4 *)(this + 0xac);
LAB_00987d34:
                *(undefined4 *)(this + 0x68) = uVar1;
            }
            FUN_005a04a0("InitOptionValue",0,&DAT_00d90fa8,0);
            *(int *)(this + 0x54) = *(int *)(this + 0x54) + 1;
        } while (*(uint *)(this + 0x54) < *(uint *)(this + 0x60));
    }
    return;
}