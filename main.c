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
#include <psp2/registrymgr.h>

int _newlib_heap_size_user = 4 * 1024;

int main(int argc, char **argv) { (void)argc; (void)argv;

	int v;
	sceRegMgrGetKeyInt("/CONFIG/DISPLAY/", "color_space_mode", &v);
	sceAVConfigSetDisplayColorSpaceMode(!v);
	sceRegMgrSetKeyInt("/CONFIG/DISPLAY/", "color_space_mode", !v);
	return 0;
}
