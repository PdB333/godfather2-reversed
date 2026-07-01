// FUNC_NAME: SomeTimerClass::updateTimer
bool __thiscall SomeTimerClass::updateTimer(int *this, int param_2)
{
    int iVar1;
    int iVar2;
    float fVar3;
    
    // Check if some global flag at DAT_0112aa1c + 0x2c88 is zero
    if (*(int *)(DAT_0112aa1c + 0x2c88) == 0) {
        iVar2 = *this;
        FUN_00788610(param_2);
        return iVar2 == param_2;
    }
    
    iVar1 = FUN_007856f0(*(undefined4 *)(param_2 + 4));
    iVar2 = *this;
    if (iVar2 != param_2) {
        fVar3 = *(float *)(iVar1 + 0xc);  // +0x0C: some time value
    }
    else {
        fVar3 = *(float *)(iVar1 + 8);    // +0x08: some time value
    }
    
    // Subtract time from timer at this[7]
    this[7] = (int)((float)this[7] - fVar3);
    
    // Subtract time from timer at this[8] and clamp to zero
    fVar3 = (float)this[8] - *(float *)(iVar1 + 0x10);  // +0x10: another time value
    this[8] = (int)fVar3;
    if (fVar3 < 0.0) {
        this[8] = 0;
    }
    
    FUN_00788610(param_2);
    
    // If we were comparing the same object and the first pointer is non-null
    if ((iVar2 == param_2) && (*this != 0)) {
        iVar2 = FUN_007856f0(*(undefined4 *)(*this + 4));
        fVar3 = (float)this[7] - *(float *)(iVar2 + 0xc);  // +0x0C: time value
        this[7] = (int)fVar3;
        this[7] = (int)(*(float *)(iVar2 + 8) + fVar3);  // +0x08: time value
    }
    
    return false;
}