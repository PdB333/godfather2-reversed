// FUNC_NAME: UIRect::setFromSource
void __thiscall UIRect::setFromSource(UIRect* this, UIRect* outRect2, void* source)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;

    // Initialize both output rectangles to empty
    this->flag = 0;
    outRect2->flag = 0;
    this->field_0x14 = 0;   // +0x14 (short)
    this->field_0x16 = 0;   // +0x16 (short)
    outRect2->field_0x14 = 0;
    outRect2->field_0x16 = 0;

    if (*(int*)((char*)source + 0x20) == 0) {
        // Source has no sub-object at +0x20; use direct fields
        this->field_0x14 = *(short*)((char*)source + 100);   // +0x64
        this->field_0x16 = *(short*)((char*)source + 0x66);  // +0x66

        if (*(int*)((char*)source + 0x38) != 0) {
            void* ptr38 = *(void**)((char*)source + 0x38);
            this->flag = 1;
            this->left   = *(short*)((char*)ptr38 + 8);
            this->top    = *(short*)((char*)ptr38 + 10);
            this->right  = *(short*)((char*)ptr38 + 0xc);
            this->bottom = *(short*)((char*)ptr38 + 0xe);
            this->width  = (int)*(short*)((char*)ptr38 + 0x18);
            this->height = (int)*(short*)((char*)ptr38 + 0x16);

            iVar5 = 0;
            while (true) {
                iVar1 = this->width;
                iVar2 = this->height;
                if (iVar1 >= 0x10000 || iVar1 <= -0x10000) break;
                if (iVar2 >= 0x10000 || iVar2 <= -0x10000) break;

                // Scale by 2
                iVar3 = iVar1 * 2;
                iVar4 = iVar2 * 2;
                this->width = iVar3;
                this->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) break;
                if (iVar4 > 0xffff || iVar4 < -0xffff) break;

                // Scale by 4
                iVar3 = iVar1 * 4;
                iVar4 = iVar2 * 4;
                this->width = iVar3;
                this->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) break;
                if (iVar4 > 0xffff || iVar4 < -0xffff) break;

                // Scale by 8
                iVar3 = iVar1 * 8;
                iVar4 = iVar2 * 8;
                this->width = iVar3;
                this->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) break;
                if (iVar4 > 0xffff || iVar4 < -0xffff) break;

                // Scale by 16
                this->width = iVar1 * 0x10;
                this->height = iVar2 * 0x10;
                iVar5 += 4;
                if (iVar5 > 0xf) break;
            }
        }

        if (*(int*)((char*)source + 0x3c) != 0) {
            void* ptr3c = *(void**)((char*)source + 0x3c);
            outRect2->flag = 1;
            outRect2->left   = *(short*)((char*)ptr3c + 8);
            outRect2->top    = *(short*)((char*)ptr3c + 10);
            outRect2->right  = *(short*)((char*)ptr3c + 0xc);
            outRect2->bottom = *(short*)((char*)ptr3c + 0xe);
            outRect2->width  = (int)*(short*)((char*)ptr3c + 0x18);
            outRect2->height = (int)*(short*)((char*)ptr3c + 0x16);

            iVar5 = 0;
            while (true) {
                iVar1 = outRect2->width;
                iVar2 = outRect2->height;
                if (iVar1 >= 0x10000 || iVar1 <= -0x10000) break;
                if (iVar2 >= 0x10000 || iVar2 <= -0x10000) break;

                // Scale by 2
                iVar3 = iVar1 * 2;
                iVar4 = iVar2 * 2;
                outRect2->width = iVar3;
                outRect2->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) return;
                if (iVar4 > 0xffff || iVar4 < -0xffff) return;

                // Scale by 4
                iVar3 = iVar1 * 4;
                iVar4 = iVar2 * 4;
                outRect2->width = iVar3;
                outRect2->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) return;
                if (iVar4 > 0xffff || iVar4 < -0xffff) return;

                // Scale by 8
                iVar3 = iVar1 * 8;
                iVar4 = iVar2 * 8;
                outRect2->width = iVar3;
                outRect2->height = iVar4;
                if (iVar3 > 0xffff || iVar3 < -0xffff) return;
                if (iVar4 > 0xffff || iVar4 < -0xffff) return;

                // Scale by 16
                iVar5 += 4;
                outRect2->width = iVar1 * 0x10;
                outRect2->height = iVar2 * 0x10;
                if (iVar5 > 0xf) return;
            }
        }
    }
    else {
        // Source has a sub-object at +0x20; use its data
        void* ptr20 = *(void**)((char*)source + 0x20);
        this->flag = 1;
        this->left   = *(short*)((char*)ptr20 + 0x114);
        this->top    = *(short*)((char*)ptr20 + 0x118);
        this->right  = *(short*)((char*)ptr20 + 0x11c);
        this->bottom = *(short*)((char*)ptr20 + 0x120);
        iVar5 = *(int*)((char*)ptr20 + 0x124);
        this->width = 0;
        this->height = 0x10000;
        if (iVar5 != 0) {
            this->width = 0;
            this->height = 0;
            return;
        }
    }
    return;
}