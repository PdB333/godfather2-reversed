// FUNC_NAME: Node::insert
struct Node {
    int data;          // +0x00
    Node* next;        // +0x04
    int flag;          // +0x08
};

// Global linked list head
static Node* s_head = nullptr;

// External engine functions (not defined here)
extern void memorySet(float param, int size, void* source);         // FUN_009a3ea0
extern void computeSpatialData(float* radius, byte buffer[16], float area); // FUN_005fcf80
extern void nodeCleanup(Node* node);                                // FUN_004daf90
extern void postInsertCleanup();                                    // FUN_006a8490

bool __thiscall Node::insert(float radius)
{
    bool result = false;
    byte buffer[16]; // local_194

    // Copy 0x20 bytes from global DAT_00d5ccf8 using radius as parameter (likely a pattern)
    memorySet(radius, 0x20, (void*)0x00d5ccf8);

    // Compute spatial data: pass address of radius, buffer, and area = radius * radius
    computeSpatialData(&radius, buffer, radius * radius);

    // Insert this node at the front of the global linked list
    if (this != s_head && this->data != s_head->data) { // compare pointers and data
        if (this->data != 0) {
            nodeCleanup(this); // Free old node data if present
        }
        this->data = (int)s_head; // Cast head pointer to data field (store reference)
        if (s_head != nullptr) {
            this->next = s_head->next;
            s_head->next = this;
        }
    }
    this->flag = (int)this; // local_17c is set to something; likely the node's own address

    // Determine success: both data and flag are non-zero
    if (this->data != 0 && this->flag != 0) {
        result = true;
    }
    postInsertCleanup();
    return result;
}