// FUNC_NAME: VehicleMessage::create_various_parameters
void __thiscall createVehicleMessage(uint this, uint param_2, uint param_3, uint param_4, uint param_5, uint param_6, uint param_7, uint param_8, uint param_9)
{
    char cVar1;
    int iVar2;

    cVar1 = FUN_00481660();
    if (cVar1 != '\0') {
        iVar2 = FUN_009c8e50(0x58);
        if (iVar2 == 0) {
            iVar2 = 0;
        } else {
            iVar2 = FUN_008a8e40(this);
        }
        *(uint *)(iVar2 + 0x3c) = param_3;
        *(uint *)(iVar2 + 0x44) = param_5;
        *(uint *)(iVar2 + 0x40) = param_4;
        *(uint *)(iVar2 + 0x4c) = param_7;
        *(uint *)(iVar2 + 0x48) = param_6;
        *(uint *)(iVar2 + 0x54) = param_9;
        *(uint *)(iVar2 + 0x50) = param_8;
        FUN_00481690(iVar2);
    }
    return;
}