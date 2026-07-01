// FUNC_NAME: NetChannel::init

void __thiscall NetChannel::init(void *this, void *parent)
{
    uint flags = *(uint *)((char *)this + 0x4c);
    
    // Check if already initialized (bit 2)
    if ((flags & 4) == 0) {
        // Release any previously owned object at offset 0x1c
        if (*(int *)((char *)this + 0x1c) != 0) {
            releaseOwnedObject(*(int *)((char *)this + 0x1c));
        }
        
        // Store parent and increment its reference count if valid
        *(int *)((char *)this + 0x20) = (int)parent;
        if (*(short *)((char *)parent + 4) != 0) {
            *(short *)((char *)parent + 6) = *(short *)((char *)parent + 6) + 1;
        }
        
        // Mark as initialized (bit 2)
        *(uint *)((char *)this + 0x4c) = flags | 4;
        
        // Base class initialization
        initBase();
        
        // Allocate large buffer if not already done (bit 6)
        if ((*(byte *)((char *)this + 0x4c) & 0x40) == 0) {
            if (*(int *)((char *)this + 0xc) != 0) {
                registerWithGlobalSystem(gsSystem); // global handle at 0x01131018
            }
            allocateBuffer((char *)this + 0x10, 0x8000); // 32KB buffer
            *(uint *)((char *)this + 0x4c) = *(uint *)((char *)this + 0x4c) | 0x40;
        }
    }
}