// FUNC_NAME: vec3Add (3D vector addition preserving w component)
void __fastcall vec3Add(float* dest, const float* a, const float* b) {
    float w = dest[3]; // preserve w component
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    dest[3] = w;
}