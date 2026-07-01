// FUNC_NAME: GameEntity::operator=
// Address: 0x0082a8f0
// Role: Assignment operator for GameEntity, copies base class data, list head, and adjust node's prev pointer.
// The class contains:
//   +0x4c: m_position (Vec3? two floats? - 8 bytes)
//   +0x54: m_velocity? (another 8 bytes)
//   +0x5c: m_childListHead (pointer to first child node, which has prev at offset +4)
//   +0x60: m_childListPrev? (used as temporary during insertion)
//   +0x64: m_childCount (int)
// Actual structure may differ, but this is a reasonable interpretation.

int __thiscall GameEntity::operator=(GameEntity *this, const GameEntity *other)
{
    // Call base class assignment (likely copies basic fields)
    BaseEntity::operator=(other);

    // Copy first 16 bytes of data (two 8-byte values: position, velocity)
    *(undefined8 *)(this + 0x4c) = *(undefined8 *)(other + 0x4c);
    *(undefined8 *)(this + 0x54) = *(undefined8 *)(other + 0x54);

    // Copy the intrusive list head (m_childListHead)
    int *destHeadPtr = (int *)(this + 0x5c);
    int srcHeadVal = *(int *)(other + 0x5c);    // source's list head pointer

    if (destHeadPtr != (int *)(other + 0x5c))   // if not the same object
    {
        if (*destHeadPtr != srcHeadVal)          // if different list node
        {
            // Free existing child list node if any
            if (*destHeadPtr != 0)
            {
                FUN_004daf90(destHeadPtr);       // destructor/free for node
            }
            *destHeadPtr = srcHeadVal;           // set new list head pointer

            // Adjust the node's prev pointer to point to this object's head slot
            if (srcHeadVal != 0)
            {
                // Copy the node's prev pointer to this->m_childListPrev
                *(int *)(this + 0x60) = *(int *)(srcHeadVal + 4);
                // Update node's prev to point to this object
                *(int **)(srcHeadVal + 4) = destHeadPtr;
            }
        }
    }

    // Copy child count
    *(int *)(this + 100) = *(int *)(other + 100);   // offset 0x64
    return (int)this;
}