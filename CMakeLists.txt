# This file is part of LCD Colour Crunch
# Copyright © 2020 浅倉麗子
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "DolceSDK toolchain file")
set(DOLCESDK_CMAKE_FILE "$ENV{DOLCESDK}/share/dolce.cmake" CACHE PATH "DolceSDK CMake functions file")
include("${DOLCESDK_CMAKE_FILE}" REQUIRED)

project(lcd-colour-crunch LANGUAGES C)

add_compile_options(
  -Os -std=c99
  -Wall -Wextra -Wdouble-promotion -Wshadow -Wundef
  -fsingle-precision-constant -fno-common -flto
  -ftree-vectorize -funsafe-math-optimizations
)

add_link_options(
  -nostdlib
)

# Build font

set(FONT_BASE "terminus-font-4.48")
set(FONT_FILE "ter-u28b.bdf")
set(SFN_FILE "font.sfn")
set(SFN_OBJ "${SFN_FILE}.o")

file(DOWNLOAD
  "https://sourceforge.net/projects/terminus-font/files/${FONT_BASE}/${FONT_BASE}.tar.gz/download"
  "${FONT_BASE}.tar.gz"
  EXPECTED_HASH SHA256=34799c8dd5cec7db8016b4a615820dfb43b395575afbb24fc17ee19c869c94af
)

add_custom_command(OUTPUT "${SFN_FILE}"
  DEPENDS "${FONT_BASE}.tar.gz"
  COMMAND "${CMAKE_COMMAND}" -E tar xzf "${FONT_BASE}.tar.gz" "${FONT_BASE}/${FONT_FILE}"
  COMMAND "${CMAKE_COMMAND}" -E rename "${FONT_BASE}/${FONT_FILE}" "${FONT_FILE}"
  COMMAND bit2sfn -r "Basic Latin" "${FONT_FILE}" "${SFN_FILE}"
)

add_custom_command(OUTPUT "${SFN_OBJ}"
  DEPENDS "${SFN_FILE}"
  COMMAND "${CMAKE_LINKER}" --relocatable --format=binary --output="${SFN_OBJ}" "${SFN_FILE}"
)

# Build self

set(ELF "lcd-colour-crunch.elf")
set(SELF "lcd-colour-crunch.self")
set(BOOTPARAM "${CMAKE_CURRENT_BINARY_DIR}/boot_param.bin")

add_executable("${ELF}"
  main.c
  "${SFN_OBJ}"
)

target_link_libraries("${ELF}"
  fnblit
  SceAVConfig_stub
  SceDisplay_stub
  SceKernelThreadMgr_stub
  SceLibKernel_stub
  SceRegistryMgr_stub
  SceSysmem_stub
)

add_custom_command(OUTPUT "${BOOTPARAM}"
  COMMAND dolce-make-bootparam app_memsize 0x1000 "${BOOTPARAM}"
)

dolce_create_self("${SELF}"
  "${ELF}"
  UNSAFE
  BOOT_PARAM "${BOOTPARAM}"
)

# Build VPK

set(VPK "lcd-colour-crunch.vpk")
set(TITLE_NAME "LCD Colour Crunch")
set(TITLE_ID "AKRK00006")
set(TITLE_VER "01.02")

dolce_create_vpk("${VPK}" "${TITLE_ID}" "${SELF}"
  NAME "${TITLE_NAME}"
  VERSION "${TITLE_VER}"
)
