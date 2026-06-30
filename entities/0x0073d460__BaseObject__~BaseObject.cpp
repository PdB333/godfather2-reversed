// FUNC_NAME: BaseObject::~BaseObject
// Address: 0x0073d460
// Role: Destructor for a base EA EARS engine object. Sets vtable to base class, destroys sub-objects at offsets 0x68 and 0x70, then calls global cleanup.

#include <cstdint>

// Forward declarations for helper functions
void __fastcall SubObjectDestructor(void* ptr); // 0x004daf90, releases a sub-object
void __fastcall GlobalCleanup(); // 0x0080ea60, performs global engine cleanup

struct BaseObject {
    void** vtable; // +0x00
    // ... other members up to +0x68 ...
    void* subObject1; // +0x68 (offset 0x1a * 4)
    void* subObject2; // +0x70 (offset 0x1c * 4)
    // ... possibly more ...
};

// Destructor
void __fastcall BaseObject::~BaseObject(BaseObject* this) {
    // Switch vtable to first base class (PTR_LAB_00d636bc)
    this->vtable = reinterpret_cast<void**>(0x00d636bc);

    // Destroy sub-object at +0x70 if non-null
    if (this->subObject2 != nullptr) {
        SubObjectDestructor(&this->subObject2);
    }

    // Switch vtable to second base class (PTR_LAB_00d63090)
    this->vtable = reinterpret_cast<void**>(0x00d63090);

    // Destroy sub-object at +0x68 if non-null
    if (this->subObject1 != nullptr) {
        SubObjectDestructor(&this->subObject1);
    }

    // Call global cleanup routine
    GlobalCleanup();
}