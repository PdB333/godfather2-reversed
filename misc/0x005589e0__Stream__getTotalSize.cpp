// FUNC_NAME: Stream::getTotalSize
int __thiscall Stream::getTotalSize(void) {
    int baseSize = *(int *)(*(int *)((char *)this + 4) + 4); // m_pData->m_baseSize
    int childSize = 0;
    void *child = *(void **)((char *)this + 0x1c); // m_pChild
    if (child != nullptr) {
        void *sizeProvider = *(void **)((char *)child + 0x10); // child->m_sizeProvider
        if (sizeProvider != nullptr) {
            // Virtual call at vtable index 1 (offset 4) on sizeProvider
            childSize = (*(int (__thiscall **)(void *))(*(int *)sizeProvider + 4))(sizeProvider);
        }
    }
    return baseSize + childSize;
}