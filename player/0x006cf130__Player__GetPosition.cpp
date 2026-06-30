// FUNC_NAME: Player::GetPosition
// Function at 0x006cf130: Returns the player's position as a 4-component vector (likely x,y,z,w).
// Assumes the Player class has a member 'm_position' of type Vector4 at offset 0x60.
// Offsets: +0x60 = x, +0x64 = y, +0x68 = z, +0x6c = w.

struct Vector4 {
    float x, y, z, w;
};

void __thiscall Player::GetPosition(Player *this, Vector4 *outPosition)
{
    outPosition->x = *(float *)((char *)this + 0x60);
    outPosition->y = *(float *)((char *)this + 0x64);
    outPosition->z = *(float *)((char *)this + 0x68);
    outPosition->w = *(float *)((char *)this + 0x6c);
}