// FUNC_NAME: forwardCallTo_572ac0
void __fastcall forwardCallTo_572ac0(void* param_1, void* param_2, void* param_3, unsigned short param_4, void* param_5, void* param_6, unsigned short param_7)
{
    // Forward call to FUN_00572ac0, discarding param_1 (possibly this pointer) and param_3/param_5
    // The global DAT_00e2b1a4 is passed as the last argument (likely a context or data pointer)
    FUN_00572ac0(param_2, param_4, param_6, param_7, 0, 0, 0, DAT_00e2b1a4);
}