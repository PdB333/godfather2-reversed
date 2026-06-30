// FUNC_NAME: ResourceHolder::releaseResources
void __thiscall ResourceHolder::releaseResources(int this) {
    // Release two internal resources stored at offsets +0xd0 and +0xc4
    if (*(int *)(this + 0xd0) != 0) {
        operatorDelete(*(int *)(this + 0xd0));
    }
    if (*(int *)(this + 0xc4) != 0) {
        operatorDelete(*(int *)(this + 0xc4));
    }
}