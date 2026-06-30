// FUNC_NAME: lerp
// 0x004b9c30 - Linear interpolation function (lerp)
// Performs: result = (from - to) * t + to, which is standard lerp.
// Note: The original used 10-byte extended float internally, but the interface is float.

float lerp(float from, float to, float t)
{
    // Standard linear interpolation formula
    return (from - to) * t + to;
}