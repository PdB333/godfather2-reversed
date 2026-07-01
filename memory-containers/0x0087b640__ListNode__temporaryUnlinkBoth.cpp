// FUNC_NAME: ListNode::temporaryUnlinkBoth
// Address: 0x0087b640
// Role: Temporarily removes two intrusive list nodes (at offset 0x48) from their current lists by replacing their next pointers with stack-based sentinels, performs an assertion check, then reattaches them. Used for list integrity validation or temporary relocation.

void __thiscall ListNode::temporaryUnlinkBoth(int* thisPtr, int* otherObj)
{
    const int NODE_OFFSET = 0x48;     // Embedded node offset within the object (ListNode is at base+0x48)
    const int NEXT_OFFSET = 0x4c;     // Offset of 'next' pointer (from object base, pointing to next ListNode)

    // Local sentinels (will act as list heads on stack)
    int sentinel1 = 0;                // local_8
    int sentinel2 = 0;                // local_10
    int savedNext1 = 0;               // local_4
    int savedNext2 = 0;               // local_c

    // Unlink this node
    if (thisPtr != 0 && (thisPtr + NODE_OFFSET) != 0) {
        // Save current next pointer
        savedNext1 = *(int*)(thisPtr + NEXT_OFFSET);
        // Replace node's next pointer with address of stack sentinel1
        *(int**)(thisPtr + NEXT_OFFSET) = &sentinel1;
        // Set sentinel1 to point to this node's embedded ListNode
        sentinel1 = reinterpret_cast<int>(thisPtr + NODE_OFFSET);
    }

    // Prepare other object's node pointer
    int* otherNode = otherObj;
    if (otherNode == 0) {
        otherNode = 0;
    } else {
        otherNode = reinterpret_cast<int*>(reinterpret_cast<char*>(otherNode) + NODE_OFFSET);
    }

    // Unlink other node
    if (otherNode != 0) {
        sentinel2 = 0;
        sentinel1 = reinterpret_cast<int>(otherNode); // Note: This reuses sentinel1 as a temporary (from decompiled code)
        // Save current other node's next pointer (at node+4 = object base+0x4c)
        savedNext2 = *(int*)(otherNode + 4);
        // Replace other node's next pointer with address of stack sentinel2
        *(int**)(otherNode + 4) = &sentinel2;
        // Note: sentinel2 was originally set from local_10, but here we reassign it
        sentinel2 = reinterpret_cast<int>(otherNode);
    }

    // Debug assertion: likely checks that the list state is valid
    // Arguments: static data (DAT_0112e028), a function pointer (PTR_FUN_00d7666c), and 0
    int local_20 = DAT_0112e028;
    int local_18 = 0;
    // This call probably performs an assertion or logs a diagnostic
    debugAssert(&local_20, 0);

    // Reattach the sentinels (clean up local list)
    if (sentinel1 != 0) {
        unlinkListNode(&sentinel1);   // FUN_004daf90
    }
    if (sentinel2 != 0) {
        unlinkListNode(&sentinel2);   // FUN_004daf90
    }

    // Note: After this function returns, the nodes are back in their original lists
    // because the sentinels were temporary and the original next pointers were saved.
    // However, the decompiled code does not restore savedNext1/savedNext2, which suggests
    // the operation is intentional (maybe the sentinels become part of the list).
    // This may be a bug in the decompilation or the function deliberately leaves the list
    // in an altered state (the sentinels replace the original next pointers).
}