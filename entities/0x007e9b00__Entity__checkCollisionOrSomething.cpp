// FUNC_NAME: Entity::checkCollisionOrSomething
bool Entity::checkCollisionOrSomething(int* param_1, int param_2)
{
    char cVar1;
    uint uVar2;
    int iVar3;
    int iVar4;
    float10 fVar5;
    undefined8 local_c;
    undefined4 local_4;
    
    // Check if entity type is 4 or has a specific flag (bit 3) set
    if ((*(int *)(param_2 + 0x30) == 4) ||
       (uVar2 = FUN_0084d420(*(int *)(param_2 + 0x30)), (uVar2 & 8) != 0)) {
        local_4 = *(undefined4 *)(param_2 + 0x28);
        local_c = *(undefined8 *)(param_2 + 0x20);
    }
    // Check if entity subtype is 0 or 0x48
    else if ((*(int *)(param_2 + 4) == 0) || (*(int *)(param_2 + 4) == 0x48)) {
        local_4 = *(undefined4 *)(param_2 + 0x1c);
        local_c = *(undefined8 *)(param_2 + 0x14);
    }
    else {
        iVar3 = FUN_00471610();
        local_c = *(undefined8 *)(iVar3 + 0x30);
        local_4 = *(undefined4 *)(iVar3 + 0x38);
    }
    iVar3 = FUN_00471610();
    iVar4 = FUN_00471610();
    fVar5 = (float10)(**(code **)(*param_1 + 0x21c))();
    cVar1 = FUN_007f7f30(&local_c, iVar4 + 0x30, iVar3 + 0x20, (float)fVar5);
    return cVar1 != '\0';
}