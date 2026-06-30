// 0x0040cf30
// Bounded string setter used by an engine object that owns a fixed 0x80-byte
// text field at offset 0x90.
//
// The decompiled code only proves the storage pattern, not the higher-level
// game concept behind the field, so the object name stays intentionally opaque.

#include <cstring>
#include <cstdint>

class FixedTextSlotOwner
{
public:
    std::uint8_t unknown_00[0x90];
    char textField[0x80];

    void __thiscall setText(const char* sourceText);
};

void __thiscall FixedTextSlotOwner::setText(const char* sourceText)
{
    if (sourceText == nullptr)
    {
        return;
    }

    // The original function performs a bounded copy into the embedded buffer.
    // It does not explicitly force a trailing null byte, so this stays faithful
    // to the observed engine behavior.
    std::strncpy(textField, sourceText, sizeof(textField));
}
