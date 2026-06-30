// FUNC_NAME: BlendMatrix::setBlendFactor

class BlendMatrix {
public:
    float data[11]; // offset 0: 44 bytes (11 floats)
};

// Global constants (from binary)
const float g_initialConstant = *reinterpret_cast<const float*>(0x00e2b1a4); // DAT_00e2b1a4
const float g_oneConstant = *reinterpret_cast<const float*>(0x00e44564);     // DAT_00e44564

void __thiscall BlendMatrix::setBlendFactor(float value, int axis)
{
    float init = g_initialConstant;

    // Initialize diagonal pattern (indices 0,5,10) and clear others
    data[0] = init;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
    data[4] = 0.0f;
    data[5] = init;
    data[6] = 0.0f;
    data[7] = 0.0f;
    data[8] = 0.0f;
    data[9] = 0.0f;
    data[10] = init;

    // Select axis (0, 1, or other). Each case sets four elements:
    // three to value and one to (1 - value) for complement.
    if (axis == 0)
    {
        preTransform();        // FUN_00b99fcb
        data[6] = value;
        postTransform();       // FUN_00b99e20
        data[9] = g_oneConstant - value;
        data[10] = value;
        data[5] = value;
    }
    else if (axis == 1)
    {
        preTransform();        // FUN_00b99fcb
        data[8] = value;
        postTransform();       // FUN_00b99e20
        data[10] = value;
        data[2] = g_oneConstant - value;
        data[0] = value;
    }
    else // axis >= 2 or negative
    {
        preTransform();        // FUN_00b99fcb
        data[1] = value;
        postTransform();       // FUN_00b99e20
        data[0] = value;
        data[4] = g_oneConstant - value;
        data[5] = value;
    }
}