// FUNC_NAME: getObjectProperty
unsigned int getObjectProperty(unsigned int handle)
{
    void* pObject = getObjectFromHandle(handle);
    if (pObject != 0) {
        return *(unsigned int*)((int)pObject + 0x88); // +0x88: property (ID, index, etc.)
    }
    return 0xFFFFFFFF;
}