// FUNC_NAME: removeNodeFromList
// Address: 0x00441e00
// This function removes a node from a singly linked list where the next pointer
// uses its least significant bit as a "deleted" flag. It searches for a node with
// a given key (passed in ESI), unlinks it, and then either marks it as deleted
// (sets LSB of its own next pointer) or frees it, depending on a flag in the
// manager structure.
// Parameters:
//   ECX: unused (possibly this pointer of a containing object)
//   EDX: pointer to ListManager structure (offsets +0x0c, +0x10)
//   ESI: key value to search for
// The function is called with __fastcall but also expecting ESI set by the caller.

struct ListNode {
    int  key;   // +0x00 : node identifier / value to match
    int  next;  // +0x04 : pointer to next node (bit 0 is a deletion flag)
};

struct ListManager {
    char deleteFlag; // +0x0c : if non‑zero, mark node instead of freeing it
    int  head;       // +0x10 : pointer to first node (LSB may be set)
};

void __fastcall removeNodeFromList(int unusedECX, ListManager* mgr)
{
    int key;  // === ESI (set by caller) ===
    // In the original assembly the key is passed in ESI. For reconstruction we
    // treat it as a hidden third parameter; the actual calling convention
    // expects ESI to contain the value before the call.

    // In the decompiled code, `unaff_ESI` is used as the key. To make the
    // logic explicit, we assume the compiler or caller has placed `key` in ESI.
    // This is a reconstruction, so we simply declare it as a local constant.
    // (The real callers load ESI before calling.)

    #ifdef RECONSTRUCTED
    // This value is actually passed via ESI. We will either inject it as a
    // parameter or use a local that represents the register. For clarity we
    // define it as a function hook; in the original binary it is not a local.
    int key_from_esi; // placeholder – must be set before function body
    #endif

    ListNode* prev = 0;
    ListNode* curr = (ListNode*)mgr->head;

    while (curr != 0) {
        if (curr->key == key && ((curr->next & 1) == 0))
            break;
        prev = curr;
        curr = (ListNode*)(curr->next & ~1);   // clear LSB to get raw pointer
    }

    if (curr == 0)
        return;

    // Unlink curr from the list
    if (prev == 0) {
        // Removing the head node
        mgr->head = curr->next & ~1;
    } else {
        // Update previous node's next pointer, preserving its own LSB flag
        // Expression: ((curr->next ^ prev->next) & 1) ^ curr->next
        // This sets the LSB of prev->next to the old LSB of prev->next
        // while keeping the rest of curr->next.
        prev->next = ( (curr->next ^ prev->next) & 1 ) ^ curr->next;
    }

    if (mgr->deleteFlag) {
        // Mark the removed node as deleted (set LSB of its own next pointer)
        curr->next = curr->next | 1;
    } else {
        // Actually deallocate the node – function at 0x004abf50 (probably a custom free)
        // FUN_004abf50(curr);
        // In real code this might be operator delete or a pool release.
        // We simulate it with a call:
        // freeNode(curr);
    }
}