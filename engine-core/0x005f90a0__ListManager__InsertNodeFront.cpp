// FUNC_NAME: ListManager::InsertNodeFront

class ListManager {
public:
    // +0x18: Node* m_pListHead (or some list head structure)
    void InsertNodeFront(int param_1); // param_1 is likely this
};

// Forward declarations for internal functions
static Node* AllocateNode(Node* listHead, Node* next, int someParam);
static void OnNodeAdded(); // no parameters, maybe notification

// Node structure (unknown offsets)
struct Node {
    // offset 0: unknown (maybe prev or data)
    // offset 4: Node* next; // or prev? Based on usage, likely next
    Node* next; // +0x04
};

void __fastcall ListManager::InsertNodeFront(int param_1)
{
    // param_1 is this pointer
    Node* listHead = *(Node**)(param_1 + 0x18); // +0x18: pointer to list head object
    Node* oldNext = *(Node**)(listHead + 4); // listHead->next
    Node* newNode = AllocateNode(listHead, oldNext, in_EAX); // in_EAX is an undefined register value, we treat as int
    OnNodeAdded(); // some post-processing

    // Insert at front of list
    listHead->next = newNode;
    // Set the previous pointer of the node that newNode points to (via its next)
    // newNode->next->prev = newNode
    *(Node**)(newNode->next) = newNode; // newNext is the address of the node's prev field? Actually node+4 is next pointer
}

// Non-member helper wrappers (if needed)