// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x006a9bc0
// Role: Destructor for a class of size 0xEC (236 bytes). Calls base destructor then conditionally frees memory if the 'freeFlag' byte has bit 0 set.

// Forward declarations of called functions
void __thiscall BaseClass::~BaseClass(void);
void __thiscall MemoryFree(void* ptr, uint size);

class SomeClass : public BaseClass {
public:
    // Custom destructor with flag to control deallocation
    void __thiscall ~SomeClass(byte freeFlag)
    {
        // Call base class destructor
        BaseClass::~BaseClass();

        // If freeFlag's bit 0 is set, free this object's memory
        if (freeFlag & 1) {
            MemoryFree(this, 0xEC);
        }
    }
};