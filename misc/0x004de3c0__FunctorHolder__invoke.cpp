// FUNC_NAME: FunctorHolder::invoke
// Address: 0x004de3c0
// Role: Calls a functor object's function (first vtable entry or function pointer at offset 0) with the given argument and a temporary result buffer (three ints). The functor pointer is stored at +0x4 of the this object. If the functor is null, does nothing.

// The functor structure: points to a function at offset 0 that takes (int arg, int* resultBuffer) and presumably fills the buffer.
struct Functor {
    void (*call)(int, int*); // +0x00: function pointer
};

class FunctorHolder {
    // +0x00: unknown (possibly vtable pointer or other members)
    Functor* m_functor; // +0x04: pointer to functor object
public:
    void __thiscall invoke(int param_2);
};

void __thiscall FunctorHolder::invoke(int param_2) {
    if (m_functor != nullptr) {
        int resultBuffer[3] = { 0, 0, 0 }; // local_c, local_8, local_4
        m_functor->call(param_2, resultBuffer);
    }
}