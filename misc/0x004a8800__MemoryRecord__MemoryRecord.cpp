// FUNC_NAME: MemoryRecord::MemoryRecord
void __fastcall MemoryRecord::MemoryRecord(uint this_ecx, int id_edx) {
    // 'this' is in ECX, id in EDX
    MemoryRecord* self = reinterpret_cast<MemoryRecord*>(this_ecx);
    int id = id_edx;

    // Zero-initialize most fields
    self->field_04 = 0;           // +0x04
    self->field_08 = 0;           // +0x08
    self->field_20 = 0;           // +0x20
    self->field_30 = 0;           // +0x30
    self->field_18 = 0xFFFFFFFF;  // +0x18, invalid ID/flag
    self->field_1C = 0;           // +0x1C
    self->field_0C = 0;           // +0x0C
    self->field_10 = 0;           // +0x10
    self->field_14 = 0;           // +0x14
    self->field_2C = 0;           // +0x2C
    self->field_34 = 0;           // +0x34, prev pointer
    self->field_38 = 0;           // +0x38, next pointer (set later)
    self->vtable = &s_vtable;     // +0x00, set to vtable at 0x00e355bc
    self->field_3C = 0;           // +0x3C
    self->field_40 = 0;           // +0x40
    self->id = id;                // +0x44, parameter passed in EDX
    self->field_48 = 0xFE16702F;  // +0x48, some class identifier constant
    self->field_4C = 0;           // +0x4C
    self->field_50 = 1;           // +0x50, maybe initialization flag

    // Re-read manager pointer (in case it changed? but it's static)
    MemoryRecordManager* mgr = s_pMemoryRecordManager; // DAT_0122344c
    MemoryRecord** tail = reinterpret_cast<MemoryRecord**>(&mgr->tail); // +0x20

    // Set prev pointer to 0 (already done) and next to current head
    self->field_34 = 0;                                          // +0x34 = 0
    self->field_38 = mgr->head;                                  // +0x38 = mgr->head

    // Insert into doubly linked list at head
    if (mgr->head != nullptr) {
        // Old head's prev points to new node
        mgr->head->field_34 = self;                              // +0x34 of old head = new node
    } else {
        // List was empty: also set tail to this new node
        mgr->tail = self;
    }
    mgr->head = self;                                            // +0x24 = new node becomes head
}