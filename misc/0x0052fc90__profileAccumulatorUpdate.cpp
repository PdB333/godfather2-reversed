// FUNC_NAME: profileAccumulatorUpdate

void __fastcall profileAccumulatorUpdate(float* inputData)
{
    float deltaTime = reinterpret_cast<float>(0x00e2b1a4); // global frame delta time (DAT_00e2b1a4)
    float mode = inputData[6];

    if (mode == 0.0f)
    {
        // Accumulator set 0: integrate with dt
        _DAT_01219860 += deltaTime * inputData[0];
        _DAT_01219864 += deltaTime * inputData[1];
        _DAT_01219868 += deltaTime * inputData[2];
        _DAT_0121986c += deltaTime * inputData[3];
        DAT_01219870 += inputData[4];
        DAT_01219874 += inputData[5];
        DAT_01219880 += deltaTime;
    }
    else if (mode == 1.4013e-45f)
    {
        // Exponential moving average (blend) mode
        float alpha = deltaTime / (DAT_012198e0 + deltaTime);
        _DAT_012198c0 = (inputData[0] - _DAT_012198c0) * alpha + _DAT_012198c0;
        _DAT_012198c4 = (inputData[1] - _DAT_012198c4) * alpha + _DAT_012198c4;
        _DAT_012198c8 = (inputData[2] - _DAT_012198c8) * alpha + _DAT_012198c8;
        _DAT_012198cc = (inputData[3] - _DAT_012198cc) * alpha + _DAT_012198cc;
        _DAT_012198d0 = inputData[4] * alpha + (deltaTime - alpha) * _DAT_012198d0;
        _DAT_012198d4 = inputData[5] * alpha + (deltaTime - alpha) * _DAT_012198d4;
        DAT_012198e0 += deltaTime;
    }
    else if (mode == 2.8026e-45f)
    {
        // Accumulator set 2: integrate with dt (different variable group)
        _DAT_01219890 += deltaTime * inputData[0];
        _DAT_01219894 += deltaTime * inputData[1];
        _DAT_01219898 += deltaTime * inputData[2];
        _DAT_0121989c += deltaTime * inputData[3];
        DAT_012198a0 += inputData[4];
        DAT_012198a4 += inputData[5];
        DAT_012198b0 += deltaTime;
    }
}