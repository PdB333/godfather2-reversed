// FUNC_NAME: ConfigLoader::loadFromStream

void __thiscall ConfigLoader::loadFromStream(int thisPtr, Stream* stream) {
    Stream_init(stream);              // FUN_0046c710 - likely initialize stream state
    Stream_setMagic(stream, 0xc1ae9ce7); // FUN_0043aff0 - set magic number for parsing

    char hasMore = Stream_hasMore(stream); // FUN_0043b120
    while (hasMore == 0) {
        Stream_readNext(stream);          // FUN_0043b210 - advance to next entry
        uint type = Stream_readType(stream); // FUN_0043ab70 - read type identifier

        switch (type) {
        case 0: { // String field 0
            Stream_readNext(stream);
            String str = Stream_readString(stream); // FUN_0043ab90
            String_set(thisPtr + 0x50, str);        // FUN_004089b0 (offset +0x50)
            break;
        }
        case 1: { // String field 1
            Stream_readNext(stream);
            String str = Stream_readString(stream);
            String_set(thisPtr + 0x58, str);        // offset +0x58
            break;
        }
        case 2: { // Vector4
            Stream_readNext(stream);
            Vector4* vec = (Vector4*)Stream_readPointer(stream); // FUN_0043abc0
            *(uint32*)(thisPtr + 0x64) = vec->x;   // offset +0x64 (100)
            *(uint32*)(thisPtr + 0x68) = vec->y;   // offset +0x68
            *(uint32*)(thisPtr + 0x6C) = vec->z;   // offset +0x6C
            *(uint32*)(thisPtr + 0x70) = vec->w;   // offset +0x70
            break;
        }
        case 3: { // Pointer field 1 (with offset +0x60)
            int ptr = Stream_readNext(stream); // returns address of a struct
            *(uint32*)(thisPtr + 0x60) = *(uint32*)(ptr + 8); // read at struct+8
            break;
        }
        case 4: { // Handle 0
            Stream_readNext(stream);
            String id = Stream_readString(stream);
            *(uint32*)(thisPtr + 0x74) = Handle_resolve(id); // FUN_004dafd0
            break;
        }
        case 5: { // Handle 1
            Stream_readNext(stream);
            String id = Stream_readString(stream);
            *(uint32*)(thisPtr + 0x78) = Handle_resolve(id);
            break;
        }
        case 6: { // Handle 2
            Stream_readNext(stream);
            String id = Stream_readString(stream);
            *(uint32*)(thisPtr + 0x7C) = Handle_resolve(id);
            break;
        }
        case 7: { // Pointer field 2 (offset +0x84)
            int ptr = Stream_readNext(stream);
            *(uint32*)(thisPtr + 0x84) = *(uint32*)(ptr + 8);
            break;
        }
        case 8: { // Handle 3
            Stream_readNext(stream);
            String id = Stream_readString(stream);
            *(uint32*)(thisPtr + 0x80) = Handle_resolve(id);
            break;
        }
        case 9: { // Pointer field 3 (offset +0x88)
            int ptr = Stream_readNext(stream);
            *(uint32*)(thisPtr + 0x88) = *(uint32*)(ptr + 8);
            break;
        }
        case 10: { // Pointer field 4 (offset +0x8C)
            int ptr = Stream_readNext(stream);
            *(uint32*)(thisPtr + 0x8C) = *(uint32*)(ptr + 8);
            break;
        }
        case 11: { // Pointer field 5 (offset +0x90)
            int ptr = Stream_readNext(stream);
            *(uint32*)(thisPtr + 0x90) = *(uint32*)(ptr + 8);
            break;
        }
        case 12: { // Pointer field 6 (offset +0x94)
            int ptr = Stream_readNext(stream);
            *(uint32*)(thisPtr + 0x94) = *(uint32*)(ptr + 8);
            break;
        }
        }

        Stream_advance(stream); // FUN_0043b1a0
        hasMore = Stream_hasMore(stream);
    }
}