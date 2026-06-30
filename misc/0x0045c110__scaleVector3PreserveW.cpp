// FUNC_NAME: scaleVector3PreserveW
void scaleVector3PreserveW(float scale, float* src, float* dst)
{
    float origW = dst[3];
    dst[0] = scale * src[0];
    dst[1] = scale * src[1];
    dst[2] = scale * src[2];
    dst[3] = origW;
}