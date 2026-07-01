// Xbox PDB: AptRenderingContext::pushAppendColourTransform
// FUNC_NAME: CXFormStack::pushTransform
void __thiscall CXFormStack::pushTransform(const float* pTransform) // param_1 = pTransform (8 floats: first 4 scale, last 4 offset)
{
    int* pAssertData; // FS-based exception/assert data

    // Debug assertion: check stack depth < max stack size (16)
    if (this->m_stackDepth >= 16) { // offset +0xee (bytes)
        const char* expression = "nCXFormStack < ((int)(sizeof(aCXFormStack) / sizeof(aCXFormStack[0])))";
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_Apt.h";
        unsigned int line = 0x1d6; // 470
        int isCritical = 2;
        // Global flag? If zero, skip assertion
        if (g_AssertEnabled) { // DAT_01128f18
            void* exceptionInfo; // from FS
            // Get the current exception registration record from TLS
            pAssertData = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30) + 0x30);
            unsigned int assertResult = 1;
            if (pAssertData != nullptr) {
                assertResult = pAssertData->vfunc_0x8(&expression, expression);
                // Set global assertion flag if needed
            }
            if (assertResult & 2) {
                g_AssertEnabled = 0;
            }
            if ((pAssertData != nullptr) || (isCritical != 4)) {
                if (!(assertResult & 1) && (isCritical == 0 || isCritical == 1)) {
                    // Trigger debug break
                    ((void (*)(void))0)(); // swi(3) then call
                    return;
                }
            }
        }
    }

    // Push the current transformation onto the stack
    int newDepth = this->m_stackDepth + 1; // new depth index
    // Copy current transform (8 floats) to the new stack slot
    this->m_stackSlots[newDepth * 8 + 0] = this->m_currentTransform[0];
    this->m_stackSlots[newDepth * 8 + 1] = this->m_currentTransform[1];
    this->m_stackSlots[newDepth * 8 + 2] = this->m_currentTransform[2];
    this->m_stackSlots[newDepth * 8 + 3] = this->m_currentTransform[3];
    this->m_stackSlots[newDepth * 8 + 4] = this->m_currentTransform[4];
    this->m_stackSlots[newDepth * 8 + 5] = this->m_currentTransform[5];
    this->m_stackSlots[newDepth * 8 + 6] = this->m_currentTransform[6];
    this->m_stackSlots[newDepth * 8 + 7] = this->m_currentTransform[7];
    // Update stack depth
    this->m_stackDepth = newDepth;

    // Combine the new transform with the current transform
    // Scale: element-wise multiplication of first 4 components
    float s1 = pTransform[1];
    float s2 = pTransform[2];
    float s3 = pTransform[3];
    this->m_currentTransform[0] = pTransform[0] * this->m_currentTransform[0]; // red multiplier
    this->m_currentTransform[1] = s1 * this->m_currentTransform[1];            // green multiplier
    this->m_currentTransform[2] = s2 * this->m_currentTransform[2];            // blue multiplier
    this->m_currentTransform[3] = s3 * this->m_currentTransform[3];            // alpha multiplier

    // Offset: addition of next 4 components
    float o1 = pTransform[5];
    float o2 = pTransform[6];
    float o3 = pTransform[7];
    this->m_currentTransform[4] = pTransform[4] + this->m_currentTransform[4]; // red offset
    this->m_currentTransform[5] = o1 + this->m_currentTransform[5];            // green offset
    this->m_currentTransform[6] = o2 + this->m_currentTransform[6];            // blue offset
    this->m_currentTransform[7] = o3 + this->m_currentTransform[7];            // alpha offset

    // Call global transform changed callback
    g_TransformChangedCallback();
}