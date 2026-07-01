// FUNC_NAME: TransformDelta::constructDifference
// Address: 0x00835f60
// Role: Constructs a TransformDelta object as the element-wise difference of 5 floats at offset 0x4c from two source objects.
// Called from: FUN_0082b580 (likely a gameplay function needing transform deltas)
// Notes: The source objects may be character transforms or physics states.
// Offsets: +0x4c to +0x5c = 5 floats (position x,y,z? + rotation quaternion w? + scale?).

class TransformDelta {
public:
    // Vtable pointer at offset 0
    void* vtable;

    // Other fields assumed up to offset 0x4c

    // 5 float components starting at offset 0x4c (0x13 * 4)
    float delta0; // +0x4c
    float delta1; // +0x50
    float delta2; // +0x54
    float delta3; // +0x58
    float delta4; // +0x5c

    // Constructor from two source objects (pointers to something with floats at offset 0x4c)
    // The source objects might be of class 'Transform' or 'PhysicsState'
    static TransformDelta* constructDifference(TransformDelta* pThis, void* srcA, void* srcB);
};

// External unknown initializer (likely base class constructor)
extern void FUN_008334a0();

// Global default values (probably identity/zero)
extern float DAT_00e44630; // appears as initial delta3
extern float DAT_00d5ef88; // appears as initial delta0
extern float DAT_00d6471c; // appears as initial delta1
extern float _DAT_00d5cf70; // appears as initial delta2 and delta4 (note same global used twice)

TransformDelta* TransformDelta::constructDifference(TransformDelta* pThis, void* srcA, void* srcB) {
    // Call base class initializer (likely sets vtable and other fields)
    FUN_008334a0();

    // Set vtable pointer
    pThis->vtable = &PTR_LAB_00d7377c;

    // Set default/initial values from global data (likely identity or zero)
    pThis->delta0 = DAT_00d5ef88;
    pThis->delta1 = DAT_00d6471c;
    pThis->delta2 = _DAT_00d5cf70;
    pThis->delta3 = DAT_00e44630;
    pThis->delta4 = _DAT_00d5cf70; // note: same global as delta2? Possibly a bug or intended

    // Overwrite with actual differences between srcA and srcB
    // Each float at offset 0x4c from srcA minus corresponding float from srcB
    pThis->delta0 = *(float*)((char*)srcA + 0x4c) - *(float*)((char*)srcB + 0x4c);
    pThis->delta1 = *(float*)((char*)srcA + 0x50) - *(float*)((char*)srcB + 0x50);
    pThis->delta2 = *(float*)((char*)srcA + 0x54) - *(float*)((char*)srcB + 0x54);
    pThis->delta3 = *(float*)((char*)srcA + 0x58) - *(float*)((char*)srcB + 0x58);
    pThis->delta4 = *(float*)((char*)srcA + 0x5c) - *(float*)((char*)srcB + 0x5c);

    return pThis;
}