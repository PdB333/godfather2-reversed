// FUNC_NAME: BaseObject::BaseObject
class BaseObject {
public:
    BaseObject(bool flag);
private:
    void init();       // FUN_006a3720 – base initialization
    void finalizeInit(); // FUN_009c8eb0 – extra setup (e.g. vtable, allocation)
};

// Constructor: if flag is true, perform additional initialization
BaseObject::BaseObject(bool flag) {
    this->init();
    if (flag) {
        this->finalizeInit();
    }
}