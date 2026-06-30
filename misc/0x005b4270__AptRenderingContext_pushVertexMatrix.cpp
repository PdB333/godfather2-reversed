// Xbox PDB: AptRenderingContext::pushVertexMatrix
// FUNC_NAME: VertexMatrixStack::push

// Reconstructed C++ for function at 0x005b4270
// This function pushes the current vertex matrix onto the matrix stack.
// The stack is an array of 16 matrices (each 24 bytes) at +0x238.
// Current matrix is at +0x220.
// Stack index at +0x3bc.
// Assertion checks for overflow; in debug builds the assertion triggers a break.

#include <cstdint>

class VertexMatrixStack {
public:
    // Structure representing a 24-byte vertex matrix (3 × 8 bytes)
    // Layout: row[0] at offset 0, row[1] at 8, row[2] at 16
    struct Matrix24 {
        uint64_t row0; // +0x00
        uint64_t row1; // +0x08
        uint64_t row2; // +0x10
    };

    static const int kMaxStackDepth = 16;

    // Push current matrix onto the stack
    void push() {
        // +0x3bc: current stack depth
        if (m_stackIndex >= kMaxStackDepth) {
            // Assertion message from source:
            // "nVertexMatrixStack < ((int)(sizeof(aVertexMatrixStack) / sizeof(aVertexMatrixStack[0])))"
            if (s_assertEnabled) {
                __debugbreak(); // break on assertion
                return;
            }
        }
        // Copy current matrix (3 × 8 bytes) to stack at current index
        // +0x220: current matrix (m_currentMatrix)
        // +0x238: stack array (aVertexMatrixStack)
        m_stack[m_stackIndex] = m_currentMatrix;
        ++m_stackIndex;
    }

private:
    // Offset 0x000: unknown, but the stack index and current matrix are at fixed offsets
    // We'll declare members at expected offsets; actual class layout may vary
    char _padding[0x220]; // placeholder up to m_currentMatrix

    // +0x220
    Matrix24 m_currentMatrix;

    // +0x238
    Matrix24 m_stack[kMaxStackDepth];

    // +0x3bc
    int32_t m_stackIndex;

    static bool s_assertEnabled; // controls assertion behavior
};

// Static variable to represent the debug flag (DAT_01129029)
bool VertexMatrixStack::s_assertEnabled = true; // default debug on