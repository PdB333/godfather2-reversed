extern "C" void FUN_0040a920(undefined4* param_1, undefined4* param_2)
{
    undefined4 uVar1 = param_1[1];
    undefined4 uVar2 = param_1[2];
    undefined4 uVar3 = param_1[3];

    *param_2 = *param_1;
    param_2[1] = uVar1;
    param_2[2] = uVar2;
    param_2[3] = uVar3;
}