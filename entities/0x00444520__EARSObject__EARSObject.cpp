// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00444520
// Role: Constructor for EARSObject, calls base constructor and optionally performs heap-allocation tracking based on a flag.

class EARSObject {
public:
    // Constructor
    // @param heapAllocated - flag indicating if the object was heap-allocated (1=yes, 0=no)
    __thiscall EARSObject(byte heapAllocated) {
        // Call base class constructor
        baseClassConstructor();

        // If heap-allocated, perform additional setup (e.g., store allocation info)
        if (heapAllocated & 1) {
            heapAllocationHandler(this);
        }

        // Return this pointer (implicit in __thiscall)
        return this;
    }

private:
    void baseClassConstructor(); // 0x00444540
    void heapAllocationHandler(void* obj); // 0x009c8eb0
};