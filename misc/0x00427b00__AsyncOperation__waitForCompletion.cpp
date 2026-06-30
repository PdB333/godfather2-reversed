// FUNC_NAME: AsyncOperation::waitForCompletion
// Address: 0x00427b00
// Role: Wait loop for async operation with retry/backoff (up to 300 iterations).
//        Calls a virtual method on an internal delegate object to check completion status.
//        Returns when operation finishes (status 0 or 1), or after timeout.

class AsyncOperation {
public:
    // +0x00: operation state (e.g., 2 = completed, others pending)
    int state;

    // +0x04: padding? (not accessed here)

    // +0x08: some parameter (set to 0x10 on success)
    int internalParam;

    // +0x0C: pointer to delegate object (has vtable)
    class Delegate* delegate;

    // __fastcall: this in ESI, param1 in ECX
    void __fastcall waitForCompletion(int timeoutFlags);
};

// Delegate class (internal interface)
class Delegate {
public:
    // vtable+0x1C: virtual method that checks operation status
    // Returns: 0 = success, 1 = ongoing, other = error
    virtual int __thiscall checkStatus(void* arg, int a, int b) = 0;
};

void __fastcall AsyncOperation::waitForCompletion(int timeoutFlags) {
    int retryCount = 0;

    while (true) {
        // Call delegate to check status
        int status = delegate->checkStatus(delegate + 2, 4, 1);
        int statusCode;
        if (status == 0) {
            statusCode = 1;          // success
        } else {
            if (status == 1) {
                statusCode = 0;      // still running -> treat as failure? Actually 1 leads to fallthrough below
            } else {
                statusCode = (-(status != 1) & 0xFFFFFFFE) + 2; // maps non-1 status to 2
            }
        }
        if (statusCode == 0) {
            // status == 1 -> operation ongoing, retry path
        } else if (statusCode == 1) {
            // status == 0 -> success
            goto success;
        } else {
            // status != 0 && !=1 -> error/other, set retry flag
            timeoutFlags = 1;
            sleepMs(&timeoutFlags);
            retryCount++;
            if (retryCount > 299) {
                return;                // timeout, return without state change
            }
            continue;                  // retry loop
        }
    }

    // Only reached if statusCode == 1 (i.e., status 0) or fallthrough from goto
    internalParam = 0x10;              // mark success parameter

success:
    state = 2;                         // completed state
    return;
}