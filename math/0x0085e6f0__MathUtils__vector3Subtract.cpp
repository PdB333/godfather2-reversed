//FUNC_NAME: MathUtils::vector3Subtract
void __fastcall vector3Subtract(int unused, float* src1, float* src2)
{
    // This function subtracts two 4-component vectors (src1 - src2) but only for the first three components.
    // The fourth component of the destination (passed in EAX) is preserved unchanged.
    // In the original binary, the destination pointer is passed in EAX, not as a parameter.
    // For reconstruction, we assume the caller sets EAX to the destination buffer.
    // Here we treat the destination as an implicit parameter; the actual C++ signature cannot represent this directly.
    // The following code emulates the behavior using a local pointer to the destination.
    // Note: The first parameter (ECX) is unused.

    // In the original, the destination is in EAX. We'll simulate by assuming a global or passed pointer.
    // For clarity, we'll write the function as if it takes three float* parameters: dest, src1, src2.
    // But to match the __fastcall signature, we keep the unused first parameter.
    // The actual implementation would be:
    // void vector3Subtract(float* dest, float* src1, float* src2) { ... }
    // However, due to the calling convention, we cannot perfectly reconstruct.

    // For the purpose of this reconstruction, we'll write the logic as a static function.
    // The original code:
    float fVar2 = src1[1];
    float fVar3 = src1[2];
    float fVar4 = src1[3];
    float fVar5 = src2[1];
    float fVar6 = src2[2];
    float fVar7 = src2[3];
    // dest pointer is in EAX; we'll use a local variable to represent it.
    float* dest; // This would be the value of EAX at entry.
    // Assume dest is provided by the caller via some mechanism.
    // For the sake of the reconstruction, we'll treat dest as an additional parameter.
    // But since we cannot add it without changing the signature, we'll comment that the function expects dest in EAX.
    // The following lines show the actual operations:
    float fVar1 = dest[3]; // save original dest[3]
    dest[0] = src1[0] - src2[0];
    dest[1] = fVar2 - fVar5;
    dest[2] = fVar3 - fVar6;
    dest[3] = fVar4 - fVar7; // temporary subtraction
    dest[3] = fVar1; // restore original fourth component
}