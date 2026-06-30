// FUNC_NAME: Math::lerpQuaternion
void __fastcall Math::lerpQuaternion(float *out, float *from, float *to, float t)
{
    // Linearly interpolate quaternions: out = from * (1-t) + to * t
    // But this implementation actually computes: out = to + t * (from - to)
    // using the given ordering: out = t * from + to
    // The quaternion is stored as 4 floats (x, y, z, w)
    
    float fVar2 = from[1]; // y
    float fVar3 = from[2]; // z
    float fVar4 = from[3]; // w
    
    float fVar1 = out[3];  // Save original w (maybe used for something else?)
    
    float fVar5 = to[1];   // y
    float fVar6 = to[2];   // z
    float fVar7 = to[3];   // w
    
    out[0] = t * from[0] + to[0];  // x = t * from.x + to.x
    out[1] = t * fVar2 + fVar5;    // y = t * from.y + to.y
    out[2] = t * fVar3 + fVar6;    // z = t * from.z + to.z
    out[3] = t * fVar4 + fVar7;    // w = t * from.w + to.w
    out[3] = fVar1;                // Restore original w (seems like a bug or special behavior)
    
    return;
}