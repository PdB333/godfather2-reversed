// FUNC_NAME: GodfatherGameManager::checkAndInvokeCallback
uint GodfatherGameManager::checkAndInvokeCallback(uint param) // __thiscall, calling function at 0x005e2280
{
    uint thisPtr = (uint)this; // in_EAX at entry

    if (*(char *)(thisPtr + 0x1744) != '\0') { // offset 0x1744: flag indicating some state is active
        thisPtr = FUN_005e2150();               // likely getSomeObject() - returns handle/pointer
        if (thisPtr != 0) {
            uint uVar1 = (**(code **)(*g_funcTable + 0x98))( *(undefined4 *)(thisPtr + 0x1cc), param );
            return uVar1;
        }
    }
    return thisPtr & 0xffffff00; // clear low byte, possibly a status/error code
}