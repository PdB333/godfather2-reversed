// FUNC_NAME: PacketWindow::create

#include <cstdint>
#include <cstdlib>

// Global allocator function pointers (set by engine initialization)
static void* (*s_allocFunc)(size_t) = nullptr;
static void  (*s_freeFunc)(void*)  = nullptr;

constexpr uint32_t kErrorSuccess      = 0;
constexpr uint32_t kErrorOutOfMemory  = 0x2718;   // 10008 – allocation failed

constexpr uint32_t kMagicHeader       = 0xab1500ff; // class identifier
constexpr uint32_t kMagicFooter1      = 0xaa005501; // footer marker
constexpr uint32_t kMagicFooter2      = 0xa5a55a5a; // footer marker

constexpr int32_t  kWindowSize        = 0x1f5;     // 501 entries

// PacketWindow – sliding window for reliable network packets (size 0x94)
struct PacketWindow
{
    uint32_t magic;              // +0x00: class magic
    int32_t  field_04;           // +0x04
    int32_t  windowSize;         // +0x08: number of entries in the window array
    int32_t* windowEntries;      // +0x0C: pointer to array of ints [windowSize]

    // +0x10…+0x68: state fields, all initialised to 0
    int32_t  field_10;
    int32_t  field_14;
    int32_t  field_18;
    int32_t  field_1C;
    int32_t  field_20;
    int32_t  field_24;
    int32_t  field_28;
    int32_t  field_2C;
    int32_t  field_30;
    int32_t  field_34;
    int32_t  field_38;
    int32_t  field_3C;
    int32_t  field_40;
    int32_t  field_44;
    int32_t  field_48;
    int32_t  field_4C;
    int32_t  field_50;
    int32_t  field_54;
    int32_t  field_58;
    int32_t  field_5C;
    int32_t  field_60;
    int32_t  field_64;
    int32_t  field_68;

    // +0x6C…+0x84: flags, all initialised to 1
    int32_t  flags_6C;
    int32_t  flags_70;
    int32_t  flags_74;
    int32_t  flags_78;
    int32_t  flags_7C;
    int32_t  flags_80;
    int32_t  flags_84;

    int32_t  field_88;           // +0x88: 0

    // Footers to detect memory corruption
    uint32_t footerMagic1;       // +0x8C
    uint32_t footerMagic2;       // +0x90
};
static_assert(sizeof(PacketWindow) == 0x94, "PacketWindow size mismatch");

// Factory: allocate and initialise a new PacketWindow
// Returns pointer to the object, or nullptr on failure.
// *outError is set to kErrorOutOfMemory if an allocation fails.
PacketWindow* PacketWindow::create(uint32_t* outError)
{
    if (s_allocFunc == nullptr)
    {
        *outError = kErrorOutOfMemory;
        return nullptr;
    }

    PacketWindow* win = static_cast<PacketWindow*>(s_allocFunc(sizeof(PacketWindow)));
    if (win == nullptr)
    {
        *outError = kErrorOutOfMemory;
        return nullptr;
    }

    // Write magic numbers and header data
    win->magic        = kMagicHeader;
    win->field_04     = 0;
    win->windowSize   = kWindowSize;
    win->footerMagic1 = kMagicFooter1;
    win->footerMagic2 = kMagicFooter2;

    // Allocate the window array
    win->windowEntries = static_cast<int32_t*>(s_allocFunc(kWindowSize * sizeof(int32_t)));
    if (win->windowEntries == nullptr)
    {
        s_freeFunc(win);
        *outError = kErrorOutOfMemory;
        return nullptr;
    }

    // Zero the window array
    for (int32_t i = 0; i < kWindowSize; ++i)
        win->windowEntries[i] = 0;

    // Zero state fields (offsets 0x10–0x68)
    win->field_10 = 0;
    win->field_14 = 0;
    win->field_18 = 0;
    win->field_1C = 0;
    win->field_20 = 0;
    win->field_24 = 0;
    win->field_28 = 0;
    win->field_2C = 0;
    win->field_30 = 0;
    win->field_34 = 0;
    win->field_38 = 0;
    win->field_3C = 0;
    win->field_40 = 0;
    win->field_44 = 0;
    win->field_48 = 0;
    win->field_4C = 0;
    win->field_50 = 0;
    win->field_54 = 0;
    win->field_58 = 0;
    win->field_5C = 0;
    win->field_60 = 0;
    win->field_64 = 0;
    win->field_68 = 0;

    // Set flags to 1 (offsets 0x6C–0x84)
    win->flags_6C = 1;
    win->flags_70 = 1;
    win->flags_74 = 1;
    win->flags_78 = 1;
    win->flags_7C = 1;
    win->flags_80 = 1;
    win->flags_84 = 1;

    // Remaining zero field
    win->field_88 = 0;

    *outError = kErrorSuccess;
    return win;
}