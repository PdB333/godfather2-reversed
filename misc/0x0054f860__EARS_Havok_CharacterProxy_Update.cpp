// Xbox PDB: EARS::Havok::CharacterProxy::Update
// FUNC_NAME: TtCharacter::update

#include <windows.h>
#include <intrin.h>

#pragma pack(push, 4)
struct ProfilingEntry {
    const char* name;
    unsigned int timestamp;
    unsigned int padding; // align to 12 bytes
};
#pragma pack(pop)

struct ProfilingBlock {
    void* unk00;               // +0x00
    ProfilingEntry* pCurrent;  // +0x04
    ProfilingEntry* pEnd;      // +0x0C
};

extern DWORD g_tlsProfileIndex; // DAT_01139830

// Forward declarations for sub-called functions
extern void FUN_00550a70(void);
extern void CharacterUpdateNormal(TtCharacter* thisPtr, float deltaTime);
extern void CharacterUpdateAlternate(float deltaTime);

class TtCharacter {
public:
    enum Flags {
        kFlagBit4 = 0x10,  // bit 4
        kFlagBit6 = 0x40   // bit 6
    };

    unsigned int m_flags; // offset +0xE4

    void update(float deltaTime);
};

void __thiscall TtCharacter::update(float deltaTime) {
    // Profiling push: mark begin of "TtCharacter Update"
    ProfilingBlock* block = (ProfilingBlock*)TlsGetValue(g_tlsProfileIndex);
    if (block->pCurrent < block->pEnd) {
        block->pCurrent->name = "TtCharacter Update";
        block->pCurrent->timestamp = (unsigned int)__rdtsc();
        ++block->pCurrent;
    }

    // Bit 4 check: trigger special behavior
    if (m_flags & kFlagBit4) {
        FUN_00550a70();
    }

    // Bit 6 selects update path
    if ((m_flags & kFlagBit6) == 0) {
        CharacterUpdateNormal(this, deltaTime);
    } else {
        CharacterUpdateAlternate(deltaTime);
    }

    // Profiling pop: mark end
    block = (ProfilingBlock*)TlsGetValue(g_tlsProfileIndex);
    if (block->pCurrent < block->pEnd) {
        block->pCurrent->name = (const char*)0x00e39c6c; // marker string constant
        block->pCurrent->timestamp = (unsigned int)__rdtsc();
        ++block->pCurrent;
    }
}