/*
 * dot-font.h
 *
 *  Created on: Aug 16, 2013
 *      Author: agu
 */

#ifndef DOT_FONT_H_
#define DOT_FONT_H_

#include "stm32-template.h"

struct DotFont
{
    uint8_t width;
    uint8_t height;
    uint8_t indent;
    uint8_t length;
    const uint8_t *pattern;
};

extern const DotFont vfont_7x3;
extern const DotFont vfont_5x3;
extern const DotFont vfont_6x3;
extern const DotFont vfont_8x3;
extern const DotFont vfont_7x5;


#endif /* DOT_FONT_H_ */
