// FUNC_NAME: EARSObject::destroy
// Reconstructed C++ for function at 0x005df3e0. Implements cleanup of two sub-objects and releases two resources.
// Member offsets: this+0x4 -> subObject1, this+0x8 -> resource1, this+0xc -> subObject2, this+0x10 -> resource2
// Virtual function indices: subObject1/2 vtable[1] = release(int), vtable[3] = cleanup()

class EARSObject {
public:
    // Forward declarations of internal types
    struct VTable {
        void (*unknown0)();           // vtable[0]
        void (*release)(void* obj, int flag); // vtable[1]  (offset 0x04)
        void (*unknown2)();           // vtable[2]
        void (*cleanup)();            // vtable[3]  (offset 0x0C)
    };

    // Member variables (based on observed offsets)
    // this+0x04: pointer to a sub-object with its own vtable (subObj1)
    VTable** subObj1;         // +0x04
    // this+0x08: pointer to a resource owned by subObj1
    void* resource1;          // +0x08
    // this+0x0C: pointer to another sub-object (subObj2)
    VTable** subObj2;         // +0x0C
    // this+0x10: pointer to a resource owned by subObj2
    void* resource2;          // +0x10

    void destroy() {
        // Release resource2 through subObj2's vtable[1]
        if (this->resource2 != nullptr) {
            (*((*this->subObj2)[1].release))(this->resource2, 0);
            this->resource2 = nullptr;
        }

        // Clean up subObj2 via its vtable[3]
        (*((*this->subObj2)[3].cleanup))();

        // Release resource1 through subObj1's vtable[1]
        if (this->resource1 != nullptr) {
            (*((*this->subObj1)[1].release))(this->resource1, 0);
            this->resource1 = nullptr;
        }

        // Clean up subObj1 via its vtable[3]
        (*((*this->subObj1)[3].cleanup))();
    }
};