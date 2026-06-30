// FUNC_NAME: UnknownClass::forwardCallToTarget
void __thiscall UnknownClass::forwardCallToTarget(void* this_, int arg2, int arg3) {
    // +0x4 is a pointer to a delegate/helper object
    // Reorders arguments: passes arg2, this_->field_4, arg3 to the target function
    FUN_00714db0(arg2, *(int*)((char*)this_ + 4), arg3);
}