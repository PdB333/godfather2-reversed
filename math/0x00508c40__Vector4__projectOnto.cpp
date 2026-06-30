// FUNC_NAME: Vector4::projectOnto
// Function Address: 0x00508c40
// Role: Vector projection onto a unit vector (preserves w component)
// Assumes 'onto' is a unit vector (or scales by onto's length squared if not normalized)
// Modifies this->data[0..2] to (onto·vec)*onto, leaves data[3] unchanged

void __thiscall Vector4::projectOnto(float *onto /* in EDX */, float *vec /* on stack */)
{
    float dotProduct;

    float ontoX = onto[0];
    float ontoY = onto[1];
    float ontoZ = onto[2];
    // onto[3] is used only in a redundant write, then overwritten

    float origW = this->data[3];

    float dX = vec[0] * ontoX;
    float dY = vec[1] * ontoY;
    float dZ = vec[2] * ontoZ;
    dotProduct = dX + dY + dZ; // dot(onto[0..2], vec[0..2])

    this->data[0] = dotProduct * ontoX;
    this->data[1] = dotProduct * ontoY;
    this->data[2] = dotProduct * ontoZ;
    this->data[3] = origW;     // preserve w component
}