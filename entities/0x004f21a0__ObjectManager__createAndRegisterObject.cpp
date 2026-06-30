// FUNC_NAME: ObjectManager::createAndRegisterObject
// Address: 0x004f21a0
// Creates an object of size 0x70, initializes it with given parameters, then inserts it into a hash table keyed by objectId.

void* __cdecl createAndRegisterObject(uint objectId, uint unused, uint data1, uint data2, uint data3, uint extraData)
{
    // Hash table key structure (4 uint32s)
    struct HashKey {
        uint id;      // +0x00: object ID
        uint type;    // +0x04: always 2
        uint size;    // +0x08: always 0x10
        uint flags;   // +0x0C: always 0
    } key;

    key.id = objectId;
    key.type = 2;
    key.size = 0x10;
    key.flags = 0;

    // Allocate memory for the object (size 0x70 = 112 bytes)
    void* obj = FUN_009c8ed0(0x70, &key.type);  // allocator, second param is pointer to type info
    if (obj != nullptr) {
        // Set vtable pointer (EA EARS object base)
        *(void**)obj = &PTR_FUN_00e37558;  // vtable

        // Initialize data fields
        *(uint*)((char*)obj + 4) = data1;   // +0x04
        *(uint*)((char*)obj + 8) = data2;   // +0x08
        *(uint*)((char*)obj + 12) = data3;  // +0x0C
        *(uint*)((char*)obj + 0x60) = extraData; // +0x60 (offset 24 * 4)
    }

    // Compute hash: objectId % (hashTableSize)
    // DAT_01223398 points to the global ObjectManager singleton
    // Its member at +8 is a HashTable object, and its member at +8 is the table size (number of buckets)
    int* managerBase = (int*)DAT_01223398;
    int hashTableSize = *(int*)(*(int*)(managerBase + 2) + 2);  // dereference chain
    uint hash = objectId % (uint)hashTableSize;

    // Register the object in the hash table (key, pointer to object, hash)
    FUN_00423cf0(&key, &obj, hash);

    return obj;  // returns the newly created object
}