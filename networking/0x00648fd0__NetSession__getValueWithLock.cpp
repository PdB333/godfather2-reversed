// FUNC_NAME: NetSession::getValueWithLock

#include <windows.h>

// Unknown class, likely a session or manager with thread-safe object retrieval.
// Structure offsets:
//   +0x1B8: pointer to a CRITICAL_SECTION (or similar lock structure)
//   +0x17C: default return value when lookup fails
class NetSession {
public:
    int getValueWithLock(int /* unknown key */) {
        LPCRITICAL_SECTION pLock = *(LPCRITICAL_SECTION*)((char*)this + 0x1B8);
        if (pLock) {
            EnterCriticalSection(pLock);
            // The following increments a reference count stored at offset 8 of the lock
            // (decompiler misinterprets as debug info pointer arithmetic)
            *(int*)((char*)pLock + 8) += 1;
        }

        // Attempt to find an object; returns pointer on success (non-zero)
        int* pObj = findObject(*(int*)((char*)this + 0x1B8 ? ...)); // actual signature unknown
        // Actually: call to FUN_00649040(param_1, param_2)
        pObj = reinterpret_cast<int*>(FUN_00649040(this, param_2));
        if (pObj) {
            // Release the object's reference? (FUN_006492f0())
            releaseObject();
            if (pLock) {
                // Decrement reference count
                *(int*)((char*)pLock + 8) -= 1;
                LeaveCriticalSection(pLock);
            }
            return *(int*)(pObj + 8); // return value at offset 8 of object
        }

        if (pLock) {
            *(int*)((char*)pLock + 8) -= 1;
            LeaveCriticalSection(pLock);
        }
        return *(int*)((char*)this + 0x17C); // default value
    }

private:
    // External helper functions (renamed from FUN_00649040 and FUN_006492f0)
    int* findObject(int key); // returns pointer to some object
    void releaseObject();     // releases object reference

    // Dummy function declarations to make compiler happy
    static void EnterCriticalSection(LPCRITICAL_SECTION);
    static void LeaveCriticalSection(LPCRITICAL_SECTION);
};