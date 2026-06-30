// FUNC_NAME: Event::~Event
void __thiscall Event::~Event(Event* this) // +0x00: vtable at 0x00e3f0b4
{
    int data = this->data; // +0x20, pointer to additional data
    this->vtable = (int*)0x00e3f0b4; // set base vtable before cleanup

    if (data != 0) {
        int param2 = this->param2; // +0x14
        int param1 = this->param1; // +0x10
        int* listInsertPtr = (int*)((int*)0x01206880)[0x5]; // gEventListHead + 0x14 (tail insertion point)
        **(int**)((int*)0x01206880 + 0x5) = 0x011273f4; // write vtable for new node
        *listInsertPtr += 4;
        *(int*)*listInsertPtr = data;
        *listInsertPtr += 4;
        *(int*)*listInsertPtr = param1;
        *listInsertPtr += 4;
        *(int*)*listInsertPtr = param2;
        *listInsertPtr += 4;
    }

    if (this->callback != 0) { // +0x18, function pointer to release callback context
        ((void (__stdcall*)(int))0x0119caf4)(this->callback); // call gEventCallbackDeleter
    }

    FUN_00423bf0(&this); // free Event memory
    FUN_005d8600(); // global cleanup (likely decrement reference or pool reset)
}