// FUNC_NAME: UIRect::initFromConfig
void __thiscall UIRect::initFromConfig(UIRect* thisRect, UIRect* secondRect, ConfigData* config)
{
    // Initialize both rectangles to default (inactive)
    secondRect->active = 0;
    thisRect->active = 0;
    thisRect->field20 = 0;
    thisRect->field22 = 0;
    secondRect->field20 = 0;
    secondRect->field22 = 0;

    if (config->specialMode == 0) {
        // Set default short fields from config offsets 100 and 0x66
        thisRect->field20 = *(short*)((char*)config + 100);
        thisRect->field22 = *(short*)((char*)config + 0x66);

        if (config->primaryRect != NULL) {
            thisRect->active = 1;
            thisRect->x = *(short*)(config->primaryRect + 8);
            thisRect->y = *(short*)(config->primaryRect + 10);
            thisRect->w = *(short*)(config->primaryRect + 12);
            thisRect->h = *(short*)(config->primaryRect + 14);
            thisRect->scaleX = (int)*(short*)(config->primaryRect + 0x18);
            thisRect->scaleY = (int)*(short*)(config->primaryRect + 0x16);

            int loopCount = 0;
            while (true) {
                int sx = thisRect->scaleX;
                int sy = thisRect->scaleY;
                if (sx >= 0x10000 || sx <= -0x10000 || sy >= 0x10000 || sy <= -0x10000)
                    break;

                int nx1 = sx * 2, ny1 = sy * 2;
                thisRect->scaleX = nx1;
                thisRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    break;

                nx1 = sx * 4; ny1 = sy * 4;
                thisRect->scaleX = nx1;
                thisRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    break;

                nx1 = sx * 8; ny1 = sy * 8;
                thisRect->scaleX = nx1;
                thisRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    break;

                thisRect->scaleX = sx * 16;
                thisRect->scaleY = sy * 16;
                loopCount += 4;
                if (loopCount > 15)
                    break;
            }
        }

        if (config->secondaryRect != NULL) {
            secondRect->active = 1;
            secondRect->x = *(short*)(config->secondaryRect + 8);
            secondRect->y = *(short*)(config->secondaryRect + 10);
            secondRect->w = *(short*)(config->secondaryRect + 12);
            secondRect->h = *(short*)(config->secondaryRect + 14);
            secondRect->scaleX = (int)*(short*)(config->secondaryRect + 0x18);
            secondRect->scaleY = (int)*(short*)(config->secondaryRect + 0x16);

            int loopCount = 0;
            while (true) {
                int sx = secondRect->scaleX;
                int sy = secondRect->scaleY;
                if (sx >= 0x10000 || sx <= -0x10000 || sy >= 0x10000 || sy <= -0x10000)
                    break;

                int nx1 = sx * 2, ny1 = sy * 2;
                secondRect->scaleX = nx1;
                secondRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    return;

                nx1 = sx * 4; ny1 = sy * 4;
                secondRect->scaleX = nx1;
                secondRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    return;

                nx1 = sx * 8; ny1 = sy * 8;
                secondRect->scaleX = nx1;
                secondRect->scaleY = ny1;
                if (nx1 > 0xffff || nx1 < -0xffff || ny1 > 0xffff || ny1 < -0xffff)
                    return;

                secondRect->scaleX = sx * 16;
                secondRect->scaleY = sy * 16;
                loopCount += 4;
                if (loopCount > 15)
                    return;
            }
        }
    } else {
        // specialMode != 0: use direct texture coordinates
        thisRect->active = 1;
        thisRect->x = *(short*)(config->textureData + 0x114);
        thisRect->y = *(short*)(config->textureData + 0x118);
        thisRect->w = *(short*)(config->textureData + 0x11C);
        thisRect->h = *(short*)(config->textureData + 0x120);
        int texFlag = *(int*)(config->textureData + 0x124);
        thisRect->scaleX = 0;
        thisRect->scaleY = 0x10000; // represents 1.0 in fixed-point?
        if (texFlag != 0) {
            thisRect->scaleX = 0;
            thisRect->scaleY = 0;
            return;
        }
    }
}