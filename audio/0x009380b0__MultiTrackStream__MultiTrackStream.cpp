// FUNC_NAME: MultiTrackStream::MultiTrackStream
MultiTrackStream* __thiscall MultiTrackStream::MultiTrackStream(MultiTrackStream* this)
{
    // Base initialization (likely parent class constructor)
    baseInit();

    // Set up vtable and static pointers
    // Offset +0x4C: first static pointer (overwritten later)
    this->field_0x4C = (char*)&PTR_LAB_00d8a1ec;

    // Primary vtable at offset 0x00
    this->vtable = &PTR_FUN_00d8a218;

    // Offset +0x10: secondary vtable or static data
    this->field_0x10 = (char*)&PTR_LAB_00d8a1f4;

    // Overwrite offset +0x4C with a different static pointer
    this->field_0x4C = (char*)&PTR_LAB_00d8a1f0;

    // Initialize counters/flags to zero
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x6C = 0;

    // Allocate four internal buffers
    // Buffer #1 (size 0x10) – probably a small string or track name
    this->buffer1 = (char*)allocBuffer(0x10);
    *this->buffer1 = '\0';

    // Buffer #2 (size 0x10) – another small buffer
    this->buffer2 = (char*)allocBuffer(0x10);
    *this->buffer2 = '\0';

    // Buffer #3 (size 0x10) – yet another small buffer
    this->buffer3 = (char*)allocBuffer(0x10);
    *this->buffer3 = '\0';

    // Buffer #4 (size 0x80) – larger buffer (e.g., stream data or audio)
    this->buffer4 = (char*)allocBuffer(0x80);
    *this->buffer4 = '\0';

    // Store singleton instance (global pointer)
    DAT_011305b4 = this;

    return this;
}