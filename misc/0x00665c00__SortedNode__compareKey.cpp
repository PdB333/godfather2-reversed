// FUNC_NAME: SortedNode::compareKey
int __fastcall SortedNode::compareKey(uint key) const
{
    // +0x08: sentinel flag – if 1, this node is a sentinel (end marker)
    if (this->sentinelFlag == 1) {
        return -1;
    }
    // +0x00: count or size indicator; if less than 2, node may be a leaf or empty
    if (this->count < 2) {
        // +0x0C: pointer to the stored key value (uint)
        uint storedKey = *(this->pKey);
        // Returns -1 if storedKey < key, 0 if equal, 1 otherwise (but only reached when count>=2)
        return -(storedKey < key ? 1 : 0);
    }
    // For nodes with count >= 2, always return 1 (greater)
    return 1;
}