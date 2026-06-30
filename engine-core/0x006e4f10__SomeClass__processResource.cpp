// FUNC_NAME: SomeClass::processResource

class SomeClass {
public:
    // Offset +0x28c4: some data buffer.
    void processResource(BaseObject* baseObj, int handle);
};

class BaseObject {
public:
    // Offset +0x100: pointer to resource manager with vtable.
    ResourceManager* m_pResourceManager;
};

class ResourceManager {
public:
    void** vtable;
    // Vtable entry at +0x10: bool getByHash(uint hash, int& outHandle)
    bool getByHash(uint hash, int& outHandle);
};

// Forward declaration of the helper function (implemented elsewhere)
void processResourceHandle(BaseObject* baseObj, int handle, void* data);

void SomeClass::processResource(BaseObject* baseObj) {
    ResourceManager* resMgr = baseObj->m_pResourceManager;
    int handle = 0;
    // Call vtable method at offset 0x10 (index 4)
    bool found = resMgr->getByHash(0x383225a1, handle);
    if (found && this != nullptr) {
        processResourceHandle(baseObj, handle, reinterpret_cast<char*>(this) + 0x28c4);
    }
}