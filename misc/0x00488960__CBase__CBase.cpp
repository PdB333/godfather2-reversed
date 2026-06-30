// FUNC_NAME: CBase::CBase

class CBase {
public:
    CBase(unsigned char flags);
private:
    void baseInit();          // FUN_00488980 - base class initialization
    void additionalInit();    // FUN_009c8eb0 - conditional secondary initialization
};

CBase::CBase(unsigned char flags) {
    baseInit();
    if (flags & 1) {
        additionalInit();
    }
}