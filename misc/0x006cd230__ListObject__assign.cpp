// FUNC_NAME: ListObject::assign
// Function at 0x006cd230: copy assignment for object with two intrusive linked list nodes and data fields

void __cdecl removeListEntry(int* node); // Removes node from its list (FUN_004daf90)

class ListObject {
public:
    // Offsets in bytes:
    int* m_list1Head;   // +0x00: first list head pointer (also node's next pointer when inserted)
    int* m_list1Prev;   // +0x04: previous node in first list
    int* m_list2Head;   // +0x08: second list head pointer
    int* m_list2Prev;   // +0x0C: previous node in second list
    int m_data0;        // +0x10
    int m_data1;        // +0x14
    int m_data2;        // +0x18
    int m_data3;        // +0x1C

    // __thiscall assignment operator
    ListObject* __thiscall assign(ListObject* other);
};

ListObject* ListObject::assign(ListObject* other) {
    if (this != other) {
        // Copy first list (list1)
        if (this->m_list1Head != other->m_list1Head) {
            if (this->m_list1Head != 0) {
                removeListEntry(&this->m_list1Head);
            }
            this->m_list1Head = other->m_list1Head;
            if (other->m_list1Head != 0) {
                // Link this node as new head of list1: store old head's prev
                this->m_list1Prev = *(int**)(other->m_list1Head + 1);
                *(int**)(other->m_list1Head + 1) = this;
            }
        }
        // Copy second list (list2)
        if (&this->m_list2Head != &other->m_list2Head) {
            if (this->m_list2Head != 0) {
                removeListEntry(&this->m_list2Head);
            }
            this->m_list2Head = other->m_list2Head;
            if (other->m_list2Head != 0) {
                this->m_list2Prev = *(int**)(other->m_list2Head + 1);
                *(int**)(other->m_list2Head + 1) = this;
            }
        }
        // Copy remaining data fields
        this->m_data0 = other->m_data0;
        this->m_data1 = other->m_data1;
        this->m_data2 = other->m_data2;
        this->m_data3 = other->m_data3;
    }
    return this;
}