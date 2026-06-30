// FUNC_NAME: EARSObject::getTransformAndOffset
void __thiscall EARSObject::getTransformAndOffset(EARSObject *this, uint param_2, float outData[8])
{
    // Stack-based temporary structure (0x28 bytes) used to compute output.
    // Structure layout (offsets from stack base):
    //   -0x40 : this copy (int*)
    //   -0x3c : unused (param_2 copy)
    //   -0x38 : delta (float) – computed but not output
    //   -0x34 : output[0] (float/int? – quaternion w)
    //   -0x30 : output[1] (quaternion x)
    //   -0x2c : output[2] (quaternion y)
    //   -0x28 : output[3] (quaternion z)
    //   -0x24 : output[4] (translation x / scale)
    //   -0x20 : output[5] (translation y)
    //   -0x1c : output[6] (translation z)
    //   -0x18 : output[7] (extra float, e.g. scale or w)
    float tempStruct[10];  // covers entire block starting at -0x40
    // Actually we need more precise, but keep local variables for clarity.

    int *thisCopy;                    // local_40 at -0x40
    unsigned int unusedParam;         // local_3c at -0x3c
    float delta;                      // local_38 at -0x38
    float out0;                       // uStack_34 at -0x34
    float out1;                       // local_30 at -0x30
    float out2;                       // local_2c at -0x2c
    float out3;                       // local_28 at -0x28
    float out4;                       // local_24 at -0x24
    float out5;                       // local_20 at -0x20
    float out6;                       // local_1c at -0x1c
    float out7;                       // local_18 at -0x18

    // Constants – likely a global zero/identity value
    const float baseValue = *(float*)0x00e2b1a4;  // DAT_00e2b1a4, identity translation/scale

    // Pre-fill some fields before calling the virtual method
    out4 = baseValue;
    out7 = baseValue;
    delta = (float)this->field_24 - baseValue;  // this+0x24 (float) minus base

    thisCopy = (int*)this;
    unusedParam = param_2;

    // Virtual call at vtable offset 0x10 – takes a pointer to the temp struct,
    // fills out0..out7 with the oriented box/transform data.
    // The struct passed is likely the entire block starting at &thisCopy.
    (*(void (__thiscall **)(void*))(*(int*)this + 0x10))(&thisCopy);

    // Copy results to output array
    outData[0] = out0;
    outData[1] = out1;
    outData[2] = out2;
    outData[3] = out3;
    outData[4] = out4;
    outData[5] = out5;
    outData[6] = out6;
    outData[7] = out7;
}