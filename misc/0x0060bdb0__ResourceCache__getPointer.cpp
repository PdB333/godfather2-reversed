// FUNC_NAME: ResourceCache::getPointer
// Address: 0x0060bdb0
// Role: Lazy getter for a cached pointer. Checks a flag at offset 0x1c; if set, calls a virtual method on a factory object (at +0x00) 
// to perform some operation and returns the factory pointer. Otherwise, sets another flag at +0x1d and returns the cached pointer at +0x10.

class ResourceCache {
public:
    void* m_pFactory;      // +0x00: pointer to an object with a vtable
    int padding_0x04[3];   // +0x04 alignment (total 12 bytes)
    void* m_pCachedResult; // +0x10: cached pointer returned in the else branch
    int padding_0x14[2];   // +0x14 alignment (total 8 bytes)
    char m_bUseFactory;    // +0x1c: flag indicating which branch to take
    char m_bFlag;          // +0x1d: set to 1 in the else branch
};

int* __thiscall ResourceCache::getPointer() {
    // Offset 0x1c byte check
    if (this->m_bUseFactory) {
        int* factoryPtr = (int*)this->m_pFactory;   // +0x00
        int dummy = 0;
        // Call vtable function at index 11 (offset 0x2c) on the factory object
        // Parameters: factoryPtr, 0, 0, &dummy, 0x10
        // The function likely performs a specific task and returns the factory pointer
        (*(code**)(*factoryPtr + 0x2c))(factoryPtr, 0, 0, &dummy, 0x10);
        return factoryPtr;
    } else {
        this->m_bFlag = 1;                    // set byte at +0x1d
        return (int*)this->m_pCachedResult;   // return pointer at +0x10
    }
}