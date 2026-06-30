// FUNC_NAME: TNLConnection::processAckOrTimeoutPacket

#include <windows.h>

// Represents a node in an intrusive doubly linked list embedded in objects
struct ListNode {
    ListNode* prev; // offset 0? or first field?
    int someField;  // Actually the decompiled shows first field is int, then next pointer at offset 12. Need to infer.
    int unknown1;
    int unknown2;
    ListNode* next; // offset 12? assuming 4-byte ints.
};

class TNLConnection {
public:
    // Reconstructed member function at 0x00645230
    int processAckOrTimeoutPacket(void* param_1) {
        LPCRITICAL_SECTION critSec = *(LPCRITICAL_SECTION*)(this + 0x4E8);
        if (critSec != nullptr) {
            EnterCriticalSection(critSec);
            // Increment lock count (hackish representation)
            ((int*)critSec)[1] = ((int*)critSec)[1] + 1;  // DebugInfo hack
        }

        int iVar3 = FUN_00644d30(param_1); // some processing

        uint uVar1 = *(uint*)((char*)param_1 + 4); // flags from object

        // Iterate over intrusive list at this+0x4A8 (head) until sentinel at this+0x49C
        ListNode* piVar2 = *(ListNode**)(this + 0x4A8);
        ListNode* sentinel = (ListNode*)(this + 0x49C);
        while (piVar2 != sentinel) {
            // Check if node's owner offset matches param_1
            // Note: the node stores owner address in its first field? Actually we compare (int)piVar2 - *piVar2
            // We assume *piVar2 is the owner object address (as int), so difference is node offset in owner.
            if ((int)piVar2 - *(int*)piVar2 == (int)param_1) {
                break;
            }
            piVar2 = (ListNode*)piVar2->next; // assume next at offset 12
        }

        if (critSec != nullptr) {
            ((int*)critSec)[1] = ((int*)critSec)[1] - 1; // Decrement lock count
            LeaveCriticalSection(critSec);
        }

        int found = (piVar2 == sentinel) ? 0 : 1;
        int bitFlag = ((byte)~(byte)(uVar1 >> 1) & 1);
        return found + iVar3 + bitFlag;
    }

private:
    // Offset 0x49C: sentinel node (tail of list)
    // Offset 0x4A8: head pointer of list
    // Offset 0x4E8: critical section pointer
    // FUN_00644d30 is an internal method (maybe "processPacket")
};