#include <cstdint>

extern "C" int FUN_009c8e80(std::uint32_t size);
extern "C" void FUN_004d3b50(void* src);
extern "C" void FUN_009c8f10(int ptr);

struct FUN_00407880_Object
{
    void* instance;                                   // [0x00]
    std::uint32_t field_0x04;                         // [0x04]
    std::uint32_t field_0x08;                         // [0x08]
    void (__thiscall* destroy)(void* instance);       // [0x0C]
};

extern "C" void __thiscall FUN_00407880(int* self, std::uint32_t capacity)
{
    int newBuffer;
    int offset;
    int destination;
    FUN_00407880_Object* object;
    std::uint32_t index;

    if (static_cast<std::uint32_t>(self[2]) < capacity) {
        newBuffer = FUN_009c8e80(capacity << 4);
        offset = 0;

        if (*self != 0) {
            index = 0;
            destination = newBuffer;

            if (self[1] != 0) {
                do {
                    object = reinterpret_cast<FUN_00407880_Object*>(*self + offset);

                    if (destination != 0) {
                        FUN_004d3b50(object);
                    }

                    if (object->instance != nullptr) {
                        object->destroy(object->instance);
                    }

                    index = index + 1;
                    offset = offset + 0x10;
                    destination = destination + 0x10;
                } while (index < static_cast<std::uint32_t>(self[1]));
            }

            FUN_009c8f10(*self);
        }

        *self = newBuffer;
        self[2] = static_cast<int>(capacity);
    }
}