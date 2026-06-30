// FUNC_NAME: BaseObject::constructor
// Address: 0x00509cd0
// Role: Constructor that calls initialization function and returns this pointer

class BaseObject {
public:
    // Initialization function at 0x00513ac0
    void init();
};

BaseObject* BaseObject::constructor() {
    this->init();
    return this;
}