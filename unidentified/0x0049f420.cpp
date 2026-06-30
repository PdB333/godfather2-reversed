// FUN_NAME: EARSObject::setWorldMatrix
void EARSObject::setWorldMatrix(const Matrix& source) // __thiscall, this=ESI, source=EAX
{
    // Copy 16 floats (64 bytes) from source to this->worldMatrix at +0x30
    // Ghidra shows copying 16 ints, but semantically they're floats
    this->worldMatrix[0] = source.m[0]; // +0x30
    this->worldMatrix[1] = source.m[1]; // +0x34
    this->worldMatrix[2] = source.m[2]; // +0x38
    this->worldMatrix[3] = source.m[3]; // +0x3c
    this->worldMatrix[4] = source.m[4]; // +0x40
    this->worldMatrix[5] = source.m[5]; // +0x44
    this->worldMatrix[6] = source.m[6]; // +0x48
    this->worldMatrix[7] = source.m[7]; // +0x4c
    this->worldMatrix[8] = source.m[8]; // +0x50
    this->worldMatrix[9] = source.m[9]; // +0x54
    this->worldMatrix[10] = source.m[10]; // +0x58
    this->worldMatrix[11] = source.m[11]; // +0x5c
    this->worldMatrix[12] = source.m[12]; // +0x60
    this->worldMatrix[13] = source.m[13]; // +0x64
    this->worldMatrix[14] = source.m[14]; // +0x68
    this->worldMatrix[15] = source.m[15]; // +0x6c

    // Check if this node has children (bit 1 at +0xAC)
    if ((this->flags & 2) != 0)
    {
        // Notify children of transform change (likely update bounds/dirty flag)
        FUN_0049feb0();

        ChildNode** childArray = reinterpret_cast<ChildNode**>(this->childListPtr); // +0x8c
        int childCount = this->childCount; // +0x90

        ChildNode** end = childArray + childCount;
        for (ChildNode** it = childArray; it != end; ++it)
        {
            ChildNode* child = *it; // each element is a pointer to ChildNode
            // Check if child is active (bit 0 at +0xB2)
            if ((child->flags2 & 1) != 0)
            {
                // Update child's transform: combine parent world matrix with child's local
                // Arguments: global transform? (DAT_012233a8+4), child->localMatrix (+0xA0), child->position? (+0x10), temp buffer
                char tempBuffer[28]; // undefined1 local_20[28]
                FUN_0042d380(*(int*)(DAT_012233a8 + 4), child->localMatrix, child->someVector, tempBuffer);
            }
        }
    }
}