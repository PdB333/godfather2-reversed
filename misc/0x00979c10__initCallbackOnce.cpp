// FUNC_NAME: initCallbackOnce
void __thiscall initCallbackOnce(int thisObj)
{
    if (((*(uint *)(thisObj + 0x60) >> 2) & 1) == 0)  // check bit 2 (value 4) at +0x60
    {
        registerCallback(thisObj + 0x10, callbackHandler, 1);  // register callback with sub-object at +0x10
        *(uint *)(thisObj + 0x60) |= 4;  // set bit 2 to mark done
    }
}