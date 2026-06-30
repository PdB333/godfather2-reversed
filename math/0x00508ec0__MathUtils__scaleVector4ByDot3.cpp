// FUNC_NAME: MathUtils::scaleVector4ByDot3
void __fastcall scaleVector4ByDot3(float* out, float* vec4, float* vec3)
{
    // Compute dot product of first 3 components of vec4 and vec3
    float dot = vec3[0] * vec4[0] + vec3[1] * vec4[1] + vec3[2] * vec4[2];
    // Save original w component of out
    float savedW = out[3];
    // Scale vec4 by dot product and write to out.xyz
    out[0] = dot * vec4[0];
    out[1] = dot * vec4[1];
    out[2] = dot * vec4[2];
    // Preserve original w component
    out[3] = savedW;
}