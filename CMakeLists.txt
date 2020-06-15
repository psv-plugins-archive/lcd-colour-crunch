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

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()

include("$ENV{DOLCESDK}/share/dolce.cmake" REQUIRED)

project(LCDColourCrunch LANGUAGES C)

set(ELF "${PROJECT_NAME}.elf")
set(SELF "${PROJECT_NAME}.self")
set(VPK "${PROJECT_NAME}.vpk")

set(TITLE_NAME "LCD Colour Crunch")
set(TITLE_ID "AKRK00006")
set(TITLE_VER "01.00")

add_executable("${ELF}"
  main.c
)

target_compile_options("${ELF}"
  PRIVATE -O3 -std=c99
  PRIVATE -Wall -Wextra -Wdouble-promotion -Wshadow -Wundef
  PRIVATE -fsingle-precision-constant -fno-common
)

target_link_libraries("${ELF}"
  SceAVConfig_stub
  SceRegistryMgr_stub
)

add_custom_command(OUTPUT boot_param.bin
  COMMAND dolce-make-bootparam app_memsize 0x1000 boot_param.bin
)

dolce_create_self("${SELF}"
  "${ELF}"
  UNSAFE
  BOOT_PARAM ${CMAKE_CURRENT_BINARY_DIR}/boot_param.bin
)

dolce_create_vpk("${VPK}"
  "${TITLE_ID}"
  "${SELF}"
  NAME "${TITLE_NAME}"
  VERSION "${TITLE_VER}"
)
