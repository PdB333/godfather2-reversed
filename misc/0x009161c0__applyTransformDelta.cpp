// FUNC_NAME: applyTransformDelta
// Address: 0x009161c0
// This function retrieves a transform structure, applies a global delta to its float field,
// and then processes the updated transform. The global delta likely represents time or positional offset.

struct TransformData {
    uint32_t field0;      // +0x00
    float     floatField; // +0x04 (modified by global delta)
    uint32_t field2;      // +0x08
    uint32_t field3;      // +0x0C
};

// External functions
TransformData* getCurrentTransform();        // 0x00950b20
void processTransform(TransformData* pTrans); // 0x0097a8d0

// External globals
extern uint32_t _DAT_00d5780c;   // default field3 when transform exists
extern float     DAT_00d8bbc8;   // delta to apply to floatField

void applyTransformDelta(void)
{
    TransformData localTransform;
    TransformData* pTransform;

    pTransform = getCurrentTransform();

    if (pTransform == nullptr) {
        // If no transform, zero the structure
        localTransform.field0 = 0;
        localTransform.floatField = 0.0f;
        localTransform.field2 = 0;
        localTransform.field3 = 0;
    } else {
        // Copy transform from the current pointer
        localTransform.field0 = pTransform->field0;
        localTransform.floatField = pTransform->floatField;
        localTransform.field2 = pTransform->field2;
        localTransform.field3 = _DAT_00d5780c;  // Use global default for field3
    }

    // Apply global delta to the float field
    localTransform.floatField += DAT_00d8bbc8;

    // Process the updated transform
    processTransform(&localTransform);
}