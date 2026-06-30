// FUNC_NAME: GameObject::constructor

// Reconstructed constructor at 0x0048c520
// Sets vtable, checks two state flags at offsets +0x0C and +0x0D.
// If both non‑zero, registers an identifier (stored at +0x04) into a global linked list.
// Parameter 'destroyOnFailure' bit 0 triggers destructor call (for placement new failure cleanup).

class GameObject {
public:
    void*     vtable;          // +0x00
    uint32_t  objectId;        // +0x04
    char      unk_08[4];       // +0x08
    char      flag1;           // +0x0C
    char      flag2;           // +0x0D

    // Constructor
    void* __thiscall constructor(uint8_t destroyOnFailure) {
        // Set primary vtable (base class)
        this->vtable = &vtable_00e33814;   // PTR_FUN_00e33814

        // Check if both flags are non‑zero (indicates object is in a registrable state)
        if (this->flag1 != 0 && this->flag2 != 0) {
            uint32_t id = this->objectId;

            // Global registry pointer structure at DAT_01206880 + 0x14
            int* pReg = reinterpret_cast<int*>(DAT_01206880 + 0x14);

            // Write a secondary vtable pointer at current location
            *(void**)(*pReg) = &vtable_01123d3c;   // PTR_LAB_01123d3c
            *pReg += 4;

            // Store the object identifier after the vtable pointer
            *(uint32_t*)(*pReg) = id;
            *pReg += 4;
        }

        // If the lowest bit is set, call destructor (likely for cleanup on allocation failure)
        if (destroyOnFailure & 1) {
            this->destructor();   // FUN_009c8eb0
        }

        return this;
    }

    // Placeholder destructor defined elsewhere
    void __thiscall destructor();
};

// External symbols referenced by this function
extern void* vtable_00e33814;       // Primary vtable
extern void* vtable_01123d3c;       // Secondary vtable for registry entries
extern uintptr_t DAT_01206880;        // Global base address