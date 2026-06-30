// FUNC_NAME: vectorSubtract3
void __fastcall vectorSubtract3(float *dest, const float *a, const float *b)
{
    float savedW = dest[3];
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    dest[3] = savedW;
}