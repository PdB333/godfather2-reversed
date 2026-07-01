// FUNC_NAME: AudioDataManager::~AudioDataManager
int __thiscall AudioDataManager::~AudioDataManager(void *this, byte flags)
{
    int iVar1;

    // +0x6c: pointer to audio resource object
    // +0x58: pointer to another resource container
    // +0x4c: pointer to a sub-resource
    
    FUN_0096abb0();  // base destructor / cleanup
    FUN_009c8f10(*(undefined4 *)((int)this + 0x6c));  // release resource at +0x6c
    
    iVar1 = *(int *)((int)this + 0x58);
    if (iVar1 != 0) {
        FUN_009c8f10(*(undefined4 *)(iVar1 + 8));  // release sub-resource at container+8
        FUN_009c8eb0(iVar1);  // release container itself
    }
    
    if (*(int *)((int)this + 0x4c) != 0) {
        FUN_009c8f10(*(int *)((int)this + 0x4c));  // release resource at +0x4c
    }
    
    FUN_005c16e0();  // global cleanup
    
    if ((flags & 1) != 0) {
        FUN_005c4480(this);  // operator delete
    }
    
    return (int)this;
}