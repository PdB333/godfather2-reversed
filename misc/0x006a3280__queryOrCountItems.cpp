// FUNC_NAME: queryOrCountItems

#include <cstdint>

// Node in a circular doubly-linked list, used as an intrusive container.
struct ListNode {
    ListNode* prev;
    ListNode* next;
};

// Forward declarations of called functions (unknown signatures).
// FUN_006a2d70 likely populates a list starting from the given sentinel.
// Returns non-zero on success, zero on failure.
extern int __cdecl populateList(ListNode* sentinel);

// FUN_009c8f10 likely frees a single node.
extern void __cdecl freeNode(ListNode* node);

/**
 * Query or count items from a list.
 * If populateList succeeds, returns its result (non-zero).
 * If it fails, writes whether any items were found into pOutHasItems and returns 0.
 * 
 * @param pOutHasItems Output boolean, set only when populateList returns 0.
 * @return Result from populateList if non-zero, else 0.
 */
int queryOrCountItems(bool* pOutHasItems) {
    // Circular doubly-linked list sentinel on the stack.
    ListNode sentinel;
    sentinel.prev = &sentinel;
    sentinel.next = &sentinel;

    int result = populateList(&sentinel);
    if (result != 0) {
        // Success: free all nodes and return the result.
        ListNode* current = sentinel.next;
        while (current != &sentinel) {
            ListNode* next = current->next;
            freeNode(current);
            current = next;
        }
        return result;
    }

    // Failure: count nodes (excluding sentinel).
    int count = 0;
    ListNode* current = sentinel.next;
    while (current != &sentinel) {
        current = current->next;
        ++count;
    }

    // Write existence flag.
    *pOutHasItems = (count != 0);

    // Free all nodes.
    current = sentinel.next;
    while (current != &sentinel) {
        ListNode* next = current->next;
        freeNode(current);
        current = next;
    }

    return 0;
}