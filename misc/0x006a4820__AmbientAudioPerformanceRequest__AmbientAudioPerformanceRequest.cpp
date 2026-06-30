// FUNC_NAME: AmbientAudioPerformanceRequest::AmbientAudioPerformanceRequest
// Function address: 0x006a4820
// Constructor for AmbientAudioPerformanceRequest. Sets up base class, vtable, member flags, and loads audio assets.

class PerformanceRequest; // forward
class AmbientAudioPerformanceRequest;

// External functions (inferred names)
void __thiscall PerformanceRequest::PerformanceRequest(void* allocator); // 0x0046c590
void* __cdecl AssetTable::findAsset(const char* name); // 0x00408240
void __thiscall DataBlock::load(DataBlock* block, void* asset, uint32_t flags); // 0x00408900

// Known global asset pointers
extern void* g_ambientAudioPerfReqAsset; // DAT_0112a534
extern void* g_ambientAudioPerfReq2;     // DAT_0112db74

class AmbientAudioPerformanceRequest {
public:
    // Constructor
    void* __thiscall ctor(void* allocator) {
        // Call base class constructor
        PerformanceRequest::PerformanceRequest(allocator);

        // Set vtable pointer (offset +0x00)
        *reinterpret_cast<void**>(this) = &PTR_FUN_00d5d724; // vtable for AmbientAudioPerformanceRequest

        // Set embedded object vtable pointers
        // offset +0x3C (0xF * 4)
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x3C) = &PTR_LAB_00d5d714;
        // offset +0x48 (0x12 * 4)
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x48) = &PTR_LAB_00d5d710;

        // Initialize byte flags
        // offset +0x50 (as byte)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x50) = 0;
        // offset +0x51 (as byte)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x51) = 0;
        // offset +0x52 (as byte)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x52) = 1;

        // Zero out 4 words (offsets +0x54, +0x58, +0x5C, +0x60)
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x54) = 0;
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x58) = 0;
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x5C) = 0;
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x60) = 0;

        // Look up asset by string name
        g_ambientAudioPerfReqAsset = AssetTable::findAsset("AmbientAudioPerformanceRequest");

        // If asset found, load into embedded DataBlock at offset +0x3C
        if (g_ambientAudioPerfReqAsset != nullptr) {
            DataBlock::load(
                reinterpret_cast<DataBlock*>(reinterpret_cast<uint8_t*>(this) + 0x3C),
                g_ambientAudioPerfReqAsset,
                0x8000 // flags
            );
        }

        // Load second asset if present
        if (g_ambientAudioPerfReq2 != nullptr) {
            DataBlock::load(
                reinterpret_cast<DataBlock*>(reinterpret_cast<uint8_t*>(this) + 0x3C),
                g_ambientAudioPerfReq2,
                0x8000
            );
        }

        return this;
    }
};