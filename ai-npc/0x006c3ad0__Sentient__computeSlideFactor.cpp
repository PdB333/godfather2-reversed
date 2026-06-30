// FUNC_NAME: Sentient::computeSlideFactor
void __thiscall Sentient::computeSlideFactor(Sentient* this, const Vector3& input)
{
    // +0x298 is likely m_slideDistance or m_obstacleFactor
    float slideFactor;

    // Get position from input transform (global offset)
    Vector3 origin;
    VectorMath::getPosition(&origin, input); // FUN_00424fb0

    // Get speed or magnitude from input
    float speed = VectorMath::getSpeed(input); // FUN_00425190

    // Get direction vector from input (probably forward direction)
    Vector3 forward;
    VectorMath::getDirection(&forward, input); // FUN_00425060

    // Decompose direction into pitch and yaw angles (assuming spherical coordinates)
    double yaw = (double)forward.x;   // local_24
    double pitch = (double)forward.y; // local_20

    // Compute sin and cos of angles
    double cosYaw = Math::cos(yaw);   // FUN_00b99fcb
    double sinYaw = Math::sin(yaw);   // FUN_00b99e20
    double cosPitch = Math::cos(pitch);// FUN_00b99fcb (second call)
    double sinPitch = Math::sin(pitch);// FUN_00b99e20 (second call)

    // Compute raycast direction components
    float invTerm = 1.0f - (float)(cosYaw * sinPitch); // fVar6
    // Actually from code: fVar6 = DAT_00e44564 - (float)dVar3 * (float)dVar5
    // dVar3 = cosYaw, dVar5 = sinPitch
    // Similarly, fVar7 = 1 - sinYaw * sinPitch

    float invFactor = 1.0f - speed; // fVar2 = DAT_00e44564 - (float)fVar1

    // Compute a point in direction scaled by invFactor
    Vector3 intermediate;
    intermediate.x = invFactor * invTerm + origin.x; // local_30
    intermediate.y = invFactor * (float)cosPitch + origin.y; // local_2c?? Wait, from code: local_2c = fVar2 * (float)dVar3 + local_14; dVar3 here is cosYaw? Actually dVar3 was reassigned later. The code is ambiguous.
    intermediate.z = invFactor * (1.0f - sinYaw * sinPitch) + origin.z; // local_28

    // Compute another point further along the direction (scaled by a constant from script)
    float mysteryScale = Script::getMysteryScale(0, 0, 0); // FUN_006c3910
    Vector3 endPoint;
    endPoint.x = mysteryScale * invTerm + intermediate.x; // local_c
    endPoint.y = mysteryScale * (float)cosPitch + intermediate.y; // local_8
    endPoint.z = mysteryScale * (1.0f - sinYaw * sinPitch) + intermediate.z; // local_4

    // Perform collision raycast from intermediate to endPoint
    float hitDistance = Physics::raycast(intermediate, endPoint, 0, 0); // FUN_006c9b00

    if (hitDistance <= 0.0f)
    {
        this->m_slideDistance = 0.0f; // +0x298
        return;
    }

    // Clamp the distance to a global maximum
    float clamped = hitDistance;
    if (gMaxSlideDistance < hitDistance) // DAT_00d5780c
    {
        clamped = gMaxSlideDistance;
    }
    this->m_slideDistance = clamped;
}