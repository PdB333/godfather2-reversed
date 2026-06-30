// FUNC_NAME: Family::findMemberById
bool __thiscall Family::findMemberById(int memberId) {
    // this + 0x11c: pointer to first family member node (list of members)
    int currentMemberNode = *(int *)((uint)this + 0x11c);
    bool found = false;

    if (currentMemberNode == nullptr) {
        // No members; return true (not found)
        return true;
    }

    do {
        // currentMemberNode + 0x18: pointer to list of children of this member
        int childNode = *(int *)(currentMemberNode + 0x18);
        while (childNode != nullptr) {
            // childNode + 0x8: child's identifier (memberId or similar)
            if (*(int *)(childNode + 0x8) == memberId) {
                found = true;
                // Found => return false (since !found becomes false)
                return false;
            }
            // childNode + 0xc: next child node
            childNode = *(int *)(childNode + 0xc);
        }
        // Move to next family member via sibling pointer
        currentMemberNode = *(int *)(currentMemberNode + 0x10);
        if (currentMemberNode == nullptr) {
            // No more members; not found
            return true;
        }
    } while (true);
}