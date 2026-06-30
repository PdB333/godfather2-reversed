// FUNC_NAME: ThreadTask::reset
void __fastcall ThreadTask::reset(ThreadTask* this)
{
    // +0x18 (index 6) handle member
    if (this->handle != (HANDLE)0xFFFFFFFF) {
        CloseHandle(this->handle);
        this->handle = (HANDLE)0xFFFFFFFF;
    }
    // +0x00 (index 0) state / flags
    this->state = 0;
    // +0x1C (index 7) - some status/flag
    this->field_1C = 0;
    // +0x20 (index 8) - default true
    this->field_20 = 1;
    // +0x24 (index 9)
    this->field_24 = 0;
    // +0x28 (index 10)
    this->field_28 = 0;

    // +0x2C (index 11) - pointer to secondary resource
    if (this->ptr2C == 0) {
        // +0x14 (index 5) - primary data pointer
        if (this->ptr14 != 0) {
            FUN_009c8eb0(this->ptr14);  // release primary resource
        }
    } else {
        FUN_009c8f10(this->ptr2C);      // release secondary resource
        this->ptr2C = 0;
    }
    this->ptr14 = 0;

    // +0x30 (index 12)
    this->field_30 = 0;
    // +0x08 (index 2) = copy of +0x04 (index 1)
    this->field_08 = this->field_04;
    // +0x34 (index 13)
    this->field_34 = 0;
}