// FUNC_NAME: Iterator::getNext
extern void __declspec(noreturn) assertFailed();

struct Container {
    char pad[0x18];
    void* sentinel;
};

class Iterator {
public:
    Container* container;
    void* current;

    void* getNext() {
        if (container == nullptr || current == container->sentinel) {
            assertFailed();
        }
        return (char*)current + 8;
    }
};