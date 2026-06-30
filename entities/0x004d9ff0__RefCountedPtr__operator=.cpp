// FUNC_NAME: RefCountedPtr::operator=
// Reconstructed assignment operator for a ref-counted smart pointer.
// Address: 0x004d9ff0
// EARS engine internal: deep-copies the managed object if present.

#include <cstdint>

// Forward declarations for internal EA EARS functions.
extern "C" {
    // Decrement reference count (or release) on the managed object.
    // Parameter 1 likely indicates decrement (1) vs. other action.
    void FUN_004d8bc0(int32_t param);

    // Free the managed object's memory.
    void FUN_009c8eb0(void* ptr);

    // Allocate memory (size 0x24 for the managed object).
    void* FUN_009c8e50(int32_t size);

    // Clone the managed object from source. Returns new pointer.
    void* FUN_004d9f80(void* sourceManagedObj);
}

// Size of the managed object (ref-counted data).
constexpr int32_t kManagedObjectSize = 0x24;

// The ref-counted smart pointer itself.
// Layout: [8 bytes data1][4 bytes managedPtr][8 bytes data2][8 bytes data3][4 bytes data4][2 bytes data5]
class RefCountedPtr {
public:
    // Assignment operator (this is the function at 0x004d9ff0).
    void operator=(const RefCountedPtr& other);

private:
    // Raw structure copied from source (except managedPtr is deep-copied).
    // Offsets: +0: data1 (8 bytes)
    //          +4: managedPtr (4 bytes) — pointer to managed object
    //          +8: data2 (8 bytes)
    //         +16: data3 (8 bytes)
    //         +24: data4 (4 bytes)
    //         +28: data5 (2 bytes)
    // Total raw size: 30 bytes (0x1E), padded to 32 probably.
    uint64_t data1_;       // offset +0
    void* managedPtr_;     // offset +4
    uint64_t data2_;       // offset +8
    uint64_t data3_;       // offset +16
    uint32_t data4_;       // offset +24
    uint16_t data5_;       // offset +28
};

void RefCountedPtr::operator=(const RefCountedPtr& other) {
    // This function uses ESI (this) and EDI (&other) in the compiled binary.
    // Prevent self-assignment (though the binary checks ESI != EDI).
    if (this == &other) return;

    // Release the current managed object if it exists.
    if (managedPtr_ != nullptr) {
        // Check a flag at offset +0x20 in the managed object.
        // If non-zero, decrement reference count (or release).
        if (*(reinterpret_cast<int32_t*>(static_cast<uint8_t*>(managedPtr_) + 0x20)) != 0) {
            FUN_004d8bc0(1);                 // decrement ref count
        }
        FUN_009c8eb0(managedPtr_);           // free the object
        managedPtr_ = nullptr;
    }

    // Raw copy of the entire structure (including managedPtr field).
    // This temporarily duplicates the source's pointer.
    // The order matches the binary: copy 8 bytes, 8 bytes, 8 bytes, 4 bytes, 2 bytes.
    *reinterpret_cast<uint64_t*>(this) = *reinterpret_cast<const uint64_t*>(&other);               // offsets 0-7
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 8) = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(&other) + 8);   // offsets 8-15
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 16) = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(&other) + 16); // offsets 16-23
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 24) = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(&other) + 24); // offset 24
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 28) = *reinterpret_cast<const uint16_t*>(reinterpret_cast<const uint8_t*>(&other) + 28); // offset 28

    // Deep-copy the managed object if the source has one.
    if (other.managedPtr_ != nullptr) {
        // Attempt to allocate memory for a clone.
        void* newManaged = FUN_009c8e50(kManagedObjectSize);
        if (newManaged != nullptr) {
            // Clone the source's managed object.
            managedPtr_ = FUN_004d9f80(other.managedPtr_);
        } else {
            // Allocation failed; set pointer to nullptr.
            managedPtr_ = nullptr;
        }
    }
}