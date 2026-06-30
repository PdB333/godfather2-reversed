// FUNC_NAME: Vector4::subtract (0x0066f520)
// This function computes the component-wise subtraction of two 4D vectors.
// this points to the minuend (vector A), param_1 is the subtrahend (vector B), 
// param_2 is the destination for the result (A - B).
void __thiscall Vector4::subtract(const Vector4* subtrahend, Vector4* result) const
{
    // Compute differences for each of the four components
    result->x = this->x - subtrahend->x;
    result->y = this->y - subtrahend->y;
    result->z = this->z - subtrahend->z;
    result->w = this->w - subtrahend->w;
}