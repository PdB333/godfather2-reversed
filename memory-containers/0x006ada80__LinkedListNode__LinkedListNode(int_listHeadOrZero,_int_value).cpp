// FUNC_NAME: LinkedListNode::LinkedListNode(int listHeadOrZero, int value)

// Address: 0x006ada80
// This is a constructor for a doubly-linked list node that inserts itself at the head of a list.
// The list header is a structure with a head pointer at offset 0x48.
// The node fields:
// +0x00: vtable pointer
// +0x04: value (some data)
// +0x08: next node pointer
// +0x0C: prev node pointer
// +0x10: field (int, default 0)
// +0x14: field (int, default 0)
// +0x18: field (int, default 0)
// +0x1C: byte field (default 0)
// +0x20: int field (initialized from global DAT_01205228)

void __thiscall LinkedListNode::LinkedListNode(int listHeadOrZero, int value)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d5dbbc;

  // Store the provided value
  this->value = value;

  // Get pointer to the list head field; if listHeadOrZero is 0, this will be 0
  int* headPtr = (listHeadOrZero != 0) ? (int*)(listHeadOrZero + 0x48) : 0;
  this->next = headPtr;
  this->prev = 0;

  // Insert at head: if list is non-empty, update old head's prev pointer
  if (headPtr != 0) {
    this->prev = *(int**)(headPtr + 4); // old head's prev? Actually headPtr + 4 is the prev field of the head node? Wait, headPtr points to a ListNode, so headPtr+4 is its prev? No, headPtr is the value of the list head pointer, i.e., it points to the first node. Then headPtr+4 is offset 4 from that node, which is the 'value' field. That seems wrong. Let's re-examine decompiled:
    // param_1[3] = 0; if (param_2 != 0) { param_1[3] = *(undefined4 *)(param_2 + 4); *(undefined4 **)(param_2 + 4) = param_1 + 2; }
    // Here param_1 is this, param_2 is listHeadOrZero. So: if listHeadOrZero != 0, then this->prev = *(int*)(listHeadOrZero + 4); and then *(int**)(listHeadOrZero + 4) = &this->next;
    // So the "head pointer" is stored at listHeadOrZero+0x48, but the node's prev pointer is stored at listHeadOrZero+4? That doesn't match typical list header. Maybe listHeadOrZero is actually a node pointer (the current head node), not the list header. The caller provides either 0 or a pointer to the current head node. Then the new node is inserted before that head. So head node's prev (offset 4?) is updated to point to new node's next pointer? Actually typical: node->next = oldHead; node->prev = 0; if (oldHead) oldHead->prev = &node->next; But here they're using offset 4 as the prev field of the old head? That would mean the node structure is: offset 0=vtable, offset 4=value, offset 8=next, offset 12=prev. So the old head's prev field is at offset 12, not 4. But the code accesses param_2+4, which would be offset 4. So perhaps the structure is different: maybe offset 0 is some field, offset 4 is prev? Let's check: param_1[3] is offset 12 (since int array: [0]=0, [1]=4, [2]=8, [3]=12). So this->prev = *(int*)(listHeadOrZero+4); That means the old head's offset 4 is being read as the previous node pointer. That offset 4 would be the 'value' field, which doesn't make sense. Perhaps the code is wrong? Or maybe the structure is: offset 0=vtable, offset 4=next, offset 8=prev, offset 12=value? No, param_1[2] is set to headPtr (which is param_2+0x48), so next is at offset 8. So offset 8 = next. Then offset 12 = prev. Then the old head's prev is at offset 8? Actually if old head's prev is at offset 8 (since it's a node), then accessing offset 4 would be something else. This is confusing. I'll stick to the decompiled logic exactly, but in reconstruction I'll name fields meaningfully based on observed behavior: this->prev = oldHead->someField; and then oldHead->someField = &this->next; The field at offset 4 of the head node is being used as a "prev" pointer for the list? That suggests the list is intrusive and the "prev" pointer is stored in a different location? Actually, typical intrusive list: each node has next and prev pointers. Here, the head node's prev pointer is stored at offset 4 of the node? That would be unusual. Let's assume the decompiler is correct and the structure is:
    // offset 0: vtable
    // offset 4: prev (for list linking)
    // offset 8: next
    // offset 12: value
    // That would fit: param_1[1] = param_3 (value) -> offset 4? No, param_1[1] is offset 4, so value is at offset 4? Then param_1[2] is next at offset 8, param_1[3] is prev at offset 12. But the code uses param_2+4 as the old head's "prev" pointer. If the old head's prev is at offset 4, then accessing offset 4 of the old head would give its prev. That would mean the node layout is:
    // +0x00: vtable
    // +0x04: next? Or prev? Actually param_1[2] = next, so next at 8, prev at 12. So offset 4 is value. Then why does the code access offset 4 of the old head? Maybe it's not the head node but a different structure? Alternatively, maybe I misread: the code says param_2 + 0x48 is assigned to param_1[2] (next). So listHeadOrZero is a pointer to a structure that contains a head pointer at +0x48. Then param_2 (the structure pointer) is not a node. So param_2 is the list header object. Then param_1[3] = *(undefined4 *)(param_2 + 4); accesses the "prev" field of the list header? Or something else. That would be weird. Let's re-read the decompiled comments: The function signature says void __thiscall FUN_006ada80(undefined4 *param_1,int param_2,undefined4 param_3). So param_1 is this, param_2 is some integer (could be a pointer), param_3 is value. In the body: param_1[1] = param_3; so this+4 = value. Then *param_1 = vtable. Then if param_2 == 0, param_2 = 0; else param_2 = param_2 + 0x48. So param_2 becomes either 0 or param_2+0x48. Then param_1[2] = param_2; so this->next = param_2. Then param_1[3] = 0; if (param_2 != 0) { param_1[3] = *(undefined4 *)(param_2 + 4); *(undefined4 **)(param_2 + 4) = param_1 + 2; } So if param_2 (the head pointer) is not null, then this->prev = *(int*)(headPtr + 4); and then *(int**)(headPtr + 4) = &this->next; So headPtr is a node pointer. Accessing headPtr+4: if headPtr points to a node, its +4 is the 'value' field. That would be using the value field as a backward pointer? That seems like a bug or misinterpretation. Perhaps the node layout is: +0x00: vtable, +0x04: prev, +0x08: next, +0x0C: value. Then headPtr+4 would be prev, which makes sense. So the offsets are different: param_1[1] = value at +0x04? But param_1[1] is at offset 4, and value is stored there. So if value is at offset 4, then prev cannot also be at offset 4. So the layout must be: +0x00: vtable, +0x04: value, +0x08: next, +0x0C: prev. Then headPtr+4 is value field of head node, not prev. So the code is using the value field as a backward link? That is unusual. Maybe the "value" field is actually some kind of node identifier used as a back pointer in a different context? I'll go with the literal reconstruction, leaving comments explaining the observed offsets. Since the game uses EARS, maybe there's a specific class like "EARSLinkedListNode" with fields: vtable, data, next, prev. I'll adopt that.

Given the ambiguity, I'll write the code with the exact logic, naming fields as observed: vtable, data (value), next, prev, and then the other fields. The offset 4 is used as a "back pointer" in the insertion, so I'll name it "backLink" or "prev" but that conflicts. I'll use "listPrev" for the field at offset 12, and note that the insertion accesses oldHead->data as the prev pointer. That suggests the data field is repurposed as a prev pointer when the node is in a list? That's weird. Alternatively, maybe the structure is: offset0: vtable, offset4: listPrev (back), offset8: next, offset12: data. That would match: param_1[1] = data is at offset12? No, param_1[1] is offset4. So if data is at offset4, then listPrev must be at offset12. Then headPtr+4 (data) is being used as the prev pointer of the old head. That would mean the data field holds the prev pointer when the node is in a list? Possibly the data field is a union or is used as a back pointer only during list operations. That's plausible. So I'll name the field at offset4 as "listData" but note it's used as a back pointer in insertion. I'll keep the reconstruction faithful to the decompiled logic.

I'll produce:

struct LinkedListNode {
    void* vtable;      // +0x00
    int data;          // +0x04 (also used as back pointer during list insertion)
    LinkedListNode* next; // +0x08
    LinkedListNode* prev; // +0x0C
    int field1;        // +0x10
    int field2;        // +0x14
    int field3;        // +0x18
    byte byteField;    // +0x1C
    int globalField;   // +0x20
};
But the code sets param_1[8] = DAT_01205228, which is offset 32 (0x20). That's field after byteField (which is at 28, so next int at 32). So total size at least 36 bytes.

Now the insertion: headPtr = listHeadOrZero ? listHeadOrZero+0x48 : 0; But wait, param_2 is originally listHeadOrZero (int). Then modified: if param_2 == 0, param_2 = 0; else param_2 = param_2 + 0x48. So headPtr = param_2 after adjustment. So the actual head node pointer is derived by adding 0x48 to the parameter. That means the parameter is a pointer to a structure that contains the head node pointer at offset 0x48. So listHeadOrZero is a "list manager" object, not a node. The head node pointer is stored at that offset. So headPtr = *(int**)(listHeadOrZero+0x48)? No, the code does param_2 = param_2 + 0x48, so headPtr becomes the address of that head pointer field, not its value. Actually param_2 is an int, so adding 0x48 gives an address. Then param_1[2] = param_2; stores that address as the next pointer. That means the "next" pointer of the new node points to the head pointer field itself? That would make the list store pointers to pointers? That seems wrong. Let's read: param_2 = param_2 + 0x48; param_1[2] = param_2; So this->next is the address of the head pointer field. Then later, if (param_2 != 0) { param_1[3] = *(undefined4 *)(param_2 + 4); ... } Here param_2 is a pointer to the head pointer field, so param_2+4 is that field +4, which is inside the list manager object. That is weird. Given the confusion, I'll stick exactly to the decompiled code in my reconstruction, using the same variable names but with meaningful comments.

I think the best approach is to produce a function that matches the decompiled logic exactly, with symbolic names for the parameters and fields based on typical list node patterns. I'll name the function `LinkedListNode::constructor` and the parameters `listHeader` and `nodeData`. I'll comment on the structure offsets.

I'll output the code in C++ style.// FUNC_NAME: LinkedListNode::constructor(int listHeader, int nodeData)
// Address: 0x006ada80
// This is a constructor for a node in a doubly-linked list. It inserts the node at the head of a list.
// The list header is a structure with a head pointer at offset 0x48.
// Node layout (offsets from this pointer):
// +0x00: vtable pointer (set to PTR_FUN_00d5dbbc)
// +0x04: nodeData (some application-specific value)
// +0x08: next node pointer (list link)
// +0x0C: prev node pointer (list link)
// +0x10: field1 (initialized to 0)
// +0x14: field2 (initialized to 0)
// +0x18: field3 (initialized to 0)
// +0x1C: byteField (initialized to 0)
// +0x20: globalField (initialized from global DAT_01205228)

void __thiscall LinkedListNode::constructor(int listHeader, int nodeData)
{
    // Set vtable
    this->vtable = &PTR_FUN_00d5dbbc;

    // Store data value
    this->data = nodeData;

    // Calculate pointer to the list head pointer field
    // If listHeader is 0, no list; otherwise, the head pointer is at offset 0x48 from the list header object.
    int* headPtr = (listHeader != 0) ? (int*)(listHeader + 0x48) : 0;
    this->next = headPtr; // next points to the head pointer field (or null)

    // Initialize prev to 0
    this->prev = 0;

    // If the list is non-empty, insert this node before the current head.
    if (headPtr != 0)
    {
        // The field at offset 0x04 of the current head is used as a backward link.
        // This could be a union or reinterpretation of the data field.
        this->prev = *(int*)(headPtr + 4); // old head's back pointer

        // Update the old head's back pointer to point to this node's next field.
        *(int**)(headPtr + 4) = &this->next;
    }

    // Clear additional fields
    this->field1 = 0;
    this->field2 = 0;
    this->field3 = 0;
    this->byteField = 0;

    // Initialize global field from a global variable
    this->globalField = DAT_01205228;

    return;
}