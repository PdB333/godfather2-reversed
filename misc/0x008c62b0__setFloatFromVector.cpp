// FUNC_NAME: setFloatFromVector
// Address: 0x008c62b0
// Role: Computes a float value from a 3-component vector (param_2, param_3, param_4) and sets it on an object (param_1).
// Calls FUN_008c5780 (likely a vector math function like magnitude or dot product) and FUN_008bfe70 (setter).

void setFloatFromVector(void* object, float x, float y, float z)
{
    // Compute a scalar from the vector components (e.g., magnitude, dot product, or weighted sum)
    float result = (float)FUN_008c5780(x, y, z); // FUN_008c5780 returns extended precision float (float10)
    
    // Apply the computed value to the object (likely sets a member variable)
    FUN_008bfe70(object, result);
}