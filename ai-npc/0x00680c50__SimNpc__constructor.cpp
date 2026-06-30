// FUNC_NAME: SimNpc::constructor
int __thiscall SimNpc::constructor(SimNpc *this, byte aFlag) {
    undefined4 *vtablePtrRef;
    
    if (this == (SimNpc *)0x0) {
        vtablePtrRef = (undefined4 *)0x0;
    } else {
        vtablePtrRef = (undefined4 *)((int)this + 0x20);  // +0x20: offset for this class's vtable
    }
    *vtablePtrRef = &g_SimNpcVtable;  // set vtable to static table
    g_someGlobal = 0;                 // reset global count/state
    initSomething();                  // perform common initialization (likely member function, but called as global here)
    if ((aFlag & 1) != 0) {
        deallocate(this);             // if allocated via 'new', call destructor/cleanup? (conditional delete)
    }
    return (int)this;
}