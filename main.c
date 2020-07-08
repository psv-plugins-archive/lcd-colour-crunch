/*
This file is part of LCD Colour Crunch
Copyright © 2020 浅倉麗子

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <psp2/avconfig.h>
#include <psp2/display.h>
#include <psp2/kernel/clib.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/registrymgr.h>
#include "fnblit.h"

extern char _binary_font_sfn_start[];

int _newlib_heap_size_user = 4 * 1024;

int main(int argc, char **argv) { (void)argc; (void)argv;

	int v;
	sceRegMgrGetKeyInt("/CONFIG/DISPLAY/", "color_space_mode", &v);
	sceAVConfigSetDisplayColorSpaceMode(!v);
	sceRegMgrSetKeyInt("/CONFIG/DISPLAY/", "color_space_mode", !v);

	SceUID mem_id = sceKernelAllocMemBlock(
		"FramebufferMem",
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
		SCE_KERNEL_2MiB,
		NULL);
	if (mem_id < 0) { goto done; }
	void *fb_base;
	sceKernelGetMemBlockBase(mem_id, &fb_base);
	sceClibMemset(fb_base, 0x00, SCE_KERNEL_2MiB);

	fnblit_set_font(_binary_font_sfn_start);
	fnblit_set_fg(0xFFFFFFFF);
	fnblit_set_bg(0x00000000);
	fnblit_set_fb(fb_base, 960, 960, 544);
	fnblit_printf(10, 10, "LCD colour space set to %s mode", !v ? "OLED emulation" : "original");
	SceDisplayFrameBuf fb = {
		sizeof(fb),
		fb_base,
		960,
		SCE_DISPLAY_PIXELFORMAT_A8B8G8R8,
		960,
		544,
	};
	sceDisplaySetFrameBuf(&fb, SCE_DISPLAY_SETBUF_NEXTFRAME);
	sceKernelDelayThread(1 * 1000 * 1000);

done:
	return 0;
}
