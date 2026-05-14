#include "cbin_font.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static inline void* malloc_cpy(void* src, size_t sz) {
    void* p = lv_malloc(sz);
    LV_ASSERT_MALLOC(p);
    memcpy(p, src, sz);
    return p;
}

static inline void addr_add(void** addr, uintptr_t add) {
    if(*addr)
        *addr = (void*)((uintptr_t)*addr + add);
}

lv_img_dsc_t* cbin_img_dsc_create(uint8_t* bin_addr) {
    lv_img_dsc_t* img_dsc = malloc_cpy(bin_addr, sizeof(lv_img_dsc_t));
    addr_add((void**)&img_dsc->data, (uintptr_t)bin_addr);
    return img_dsc;
}

lv_font_t* cbin_font_create(uint8_t* bin_addr) {
    lv_font_t* font = malloc_cpy(bin_addr, sizeof(lv_font_t));

    font->get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt;
    font->get_glyph_bitmap = lv_font_get_bitmap_fmt_txt;

    bin_addr += (uintptr_t)font->dsc;
    lv_font_fmt_txt_dsc_t* dsc = (lv_font_fmt_txt_dsc_t*)malloc_cpy(bin_addr, sizeof(lv_font_fmt_txt_dsc_t));
    font->dsc = dsc;

    addr_add((void**)&dsc->glyph_bitmap, (uintptr_t)bin_addr);
    addr_add((void**)&dsc->glyph_dsc, (uintptr_t)bin_addr);

    if(dsc->cmap_num) {
        uint8_t* cmaps_addr = bin_addr + (uintptr_t)dsc->cmaps;
        dsc->cmaps = (lv_font_fmt_txt_cmap_t*)malloc(sizeof(lv_font_fmt_txt_cmap_t)*dsc->cmap_num);

        uint8_t* ptr = cmaps_addr;
        for(int i=0; i<dsc->cmap_num; i++) {
            lv_font_fmt_txt_cmap_t* cm = (lv_font_fmt_txt_cmap_t*)&dsc->cmaps[i];
            cm->range_start = *(uint32_t*)ptr; ptr += 4;
            cm->range_length = *(uint16_t*)ptr; ptr += 2;
            cm->glyph_id_start = *(uint16_t*)ptr; ptr += 2;
            cm->unicode_list = (const uint16_t*)(*(uint32_t*)ptr); ptr += 4;
            cm->glyph_id_ofs_list = (const void*)(*(uint32_t*)ptr); ptr += 4;
            cm->list_length = *(uint16_t*)ptr; ptr += 2;
            cm->type = (lv_font_fmt_txt_cmap_type_t)*(uint8_t*)ptr; ptr += 1;
            ptr += 1; // padding

            addr_add((void**)&cm->unicode_list, (uintptr_t)cmaps_addr);
            addr_add((void**)&cm->glyph_id_ofs_list, (uintptr_t)cmaps_addr);
        }
    }

    if(dsc->kern_dsc) {
        uint8_t* kern_addr = bin_addr + (uintptr_t)dsc->kern_dsc;
        if(dsc->kern_classes == 1) {
            lv_font_fmt_txt_kern_classes_t* kcl = (lv_font_fmt_txt_kern_classes_t*)malloc_cpy(kern_addr, sizeof(lv_font_fmt_txt_kern_classes_t));
            dsc->kern_dsc = kcl;
            addr_add((void**)&kcl->class_pair_values, (uintptr_t)kern_addr);
            addr_add((void**)&kcl->left_class_mapping, (uintptr_t)kern_addr);
            addr_add((void**)&kcl->right_class_mapping, (uintptr_t)kern_addr);
        } else if(dsc->kern_classes == 0) {
            lv_font_fmt_txt_kern_pair_t* kp = (lv_font_fmt_txt_kern_pair_t*)malloc_cpy(kern_addr, sizeof(lv_font_fmt_txt_kern_pair_t));
            dsc->kern_dsc = kp;
            addr_add((void**)&kp->glyph_ids, (uintptr_t)kern_addr);
            addr_add((void**)&kp->values, (uintptr_t)kern_addr);
        }
    }

    return font;
}

void cbin_font_delete(lv_font_t* font) {
    lv_font_fmt_txt_dsc_t* dsc = (lv_font_fmt_txt_dsc_t*)font->dsc;
    lv_free((void*)dsc->cmaps);
    lv_free((void*)dsc->kern_dsc);
    lv_free((void*)dsc);
    lv_free((void*)font);
}