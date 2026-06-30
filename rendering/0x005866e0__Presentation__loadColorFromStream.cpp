// FUNC_NAME: Presentation::loadColorFromStream
void Presentation::loadColorFromStream(undefined4 this, undefined4* stream, float scale)
{
    // +0x00: stream type (byte)
    // +0x08: color data (4 floats)
    // +0x08 (this): pointer to color float[4]
    if (*(char*)stream == 0x02) {
        applyColorScale(scale);  // applies opacity or blend weight
        float* colorDest = *(float**)((char*)this + 8);  // this->color
        float* colorSrc = (float*)&stream[2];             // stream color data
        float r = colorSrc[0];
        float g = colorSrc[1];
        float b = colorSrc[2];
        *colorDest = scale * r;
        colorDest[1] = scale * g;
        colorDest[2] = scale * b;
        colorDest[3] = 1.0f;  // force alpha to 1.0 (DAT_00e2b1a4)
    }
}