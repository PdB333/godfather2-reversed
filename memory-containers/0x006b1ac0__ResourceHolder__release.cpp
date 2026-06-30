// FUNC_NAME: ResourceHolder::release
// Address: 0x006b1ac0
// Role: Releases a resource pointer and zeros out the holder structure.

struct ResourceHolder {
    void* resource;  // +0x00: Pointer to the owned resource
    int field_4;     // +0x04: Possibly a reference count or flags
    int field_8;     // +0x08: Another field to be cleared
};

// Forward declaration of the function called to actually release the resource
void __thiscall releaseResource(void* resource);  // Address: 0x009c8f10

void __thiscall ResourceHolder::release() {
    // Zero out secondary fields first
    this->field_4 = 0;
    // Release the resource pointed to by field_0
    releaseResource(this->resource);
    // Nullify the resource pointer and remaining field
    this->resource = 0;
    this->field_8 = 0;
}