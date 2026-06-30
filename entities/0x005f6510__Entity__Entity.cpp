// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(int *this, int *param_2, int *param_3, int param_4) {
    // vtable at +0x00
    this[0] = (int)&PTR_FUN_00e407c4; // set vtable
    this[1] = 0; // unknown field at +0x04

    // Insert into first list (list A)
    int headA = *param_3; // dereference head pointer
    this[2] = headA; // this->listANext = headA
    this[3] = 0; // this->listAPrev = nullptr
    if (headA != 0) {
        this[3] = *(int *)(headA + 4); // this->listAPrev = old head's prev? No, it's actually setting prev to something from old head. But typical: if headA, then new node's prev = old head's something? Let's assume it's the old head's "backlink" pointer.
        *(int **)(headA + 4) = &this[2]; // old head's backlink = &this->listANext (intrusive)
    }
    // this[4] stores the original param_3[2] value (e.g., list owner data)
    this[4] = param_3[2];

    // Insert into second list (list B)
    int headB = *param_2;
    this[5] = headB;
    this[6] = 0;
    if (headB != 0) {
        this[6] = *(int *)(headB + 4);
        *(int **)(headB + 4) = &this[5];
    }
    this[7] = param_2[2];

    // Store general parameter
    this[8] = param_4;

    // Initialize various fields
    this[10] = 0;  // +0x28
    this[12] = 0;  // +0x30
    this[13] = 0;  // +0x34
    this[14] = 0;  // +0x38
    this[15] = DAT_00e2e50c; // global value
    this[16] = 0;  // +0x40
    this[17] = 0;  // +0x44

    // Fetch from global manager (likely SimManager)
    int *manager = (int *)DAT_01223520;
    this[11] = *(int *)((int)manager + 0x20); // +0x2C

    // Local struct (12 bytes) used for allocation
    int localBuffer[3] = {0, 0, 0}; // maybe some resource descriptor

    // Call virtual function on manager to allocate memory
    // manager->vtable[0x10/4] (method at offset 0x10) with two arguments
    int (*allocFunc)(int, int *) = (int (*)(int, int *))*(int *)(*(int *)((int)manager + 0x10));
    int result = allocFunc(*(int *)((int)manager + 0x20) * 12, localBuffer);

    this[9] = result; // store allocation result

    if (result == 0) {
        this[14] |= 0x84; // set error flags (bit 7 and bit 2)
    }

    this[19] = 0x9000; // +0x4C some default size/capacity
    this[18] = 0x8000; // +0x48
}