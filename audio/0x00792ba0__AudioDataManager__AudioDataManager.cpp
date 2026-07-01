// FUNC_NAME: AudioDataManager::AudioDataManager
// Address: 0x00792ba0
// Role: Constructor for AudioDataManager singleton. Allocates internal pooled buffers for sound data.

// Assumed class definition
class AudioDataManager : public EARSObject {
public:
    // Vtable: +0x0
    // Fields:
    // +0x4: unknown (second vtable pointer or internal pointer)
    // +0x8: m_pSoundIdPool          // pointer to 0x100 byte buffer
    // +0xC: m_soundIdPoolCount      // current count (0)
    // +0x10: m_soundIdPoolCapacity  // max entries = 0x40 (64)
    // +0x14: m_pSoundBankPool       // pointer to 0x80 byte buffer
    // +0x18: m_soundBankPoolCount   // 0
    // +0x1C: m_soundBankPoolCapacity// max = 0x20 (32)
    // +0x20: m_pSampleDataPool      // pointer to 0x400 byte buffer
    // +0x24: m_sampleDataPoolCount  // 0
    // +0x28: m_sampleDataPoolCapacity// max = 0x40 (64)
    // +0x2C: m_pStreamPool          // pointer to 0x400 byte buffer
    // +0x30: m_streamPoolCount      // 0
    // +0x34: m_streamPoolCapacity   // max = 0x40 (64)
    // Total size: 0x38 bytes (56)

    __thiscall AudioDataManager() {
        // Set vtables (typical multiple inheritance or internal interface)
        this->vtable = (void*)&PTR_FUN_00d69dd4;          // primary vtable at +0x0
        this->field_4 = &PTR_LAB_00d69dd0;                // secondary vtable or other

        // Allocate fixed-size pools for sound IDs, bank IDs, sample data, and streams
        this->m_pSoundIdPool      = HeapAlloc(0x100);     // 256 bytes (64 entries of 4 bytes)
        this->m_soundIdPoolCount  = 0;
        this->m_soundIdPoolCapacity = 0x40;                // 64

        this->m_pSoundBankPool    = HeapAlloc(0x80);      // 128 bytes (32 entries of 4 bytes)
        this->m_soundBankPoolCount = 0;
        this->m_soundBankPoolCapacity = 0x20;              // 32

        this->m_pSampleDataPool   = HeapAlloc(0x400);     // 1024 bytes (64 entries of 16 bytes)
        this->m_sampleDataPoolCount = 0;
        this->m_sampleDataPoolCapacity = 0x40;             // 64

        this->m_pStreamPool       = HeapAlloc(0x400);     // 1024 bytes (64 entries of 16 bytes)
        this->m_streamPoolCount   = 0;
        this->m_streamPoolCapacity = 0x40;                 // 64

        // Call base class initializer with zero flag
        FUN_0083c930(this, 0);

        // Store global singleton pointer
        g_pAudioDataManager = this;   // DAT_0112a674
    }

private:
    // External allocation function (likely from custom heap)
    void* HeapAlloc(uint32_t size) {
        // Corresponds to FUN_009c8e80
        return operator new(size);
    }
};

// Global pointer
AudioDataManager* g_pAudioDataManager;  // DAT_0112a674