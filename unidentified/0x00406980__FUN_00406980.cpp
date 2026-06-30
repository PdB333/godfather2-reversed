#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" void* FUN_009c8e80(std::uint32_t size);

struct FUN_00406980_Object
{
    void* data;                // [0x00]
    std::uint32_t count;       // [0x04]
    std::uint32_t unknown_08;  // [0x08]
    std::uint32_t unknown_0c;  // [0x0C]
    std::uint32_t unknown_10;  // [0x10]
    bool unknown_14;           // [0x14]
};

extern "C" void __thiscall FUN_00406980(FUN_00406980_Object* this_)
{
    this_->count = 0x4b;
    this_->data = nullptr;
    this_->unknown_08 = 0;
    this_->unknown_0c = 0;
    this_->unknown_10 = 0;
    this_->unknown_14 = true;

    void* const dst = FUN_009c8e80(300);
    this_->data = dst;
    std::memset(dst, 0, this_->count * 4);
}