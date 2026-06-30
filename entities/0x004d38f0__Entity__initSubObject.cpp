// FUNC_NAME: Entity::initSubObject  
// Address: 0x004d38f0  
// Role: Initializes internal state (sets field at +0x0C to 0) and calls a sub‑initializer  

int __thiscall Entity::initSubObject(Entity* this, undefined4 argInitParam1, undefined4 argInitParam2) {
    // Field at +0x0C: likely a pointer or flag; set to null/0
    *(undefined4*)((char*)this + 0x0C) = 0;
    // Call another initialization function with the provided parameters
    FUN_004d3c40(argInitParam1, argInitParam2);
    return (int)this;
}