// FUNC_NAME: Entity::isStateInRange
class Entity {
public:
    // Returns 1 if m_state is outside the range [8, 19], 0 otherwise.
    // m_state is at offset +0x64 (100 decimal).
    bool isStateInRange() {
        int state = *(int*)((char*)this + 0x64);
        if (state > 7 && state < 20) {
            return false; // 0
        }
        return true; // 1
    }
};