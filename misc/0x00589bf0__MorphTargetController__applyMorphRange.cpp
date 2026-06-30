//FUNC_NAME: MorphTargetController::applyMorphRange
// Address: 0x00589bf0
// Role: Applies a morph target to a range of vertices, blending byte-scaled deltas into base vertex positions.
// Uses a pseudo-random 64-bit value per vertex to determine which components to blend (0=all three, 1=x, 2=y, 3=z).
// The morph delta buffer stores either 1 byte (single component) or 3 bytes (all components) per vertex.
// Global scale factor DAT_00e445cc (g_morphScale) multiplies the byte delta (0-255) before addition.

#include <cstdint>

// Forward declaration of the 64-bit random generator (likely a compiler intrinsic or global state)
extern uint64_t getRandom64();

class MorphTargetController {
public:
    // Member offsets (relative to this):
    // +0x28: byte* m_morphDeltaPtr;   // current position in morph delta buffer
    // +0x2c: float* m_baseVertexPtr;  // current position in base vertex buffer (3 floats per vertex)
    // +0x34: int32_t m_currentVertexIndex; // current vertex index being processed

    byte* m_morphDeltaPtr;      // +0x28
    float* m_baseVertexPtr;     // +0x2c
    int32_t m_currentVertexIndex; // +0x34

    // Global scale factor for morph deltas
    static constexpr float g_morphScale = DAT_00e445cc; // Replace with actual value from data

    // Apply morph to vertices from m_currentVertexIndex up to endIndex.
    // Vertices before startIndex are skipped (pointers advanced but no output).
    // Output is written to outVertices (3 floats per vertex).
    // __thiscall: this in ECX, outVertices in EAX, startIndex and endIndex on stack.
    void __thiscall applyMorphRange(float* outVertices, int32_t startIndex, int32_t endIndex) {
        int32_t currentIdx = m_currentVertexIndex;

        // Phase 1: Advance pointers for vertices before startIndex (no output)
        while (currentIdx < startIndex) {
            currentIdx = m_currentVertexIndex;
            uint64_t randVal = getRandom64();
            uint32_t lowBits = (uint32_t)(randVal & 3);

            // Advance morph delta pointer: 1 byte if lowBits != 0, else 3 bytes
            if (lowBits != 0) {
                m_morphDeltaPtr += 1;
            } else {
                m_morphDeltaPtr += 3;
            }

            // Advance base vertex pointer by 12 bytes (3 floats)
            m_baseVertexPtr += 3;

            currentIdx++;
            m_currentVertexIndex = currentIdx;
        }

        // Phase 2: Blend and output vertices from startIndex to endIndex
        while (true) {
            if (endIndex <= currentIdx) {
                return;
            }

            currentIdx = m_currentVertexIndex;
            uint64_t randVal = getRandom64();
            uint32_t lowBits = (uint32_t)(randVal & 3);

            byte* morphPtr = m_morphDeltaPtr;
            float* basePtr = m_baseVertexPtr;

            switch (lowBits) {
                case 0: {
                    // Blend all three components: out = base + morph * scale
                    outVertices[0] = (float)morphPtr[0] * g_morphScale + basePtr[0];
                    outVertices[1] = (float)morphPtr[1] * g_morphScale + basePtr[1];
                    outVertices[2] = (float)morphPtr[2] * g_morphScale + basePtr[2];
                    morphPtr += 3;
                    break;
                }
                case 1: {
                    // Blend only X component
                    outVertices[0] = (float)morphPtr[0] * g_morphScale + basePtr[0];
                    outVertices[1] = basePtr[1];
                    outVertices[2] = basePtr[2];
                    morphPtr += 1;
                    break;
                }
                case 2: {
                    // Blend only Y component
                    outVertices[0] = basePtr[0];
                    outVertices[1] = (float)morphPtr[0] * g_morphScale + basePtr[1];
                    outVertices[2] = basePtr[2];
                    morphPtr += 1;
                    break;
                }
                case 3: {
                    // Blend only Z component
                    outVertices[0] = basePtr[0];
                    outVertices[1] = basePtr[1];
                    outVertices[2] = (float)morphPtr[0] * g_morphScale + basePtr[2];
                    morphPtr += 1;
                    break;
                }
            }

            // Advance base vertex pointer by 3 floats
            m_baseVertexPtr = basePtr + 3;
            m_morphDeltaPtr = morphPtr;

            currentIdx++;
            m_currentVertexIndex = currentIdx;
            outVertices += 3;
        }
    }
};