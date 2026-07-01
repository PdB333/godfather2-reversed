// FUNC_NAME: SomeContainer::findByParam
int __thiscall SomeContainer::findByParam(int this, undefined4 param)
{
    int result;
    uint index;
    
    index = 0;
    if (*(int *)(this + 0x10) != 0) {
        do {
            result = FUN_0084af80(param);  // likely a comparison function
            if (result != 0) {
                return result;
            }
            index = index + 1;
        } while (index < *(uint *)(this + 0x10));  // +0x10 = count/size
    }
    return 0;
}