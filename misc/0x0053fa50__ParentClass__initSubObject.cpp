// FUNC_NAME: ParentClass::initSubObject
// Function at 0x0053fa50: Allocates a sub-object of size 0xa20, optionally creates a GUID-based identifier, and stores it at parent+0x1c.
// Parent class has a member at offset 0x1c (SubObject pointer).
// SubObject structure: vtable at +0x00, fields at +0xa18 and +0xa1c, total size 0xa20.

#include <cstddef>

// Forward declarations for external functions used
extern void* __cdecl _aligned_malloc(size_t size, size_t alignment);
extern void globalInitAllocator();                  // FUN_00aa19a0
extern void* allocateMemory(size_t size);           // FUN_009c8e50 – returns pointer or 0
extern unsigned int convertToGUID(void* buffer);    // FUN_004b4d10 – returns GUID (unsigned int)
extern void finalizeInit();                         // FUN_0053fb10

// Sub-object structure (size 0xa20)
struct SubObject {
    void** vtable;           // +0x00
    // ... internal data (0xa18 bytes)
    int field_0xa18;         // +0xa18
    int field_0xa1c;         // +0xa1c
};

// Assuming parent class is unknown; this is a member function called with this in ECX and a flag in EAX.
// __thiscall: this passed in ECX, param2 (bool) passed in EAX per custom convention.
class ParentClass {
public:
    // Member at offset 0x1c: pointer to SubObject
    SubObject* subObject;   // +0x1c (actually offset 0x1c in parent object)

    // Called with this in ECX, bCreateGUIDFlag in EAX (0 or 1)
    void initSubObject(int bCreateGUIDFlag);
};

void ParentClass::initSubObject(int bCreateGUIDFlag)
{
    // 1. Allocate aligned memory for sub-object (0xa20 bytes, alignment 0x10)
    SubObject* newSubObject = static_cast<SubObject*>(_aligned_malloc(0xa20, 0x10));
    
    if (newSubObject != nullptr) {
        // 2. Global allocator initialization (may set up heap)
        globalInitAllocator();
        
        // 3. Set vtable pointer for sub-object
        newSubObject->vtable = (void**)0x00e444d0;   // PTR_FUN_00e444d0
        
        // 4. Initialize fields (defaults)
        newSubObject->field_0xa18 = 0;
        newSubObject->field_0xa1c = 0;
        
        // 5. If flag is non-zero, allocate additional small object (0x48 bytes) and generate GUID
        if (bCreateGUIDFlag != 0) {
            void* smallBuffer = allocateMemory(0x48);   // FUN_009c8e50(0x48)
            if (smallBuffer != nullptr) {
                unsigned int guid = 0;
                // Local buffer for GUID conversion (stack variable)
                void* guidBuffer[3] = {0, 0, 0};
                // Convert to GUID and store at +0xa1c
                guid = convertToGUID(guidBuffer);       // FUN_004b4d10(&guidBuffer)
                newSubObject->field_0xa1c = guid;
                // Link sub-object to parent
                this->subObject = newSubObject;
                finalizeInit();                         // FUN_0053fb10
                return;
            }
            // Allocation failed: set field to 0
            newSubObject->field_0xa1c = 0;
        }
        // Link and finalize (flag was 0 or small alloc failed)
        this->subObject = newSubObject;
        finalizeInit();                                 // FUN_0053fb10
        return;
    }
    
    // Parent pointer is set even if malloc failed (null pointer)
    this->subObject = newSubObject;   // nullptr
    finalizeInit();
}