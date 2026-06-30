// FUNC_NAME: Object::updateOrientation
void __thiscall Object::updateOrientation(Object* thisObj, const float* orientationDelta) // orientationDelta likely from physics or animation

{
    float* quatOut;
    float valX, valY, valZ, valW;
    float negX, negY, negZ, w;          // for conjugate of orientationDelta[0..3]
    float tempBuffer[7];                // 28-byte temp buffer for quaternion multiplication result
    float conjQuat[4];                  // conjugate of orientationDelta quaternion

    // Possibly setup SIMD state (calls to helper that sets zero registers)
    HelperFunction();
    HelperFunction();

    // Compute conjugate of the input quaternion (assuming DAT_00e44564 is 0.0f)
    // Quaternion: orientationDelta[0..3] = (x, y, z, w)
    negX = 0.0f - orientationDelta[0];   // DAT_00e44564 - orientationDelta[0]
    negZ = 0.0f - orientationDelta[2];   // DAT_00e44564 - orientationDelta[2]
    negY = 0.0f - orientationDelta[1];   // DAT_00e44564 - orientationDelta[1]
    w = orientationDelta[3];             // keep w as is
    conjQuat[0] = negX;
    conjQuat[1] = negY;
    conjQuat[2] = negZ;
    conjQuat[3] = w;

    // Multiply current orientation (stored at this+0x10) by the conjugate
    // result stored in tempBuffer, overwriting previous data
    quatOut = (float*)(thisObj + 0x10);  // current orientation quaternion at offset 0x10
    HelperFunction(tempBuffer, &conjQuat, quatOut);  // tempBuffer = conjQuat * quatOut (quaternion product)

    // Add the translation part (orientationDelta[4..7]) to the x,y,z components of the result
    valX = orientationDelta[4];
    valY = orientationDelta[5];
    valZ = orientationDelta[6];
    valW = orientationDelta[7];

    quatOut[0] = valX + quatOut[0];   // add to x
    quatOut[1] = valY + quatOut[1];   // add to y
    quatOut[2] = valZ + quatOut[2];   // add to z
    quatOut[3] = valW + quatOut[3];   // add to w

    // Force w component to zero, effectively making the quaternion pure (rotation only)
    *(int*)(thisObj + 0x1c) = 0;      // interpret as undefined4, set to 0
}