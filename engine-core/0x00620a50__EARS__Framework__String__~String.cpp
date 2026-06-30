// FUNC_NAME: EARS::Framework::String::~String
// Address: 0x00620a50
// Role: Destructor for a string-like object managed by the EARS framework.
// Cleans up internal buffer if owned, then frees memory via the engine allocator.

void __fastcall String::~String(String *this)
{
    // Lock / enter critical section (likely for thread-safe ref counting)
    FUN_00c9eac0();

    // Check if the internal buffer is owned (byte at offset +0x24)
    if (this->ownsBuffer != 0) {
        // Release the buffer (pointer at offset +0x0C)
        FUN_00ca5480(&this->buffer);
    }

    // Deallocate this string’s memory block (size 1, alignment 0)
    FUN_00c9cd40(1, 0);

    // Unlock / leave critical section
    FUN_00c9eae0();
}