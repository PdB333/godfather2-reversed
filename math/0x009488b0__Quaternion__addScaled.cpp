// FUNC_NAME: Quaternion::addScaled
void __thiscall Quaternion::addScaled(const Quaternion* other, float t, Quaternion* result) const
{
    // Linear combination: result = other + t * this
    // Reads this vector via in_EAX (implicit this pointer) and other via param_1
    // Output to param_3 (result)

    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    float otherX = other->x;
    float otherY = other->y;
    float otherZ = other->z;
    float otherW = other->w;

    result->x = otherX + t * thisX;
    result->y = otherY + t * thisY;
    result->z = otherZ + t * thisZ;
    result->w = otherW + t * thisW;
}