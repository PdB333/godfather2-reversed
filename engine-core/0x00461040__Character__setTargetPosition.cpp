// FUNC_NAME: Character::setTargetPosition
// Address: 0x00461040
// Role: Sets two values at offsets +0x268 and +0x26c (likely target position or direction).

class Character {
public:
    void setTargetPosition(int targetX, int targetY);
};

inline void Character::setTargetPosition(int targetX, int targetY) {
    // +0x268: first target component (e.g., X)
    *(int*)((uintptr_t)this + 0x268) = targetX;
    // +0x26c: second target component (e.g., Y)
    *(int*)((uintptr_t)this + 0x26c) = targetY;
}