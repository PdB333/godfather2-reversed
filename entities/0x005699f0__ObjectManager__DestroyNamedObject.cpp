// FUNC_NAME: ObjectManager::DestroyNamedObject

#include <cstdint>
#include <cstring>

// ---------- Global / Forward declarations ----------
extern void* g_GlobalHash;                     // DAT_012233c0
extern void* g_Mutex;                          // DAT_00e2cbe8
void MutexLock(void* mutex);
void MutexUnlock(void* mutex);

// Returns pointer and length of a wide string stored in object+8
void GetObjectName(void* object, const wchar_t*& outStr, int& outLen);

// Looks up a vtable pointer from the global hash using the value at object+0x110
void* GetVTableFromHash(void* globalHash, int hashValue);

// ---------- Internal structures ----------
struct PoolEntry {
    int   unknown0;          // +0x00, unused
    void* object;            // +0x04, pointer to the actual object
};

struct ObjectPool {
    // Layout: pool pointer points to an array of PoolEntry (starting at offset 0)
    // The count of entries is stored at offset 0x104 from the pool pointer.
    // We access it via: *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x104)
    PoolEntry entries[1];    // flexible array member – actual size given by count
};

// ---------- Manager class ----------
class ObjectManager {
public:
    // Assumed offsets:
    // +0x228: array of pool pointers (int* array)
    // +0x328: number of pools
    uintptr_t poolsArray;    // offset +0x228 base address (treated as pointer to array of pool pointers)
    int       poolCount;     // offset +0x328

    void DestroyNamedObject(const wchar_t* name, int nameLength);
};

// ---------- Implementation ----------
void ObjectManager::DestroyNamedObject(const wchar_t* name, int nameLength) {
    MutexLock(g_Mutex);

    if (poolCount != 0) {
        // poolsArray is an array of pool pointers (each 4 bytes)
        // We iterate using an int* that points into this array.
        int* poolPtrIter = reinterpret_cast<int*>(poolsArray);

        for (int poolIdx = 0; poolIdx < poolCount; ++poolIdx) {
            // The current pool pointer is stored as an int (cast to pointer)
            ObjectPool* pool = reinterpret_cast<ObjectPool*>(*poolPtrIter);
            int entryCount = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(pool) + 0x104);

            if (entryCount != 0) {
                // Iterate over all entries in this pool
                int* entryIter = reinterpret_cast<int*>(pool);   // points to the start of the pool's entries array

                for (int entryIdx = 0; entryIdx < entryCount; ++entryIdx) {
                    // Each entry is 2 ints: [unknown, objectPtr]
                    // object is at entryIter[1]
                    void* obj = reinterpret_cast<void*>(entryIter[1]);

                    // Retrieve the name string from the object (object + 8)
                    const wchar_t* objName;
                    int objNameLen;
                    GetObjectName(obj, objName, objNameLen);

                    bool isMatch = false;
                    if (objNameLen == nameLength) {
                        if (nameLength == 0) {
                            isMatch = true;  // both are empty strings
                        } else {
                            // Compare wide-character strings
                            const wchar_t* src = objName;
                            const wchar_t* cmp = name;
                            isMatch = (wcsncmp(src, cmp, nameLength) == 0);
                        }
                    } else {
                        isMatch = false;
                    }

                    // free the temporary string if any (GetObjectName may allocate)
                    // (assume it's freed automatically; not shown in decompile)

                    if (isMatch) {
                        // Found the object – call its destructor or cleanup routine
                        // Look up the vtable from the global hash using the value at obj+0x110
                        int hashKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(obj) + 0x110);
                        void* vtablePtr = GetVTableFromHash(g_GlobalHash, hashKey);
                        // vtable at index 0x18 (3rd function? assuming vtable layout)
                        void (*destroyFunc)(void*) = reinterpret_cast<void (*)(void*)>(*(int*)(vtablePtr) + 0x18);
                        destroyFunc(obj);
                    }

                    // Move to next entry (each entry is 8 bytes = 2 ints)
                    entryIter += 2;   // because each entry is two ints
                }
            }

            // Move to next pool pointer in the array
            poolPtrIter++;
        }
    }

    MutexUnlock(g_Mutex);
}