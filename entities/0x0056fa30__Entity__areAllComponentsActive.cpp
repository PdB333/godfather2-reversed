// FUNC_NAME: Entity::areAllComponentsActive
bool __fastcall Entity::areAllComponentsActive(undefined4 this, int param_2)
{
    bool bVar1;
    
    bVar1 = true;
    if (*(int *)(param_2 + 0x34) != 0) {
        bVar1 = *(char *)(*(int *)(param_2 + 0x34) + 8) == '\0';
    }
    if (*(int *)(param_2 + 0x38) != 0) {
        bVar1 = (bool)(bVar1 & *(char *)(*(int *)(param_2 + 0x38) + 8) == '\0');
    }
    if (*(int *)(param_2 + 0x3c) != 0) {
        bVar1 = (bool)(bVar1 & *(char *)(*(int *)(param_2 + 0x3c) + 8) == '\0');
    }
    if (*(int *)(param_2 + 0x40) != 0) {
        bVar1 = (bool)(bVar1 & *(char *)(*(int *)(param_2 + 0x40) + 8) == '\0');
    }
    if (*(int *)(param_2 + 0x44) != 0) {
        bVar1 = (bool)(bVar1 & *(char *)(*(int *)(param_2 + 0x44) + 8) == '\0');
    }
    return bVar1;
}