// FUNC_NAME: Entity::createReferencedObject

// Forward declaration of the interface used as a factory
class IObjectManager {
public:
    virtual ~IObjectManager() = default;
    // vtable offset 0x10: creates or retrieves an object for a given hash
    // outPtr is set to point to the object if successful
    virtual bool createObject(uint32_t objectHash, void*& outPtr) = 0;
};

// This member function accesses a manager at offset 0x100 from the current object,
// calls its virtual createObject with a fixed hash, and writes that hash back into
// the obtained object's first field as a type signature.
void Entity::createReferencedObject() {
    // Offset +0x100: pointer to an object factory/manager
    IObjectManager* manager = *reinterpret_cast<IObjectManager**>(reinterpret_cast<char*>(this) + 0x100);
    const uint32_t objectHash = 0x369ac561;
    void* outPtr = nullptr;

    // Virtual call at manager->vtable[4] (offset 0x10)
    // Passes the hash and the address of the local pointer
    bool success = manager->createObject(objectHash, outPtr);
    // Regardless of success, write the hash to the first DWORD of the output object
    *reinterpret_cast<uint32_t*>(outPtr) = objectHash;
}