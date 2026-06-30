// FUNC_NAME: ThreadSafeWrapper::synchronizedCall
// Address: 0x00647020
// Role: Thread-safe wrapper that acquires a critical section, increments a lock count, 
//       calls an inner method (FUN_00647070), decrements the count, and releases.

// The class has a pointer to a lock structure at offset 0x4e8.
// The lock structure is assumed to consist of a CRITICAL_SECTION followed by a LONG lockCount.

struct LockObject {
    CRITICAL_SECTION cs;     // +0x00
    LONG lockCount;          // +0x20 (sizeof(CRITICAL_SECTION) on x86 is 0x20)
};

class ThreadSafeWrapper {
public:
    // Offset 0x4e8: pointer to a dynamically allocated LockObject
    LockObject* m_pLock; // +0x4e8

    // Returns the result of the inner call.
    // param_2 is not used in this wrapper (might be a dummy or return value placeholder).
    // param_3, param_4, param_5 are forwarded to the inner method.
    __thiscall undefined4 synchronizedCall(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5) {
        LockObject* lock = m_pLock;  // from this+0x4e8
        if (lock != nullptr) {
            EnterCriticalSection(&lock->cs);
            // Increment lock count (stored after the critical section)
            lock->lockCount++;
        }
        // Call the inner protected method (address 0x00647070)
        undefined4 result = executeInner(this, param_3, param_4, param_5);
        if (lock != nullptr) {
            // Decrement lock count
            lock->lockCount--;
            LeaveCriticalSection(&lock->cs);
        }
        return result;
    }

private:
    // The actual work function (called after acquiring the lock)
    __thiscall undefined4 executeInner(undefined4 param_3, undefined4 param_4, undefined4 param_5);
};