// FUNC_NAME: MediaCodecFactory::getOrCreateCodec
// Address: 0x0044bf90
// Role: Factory method – iterates internal codec list for a specific signature, then either activates an existing codec or allocates a new one based on a handle/magic check.

#include <cstdint>

// Forward declarations (assumed from callees)
void CodecInstance::activate(uint32_t handle); // FUN_004d9a70
void* HandleManager::getObject(uint32_t* outHandle); // FUN_00421170
void* operator new(size_t size); // FUN_009c8e50 (likely allocation)
void* CodecConstructor(void* thisPtr, uint32_t param2, void* manager, void* baseObject); // FUN_0044bb90

class MediaCodecFactory {
public:
    // Offset +0x1c: pointer to array of codec instance pointers
    void** m_codecList;
    // Offset +0x20: number of entries in the codec list (ushort)
    uint16_t m_codecCount;

    // Signature to search for in each codec’s 4th word (offset 0x10 from codec base)
    static const uint32_t kTargetSignature = 0x25c1d427;
    // Magic number expected at offset +8 of the codec’s meta‑structure
    static const int32_t kExpectedMagic = -0xc0deffc; // i.e., 0x3F210004 as signed

    void* getOrCreateCodec(uint32_t param2); // param2 = some identifier (e.g., codec type, format ID)
};

void* MediaCodecFactory::getOrCreateCodec(uint32_t param2) {
    uint32_t index = 0;
    // Local variables used as output buffer for HandleManager::getObject
    uint32_t handleBuf[4] = {0, 0, 0, 0};

    // Step 1: Search the internal codec list for one with matching signature
    if (m_codecCount != 0) {
        void** currentEntry = m_codecList;
        do {
            // Each entry is a pointer to a codec instance
            uint32_t* codecPtr = (uint32_t*)*currentEntry;
            // Check signature at offset 4 words (16 bytes) from codec base
            if (codecPtr[4] == kTargetSignature) {
                // Found – call activation function on the codec’s first word (likely a handle or id)
                if (codecPtr != nullptr) {
                    CodecInstance::activate(codecPtr[0]); // FUN_004d9a70
                }
                break;
            }
            index++;
            currentEntry++;
        } while (index < m_codecCount);
    }

    // Step 2: Obtain a handle to some base object via HandleManager
    // handleBuf is used as an output buffer (FUN_00421170 likely writes 4 uints)
    int32_t baseObject = HandleManager::getObject(handleBuf); // returns pointer or 0

    // Step 3: Validate the base object’s magic number
    if (baseObject == 0) {
        // No base object – fall through to allocate a small codec wrapper
    } else {
        // Check magic at: *(baseObject + 0x18) then +8
        int32_t* metaPtr = *(int32_t**)(baseObject + 0x18);
        if (metaPtr && metaPtr[2] == kExpectedMagic) {
            // Valid – allocate full codec structure (0x18 bytes) and construct it
            void* codecMem = operator new(0x18);
            if (codecMem != nullptr) {
                return CodecConstructor(param2, this, codecMem, baseObject); // FUN_0044bb90
            }
        }
    }

    // Fallback: Allocate a smaller codec wrapper (0xc bytes) with a vtable pointer
    uint32_t* smallCodec = (uint32_t*)operator new(0xc);
    if (smallCodec != nullptr) {
        smallCodec[0] = (uint32_t)&PTR_LAB_00e31248; // vtable
        smallCodec[1] = (uint32_t)this;              // store factory pointer
        smallCodec[2] = param2;                      // store passed identifier
        return smallCodec;
    }

    return nullptr;
}