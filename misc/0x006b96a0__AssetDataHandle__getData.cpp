// FUNC_NAME: AssetDataHandle::getData
// Reconstructed function at 0x006B96A0
// This function retrieves a data pointer from an asset handle.
// The handle contains a 16-byte identifier at offsets +0x54..+0x60.
// If the identifier matches a predefined sentinel, data is already loaded
// and stored as a pointer at +0x50. Otherwise, it attempts to load the data
// via hash lookups and virtual calls.

class AssetDataHandle {
public:
    // Note: Field offsets are guessed based on usage
    // +0x50: pointer to loaded data (void*)
    // +0x54..+0x60: 4-int identifier (possible hash/uid)

    static const int kIdentSentinel0 = 0xBADBABBA;
    static const int kIdentSentinel1 = 0xBEEFBEEF;
    static const int kIdentSentinel2 = 0xEAC15A55;
    static const int kIdentSentinel3 = 0x91100911;

    // __thiscall assumption: this in ECX
    // Actually __fastcall with one param: this in ECX, no second param? Decompiler says fastcall with one param.
    // We'll treat as __thiscall.
    void* __thiscall getData() {
        int* pId = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x54);
        int id0 = pId[0];
        int id1 = pId[1];
        int id2 = pId[2];
        int id3 = pId[3];

        // Check if identifier is the sentinel (already loaded)
        bool isSentinel = (id0 == kIdentSentinel0 && id1 == kIdentSentinel1 &&
                           id2 == kIdentSentinel2 && id3 == kIdentSentinel3);
        bool isZero = (id0 == 0 && id1 == 0 && id2 == 0 && id3 == 0);

        if (!isSentinel && !isZero) {
            // Identifier is non-zero and does not match sentinel – needs loading
            // Attempt to find an object by identifier via hash table
            int* foundObj = reinterpret_cast<int*>(FUN_00446100(pId, 0));
            if (foundObj != nullptr) {
                // Virtual call on foundObj at vtable+0x10
                int localThis = reinterpret_cast<int>(this);
                // The second argument is &localThis? Actual call: (**(code**)(*foundObj + 0x10))(0x6F1D0554, &local_4)
                // local_4 was set to this pointer initially.
                bool success = (*reinterpret_cast<bool(__thiscall*)(void*, int, int*)>(foundObj[4]))(foundObj, 0x6F1D0554, &localThis);
                // After this call, the decompiler references 'unaff_ESI', which is not defined.
                // This may be a side effect of the virtual call or a register that was set by the caller.
                // We'll ignore that branch for now and fall through.
            } else {
                // Alternative lookup method
                int result = FUN_006b95e0(pId, 0x43C8EC5B);
                if (result != 0) {
                    return reinterpret_cast<void*>(FUN_008e9640());
                }
            }
            // Fallthrough if loading did not return early
        }

        // If the sentinel or all zeros, or loading above did not return,
        // check the direct data pointer at +0x50
        void* dataPtr = *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x50);
        if (dataPtr != nullptr) {
            return reinterpret_cast<void*>(FUN_006b0ee0(reinterpret_cast<int>(dataPtr)));
        }
        return nullptr;
    }
};

// Note: The decompiled code uses unaff_ESI which could not be reliably reconstructed.
// The virtual call branch (first lookup) might return data from *unaff_ESI+0x180.
// This reconstruction omits that path. Future analysis of the caller (0x6B9760) may clarify.