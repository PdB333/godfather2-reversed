// FUNC_NAME: Entity::getPositionZ
class Entity {
public:
    // Returns the Z-coordinate of the object's position, stored at offset 0x2C.
    float __fastcall getPositionZ() const {
        return *(float*)(reinterpret_cast<const char*>(this) + 0x2C);
    }
};