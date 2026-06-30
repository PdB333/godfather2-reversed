// FUNC_NAME: ResourcePool::initialize
void __thiscall ResourcePool::initialize(ResourcePool *this)
{
    int primaryHandle;
    int secondaryHandle;
    
    primaryHandle = someAllocateFunction();
    this->mPrimaryHandle = primaryHandle; // +0x10
    secondaryHandle = someOtherAllocateFunction(PTR_DAT_00f1100c); // global pointer argument
    this->mSecondaryHandle = secondaryHandle; // +0x14
    globalInitFunction(); // likely one-time engine init
    this->mCopiedPrimaryHandle = this->mPrimaryHandle; // +0xa4
    primaryHandle = someAllocateFunction();
    this->mExtraHandle = primaryHandle; // +0xa8
    return;
}