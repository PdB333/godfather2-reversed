// FUNC_NAME: BlendNode::getBlendedPosition
// Address: 0x006cd650
// Role: Computes a blended position from two child objects, weighted by a global factor.

// Global blend factor (likely from config or gameplay tuning)
extern float g_blendFactor; // _DAT_00d5c458

// Helper function: retrieves a 3D vector from an object at the given address.
// The object is expected to have a vector at offset 0x48? (based on subtraction)
void getVectorFromObject(void* obj, float out[3]); // FUN_006ccaa0

class BlendNode {
public:
    // Offsets: +0xC0 = pointer to first child object (e.g., bone A)
    //          +0xC8 = pointer to second child object (e.g., bone B)
    // The child objects have a vector at offset 0x48 from their base.
    void* m_childA; // +0xC0
    void* m_childB; // +0xC8

    // Computes a blended position into 'out' based on the two child positions.
    void __thiscall getBlendedPosition(float out[3]) {
        float vecA[3];
        float vecB[3];

        // Retrieve vector from child A (handle null pointer)
        void* objA = m_childA;
        if (objA != nullptr) {
            objA = (void*)((char*)objA - 0x48); // Adjust to get to the vector data
        }
        getVectorFromObject(objA, vecA);

        // Retrieve vector from child B
        void* objB = m_childB;
        if (objB != nullptr) {
            objB = (void*)((char*)objB - 0x48);
        }
        getVectorFromObject(objB, vecB);

        // Blend: (vecA + vecB) * g_blendFactor
        float factor = g_blendFactor;
        out[0] = (vecA[0] + vecB[0]) * factor;
        out[1] = (vecA[1] + vecB[1]) * factor;
        out[2] = (vecA[2] + vecB[2]) * factor;
    }
};