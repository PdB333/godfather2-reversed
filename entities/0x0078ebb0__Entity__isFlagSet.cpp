// FUNC_NAME: Entity::isFlagSet
bool Entity::isFlagSet(byte flagIndex) const {
    // flags_ at +0x2f is a bitfield byte
    if (flags_ == 0) {
        return true;
    }
    return (1 << (flagIndex & 0x1f)) & flags_;
}