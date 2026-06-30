// FUNC_NAME: TransformCache::updateSlot
// Address: 0x0057d140
// This function updates a single entry in a transform cache based on a bitmask.
// The entry is either cleared (if bit not set) or populated from a computed transform.
// It also resets state for all active slots up to the current index.

// Constants from the game binary
static const float kMaxDistSq = 0.0f; // DAT_00e2b1a4 - replaced with actual value? Not known
static const float kSomeOffset = 0.0f; // DAT_00e44564

// Dummy forward declarations for called functions (assumed to be member functions or global)
void FUN_0057c010(); // Possibly reset/clear a slot
void FUN_0057cd80(int param1, int param2, int* output, float* transform); // Get transform/position

class TransformCache {
public:
    float* m_pBuffer;       // +0x00 : pointer to array of 8-float entries (transform data)
    // +0x04 : unknown (maybe byte flags)
    // +0x08 : unknown
    // +0x0C : unknown
    uint* m_pBitmaskArray;  // +0x0C : pointer to array of bitmasks (uint) for slot activity
    int m_nSlotCount;       // +0x10 : number of slots? (used in loop)
    uint m_nCurrentIndex;   // +0x14 : current slot index to update

    void updateSlot() {
        uint* bitmaskArray = reinterpret_cast<uint*>(m_pBitmaskArray);
        uint currentIndex = m_nCurrentIndex;

        // Check if the bit for the current index is set in the bitmask array
        if ((bitmaskArray[currentIndex >> 5] & (1 << (currentIndex & 0x1F))) != 0) {
            // The slot is active: clear/reset all previous active slots
            for (uint i = 0; i < currentIndex; ++i) {
                if ((bitmaskArray[i >> 5] & (1 << (i & 0x1F))) != 0) {
                    // Seven calls to reset function (likely clears slot state)
                    // This might be unrolled or a loop in the original code
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                    FUN_0057c010();
                }
            }

            // Get the transform data for this slot (e.g., world position/rotation)
            int dummy = 0;
            float transform[11]; // local_30, but only first 8 floats are used
            FUN_0057cd80(0, 0, &dummy, transform);

            // Compute squared distance of the first 3 components (position?)
            float distSq = transform[0] * transform[0] + transform[1] * transform[1] + transform[2] * transform[2];
            float result;
            if (distSq >= kMaxDistSq) {
                result = 0.0f;
            } else {
                result = sqrt(kMaxDistSq - distSq);
            }

            // If the fourth component (transform[3]) is non-zero, adjust the result
            if (transform[3] != 0.0f) {
                result = kSomeOffset - result;
            }

            // Store the result into the transform array (overwrites the fourth component)
            transform[3] = result;

            // Copy the 8-float entry from the computed transform to the buffer
            // The copy is conditional on a byte flag (pcVar7), but due to loop structure it always copies once.
            // The original code may have iterated over multiple entries, but here we only have one.
            float* dest = m_pBuffer;
            float* src = transform;
            // The loop would run exactly once because dest pointer is incremented by 8 and compared to end
            // For safety, we copy the 8 floats directly.
            for (int i = 0; i < 8; ++i) {
                dest[i] = src[i];
            }

            // Return value is a weird construct; likely a boolean or status. We'll return true.
            // In the original, it returns CONCAT31((int3)((uint)dest >> 8),1) which is always 1?
            // Based on the code, we'll just return true.
            return; // true
        } else {
            // Slot is not active: clear the buffer entry
            float* buffer = m_pBuffer;
            buffer[0] = 0.0f;
            buffer[1] = 0.0f;
            buffer[2] = 0.0f;
            buffer[3] = kMaxDistSq; // Initialize with the constant
            buffer[4] = 0.0f;
            buffer[5] = 0.0f;
            buffer[6] = 0.0f;
            buffer[7] = kMaxDistSq;

            // Return value likely false or 0 in this case
            return; // false
        }
    }
};