// FUNC_NAME: CopiedObject::CopiedObject
class CopiedObject {
public:
    // offsets: 0x00,0x04 = unknown (set to 0)
    int field0;       // +0x00
    int field4;       // +0x04
    int magic0;       // +0x08 (initially 0xbadbadba)
    int magic1;       // +0x0c (initially 0xbeefbeef)
    int magic2;       // +0x10 (initially 0xeac15a55)
    int magic3;       // +0x14 (initially 0x91100911)
    int data0;        // +0x18 (copied from src+0x18)
    int data1;        // +0x1c (copied from src+0x1c)
    ListNode* head;   // +0x20 (linked list head)
    int extra;        // +0x28 (copied from src+0x28)
};

CopiedObject* __thiscall CopiedObject::CopiedObject(CopiedObject* this, const CopiedObject* src) {
    // Initialize debug sentinels (later overwritten with actual data)
    this->field0 = 0;
    this->field4 = 0;
    this->magic0 = 0xbadbadba;
    this->magic1 = 0xbeefbeef;
    this->magic2 = 0xeac15a55;
    this->magic3 = 0x91100911;
    this->data0 = 0;
    this->data1 = 0;

    // Copy data from source (starting at offset 0x08)
    this->magic0 = src->magic0;   // +0x08
    this->magic1 = src->magic1;   // +0x0c
    this->magic2 = src->magic2;   // +0x10
    this->magic3 = src->magic3;   // +0x14
    this->data0  = src->data0;    // +0x18
    this->data1  = src->data1;    // +0x1c

    // Linked list node insertion
    // Check for self-assignment
    if (&this->head != &src->head) {   // offset 0x20
        int newHead = src->head;         // value from source's head
        if (this->head != newHead) {
            if (this->head != nullptr) {
                // Remove old node from list (likely unlink)
                FUN_004daf90(this->head);
            }
            this->head = newHead;        // set head to source's head
            if (newHead != nullptr) {
                this->head->prev = &this->head;   // node's prev points to this head pointer
            }
        }
    }
    this->extra = src->extra;   // +0x28
    return this;
}