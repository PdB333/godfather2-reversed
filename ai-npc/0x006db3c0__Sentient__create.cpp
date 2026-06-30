// FUNC_NAME: Sentient::create
// Function address: 0x006db3c0
// Role: Factory method that allocates memory for a Sentient object via the memory manager, then constructs it with an identifier.
// Uses __fastcall calling convention (ecx = identifier).

#include <cstdint>

struct AllocParams {
    uint32_t field_0; // size? (set to 2)
    uint32_t field_4; // alignment? (set to 0x10)
    uint32_t field_8; // flags? (set to 0)
};

// Forward declaration of memory manager interface
class IMemoryManager {
public:
    virtual void* __fastcall Allocate(uint32_t size, AllocParams* params) = 0;
};

// External global function that returns the memory manager singleton
IMemoryManager* __fastcall GetMemoryManager();

// Static function that constructs a Sentient given raw memory and an identifier
// Returns the constructed object pointer (or nullptr on failure)
Sentient* __fastcall Sentient::Construct(void* memory, uint32_t identifier);

Sentient* __fastcall Sentient::create(uint32_t identifier) {
    IMemoryManager* memMgr = GetMemoryManager();

    AllocParams params;
    params.field_0 = 2;
    params.field_4 = 0x10;
    params.field_8 = 0;

    void* memory = memMgr->Allocate(0x1c0, &params);
    if (memory != nullptr) {
        return Sentient::Construct(memory, identifier);
    }
    return nullptr;
}