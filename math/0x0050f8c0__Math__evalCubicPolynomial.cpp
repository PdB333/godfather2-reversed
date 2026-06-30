// FUNC_NAME: Math::evalCubicPolynomial
void Math::evalCubicPolynomial(float* outVec, const float* coeffs, const float* inVec, float t)
{
    // Compute cubic polynomial: out[0] = t * coeffs[0] + inVec[0]
    // Then out[1] = out[0] * coeffs[1] + inVec[1]
    // Then out[2] = out[1] * coeffs[2] + inVec[2]
    // The three calls to CheckNaN() are safety checks for floating-point errors.
    CheckNaN();
    float result = t * coeffs[0] + inVec[0];
    outVec[0] = result;

    CheckNaN();
    result = result * coeffs[1] + inVec[1];
    outVec[1] = result;

    CheckNaN();
    outVec[2] = result * coeffs[2] + inVec[2];
}