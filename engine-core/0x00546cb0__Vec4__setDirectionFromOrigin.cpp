// FUNC_NAME: Vec4::setDirectionFromOrigin
void __thiscall Vec4::setDirectionFromOrigin(float *origin, float &outLength) {
    // Copies the current vector (this) to local variables? Actually modifies this in place.
    // The decompiler uses in_EAX for this pointer and unaff_ESI for the same? Possibly register confusion.
    // The code computes direction from origin to this vector, normalizes this, stores original length in outLength.
    // The constant at 0x00e2b1a4 is assumed to be 1.0f.
    float dx = this[0] - origin[0];
    float dy = this[1] - origin[1];
    float dz = this[2] - origin[2];
    float dw = this[3] - origin[3]; // w component (possibly for quaternion or homogeneous coordinate)

    float lengthSq = dx*dx + dy*dy + dz*dz; // magnitude squared ignoring w
    float length = sqrt(lengthSq);
    float invLength = 1.0f / length;

    this[0] = dx * invLength;
    this[1] = dy * invLength;
    this[2] = dz * invLength;
    this[3] = dw * invLength; // w normalized by same factor (not standard for 3D vectors)

    outLength = length;
}