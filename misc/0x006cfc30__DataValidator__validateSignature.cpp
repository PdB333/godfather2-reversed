// FUNC_NAME: DataValidator::validateSignature

#include <cstdint>

// Represents the vtable structure assumed at offset 0 of this object
struct DataValidatorVTable {
    void* reserved[0x2c / 4]; // up to virtual func at 0x2c
    bool (*isReady)();   // vtable offset 0x2c (virtual function index 11)
    void* reserved2[(0x24 - 0x2c - 4) / 4]; // gap between 0x2c and 0x24? Actually 0x24 < 0x2c, so order is: vtable starts at 0, entries offset 0x24, 0x2c, 0x3c. Better to map by offset.
};

// More precisely, virtual functions at specific offsets:
// offset 0x24: void (*prepareBuffer)(char* buffer); // maybe fill buffer
// offset 0x2c: bool (*isReady)();                  // check if ready
// offset 0x3c: void (*notifyResult)(int result);   // notify result

// But for simplicity, we call through reinterpret_cast.

// Helper to call virtual function by offset
template<typename Func>
inline Func getVFunc(void* obj, uint32_t offset) {
    return reinterpret_cast<Func>((*(void***)obj)[offset / 4]);
}

void __thiscall DataValidator::validateSignature(int* thisPtr, int* inputParams)
{
    // thisPtr: pointer to DataValidator object (class with vtable)
    // inputParams: pointer to array of 4 ints (typically a hash or signature)

    typedef bool (*isReadyFunc)();
    typedef void (*notifyResultFunc)(int);
    typedef void (*prepareBufferFunc)(char*);

    isReadyFunc pIsReady = getVFunc<isReadyFunc>(thisPtr, 0x2c);
    notifyResultFunc pNotify = getVFunc<notifyResultFunc>(thisPtr, 0x3c);
    prepareBufferFunc pPrepare = getVFunc<prepareBufferFunc>(thisPtr, 0x24);

    // Check virtual function: is object ready to validate?
    // +0x2c: bool ready() const
    if (!pIsReady()) {
        // Not ready
        // +0x34 (offset 0xD0) is a flag: m_hasValidHash
        if (thisPtr[0x34] != 0) {
            // If currently has a valid hash, reset it
            FUN_004df600(); // likely some reset/log function
        }
        // +0x35 (offset 0xD4) is m_storedHash
        thisPtr[0x35] = 0;
        // Notify with failure (0)
        pNotify(0);
        return;
    }

    // Object is ready
    if (thisPtr[0x34] != 0) {
        // Already has a stored hash; compare with computed hash of inputParams
        int computedHash = ((inputParams[0] * 0x21 + inputParams[1]) * 0x21 + inputParams[2]) * 0x21 + inputParams[3];
        if (thisPtr[0x35] != computedHash) {
            // Hash mismatch – reset
            FUN_004df600(); // may log or reset validation state
        }
        // If still has valid hash (or after reset it became zero), continue
        if (thisPtr[0x34] != 0) {
            // Hash is still valid after possible reset? Fall through to notify
            pNotify(1);
            return;
        }
    }

    // Invalidate stored hash
    thisPtr[0x35] = 0;

    // Check if inputParams contains known magic numbers or all zeros
    // Magic constants: 0xBABDBBBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911 (as negatives)
    // These might be unused or debug markers
    if (!(inputParams[0] == -0x45245246 && inputParams[1] == -0x41104111 &&
          inputParams[2] == -0x153ea5ab && inputParams[3] == -0x6eeff6ef) &&
        !(inputParams[0] == 0 && inputParams[1] == 0 &&
          inputParams[2] == 0 && inputParams[3] == 0))
    {
        // Not magic: perform full validation
        char buffer[0x200]; // stack buffer, size 0x200? Actually auStack_50 is 48 bytes, but used with 0x1ff
        char tempBuf[28];    // auStack_20, size 28

        // Initialize stack buffer (maybe zero it)
        FUN_00412d90(buffer);

        // Call virtual to prepare something into tempBuf
        pPrepare(tempBuf);

        // Copy inputParams to local array (little endian order maybe)
        int localParams[4];
        localParams[0] = inputParams[0];
        localParams[1] = inputParams[1];
        localParams[2] = inputParams[2];
        localParams[3] = inputParams[3];

        int resultHash = 0;
        int outData = 0;
        uint32_t extra = 0;

        // Decode or transform the input signature into a hash
        // FUN_004df270: signature decoding/hashing, returns some status
        int status = FUN_004df270(&outData, &localParams[0], buffer, 0x1ff, 0, &extra);
        FUN_00414db0(status); // cleanup

        if (outData != 0) {
            // Clear a field at offset 8 of outData structure
            *(int*)(outData + 8) = 0;
        }

        // Extract the final hash from outData structure
        int* pHash = (int*)FUN_00445210(&outData);
        thisPtr[0x35] = *pHash;

        // Post-processing (maybe record or free resources)
        FUN_004df710();

        // Clear a flag byte at offset 0x188
        // Note: this is a byte field within the object
        *((char*)thisPtr + 0x188) = 0;
    }

    // Notify success (1)
    pNotify(1);
}

// External functions (assumed to be defined elsewhere)
void FUN_004df600();   // reset or log validation error
void FUN_00412d90(void* buf);   // initialize buffer
int  FUN_004df270(int* outData, int* input, void* buffer, int maxSize, int flags, uint32_t* extra);
void FUN_00414db0(int status);
void* FUN_00445210(int* outData);  // returns pointer to stored hash value
void FUN_004df710();   // post-validation cleanup