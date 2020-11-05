#
# Copyright © 2020 浅倉麗子
#
# This file is part of LCD Colour Crunch
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
#

cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "DolceSDK toolchain file")
set(DOLCESDK_CMAKE_FILE "$ENV{DOLCESDK}/share/dolce.cmake" CACHE PATH "DolceSDK CMake functions file")
include("${DOLCESDK_CMAKE_FILE}" REQUIRED)

option(CMAKE_TLS_VERIFY "Verify TLS" ON)
include(ExternalProject REQUIRED)

project(lcd-colour-crunch LANGUAGES C)

add_compile_options(
  -Os -std=c11
  -Wall -Wextra -Wdouble-promotion -Wshadow -Wundef
  -fsingle-precision-constant -fno-common -flto
  -ftree-vectorize -funsafe-math-optimizations
)

add_link_options(
  -nostdlib
)

# Build self

set(ELF "lcd-colour-crunch.elf")
set(SELF "eboot.bin")
set(BOOTPARAM "${CMAKE_CURRENT_BINARY_DIR}/boot_param.bin")

add_executable("${ELF}"
  main.c
  "${SFN_OBJ}"
)

target_link_libraries("${ELF}"
  SceAVConfig_stub
  SceLibc_stub
  SceLibKernel_stub
  SceNotificationUtil_stub
  SceRegMgr_stub
  SceSysmodule_stub
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
set(TITLE_VER "01.03")

dolce_create_vpk("${VPK}" "${TITLE_ID}" "${SELF}"
  NAME "${TITLE_NAME}"
  VERSION "${TITLE_VER}"
  FILE
    right.txt sce_sys/about/right.txt
    right.gim sce_sys/about/right.gim
)

# Build kernel module for PSPEmu

add_subdirectory(pspemu-colour-crunch)
