// FUNC_NAME: SomeClass::constructorWithDestructFlag
class SomeClass;

void staticInit();
void destroy(SomeClass* obj);

class SomeClass {
public:
    __thiscall SomeClass* constructorWithDestructFlag(unsigned char flag) {
        staticInit();
        if (flag & 1) {
            destroy(this);
        }
        return this;
    }
};