// FUNC_NAME: BaseObject::dispatch
void __thiscall BaseObject::dispatch(void) {
    // This function performs a type check and dispatches to a function pointer
    // stored in the object's class descriptor.
    // Object layout: at +0x8 is a pointer to a ClassInfo structure.
    struct ClassInfo {
        short unknown;   // +0x0 (possibly alignment or size)
        short typeId;    // +0x2  expected to be 8
        void (*method)(); // +0x4  function pointer to call
    };
    
    ClassInfo* classInfo = *reinterpret_cast<ClassInfo**>(reinterpret_cast<char*>(this) + 8);
    
    // Validate type ID: if not 8, call global error handler
    if (classInfo->typeId != 8) {
        // Global error handler table (likely for debug asserts)
        // DAT_01205590 points to a structure with a function pointer at +4
        typedef void (*ErrorHandler)();
        ErrorHandler* errorTable = reinterpret_cast<ErrorHandler*>(DAT_01205590);
        (*errorTable)(); // Call error handler
    }
    
    void (*method)() = classInfo->method;
    if (method != nullptr) {
        method(); // Dispatch to the stored function
    }
}