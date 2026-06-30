// FUNC_NAME: Ray::setFromPointsAndEntityId
void __thiscall Ray::setFromPointsAndEntityId(Ray* this, const Vector3* start, const Vector3* end, int entityId)
{
    // Structure layout:
    // +0x00: Vector4 start (x,y,z,w) – 16 bytes
    // +0x10: Vector4 end   (x,y,z,w) – 16 bytes
    // +0x20: byte validFlag
    // +0x24: int entityId
    // Total size: 40 bytes (with alignment padding)

    this->validFlag = 0;          // Write byte at +0x20
    this->entityId = 0;           // Write int at +0x24

    // Copy start vector (3 floats) and set w to 0
    this->start.x = start->x;
    this->start.y = start->y;
    this->start.z = start->z;
    this->start.w = 0.0f;        // param_1[3] = 0

    // Copy end vector (3 floats) and set w to 0
    this->end.x = end->x;
    this->end.y = end->y;
    this->end.z = end->z;
    this->end.w = 0.0f;          // param_1[7] = 0

    this->validFlag = 1;          // Mark as valid
    this->entityId = entityId;    // Store entity/intersection ID
}