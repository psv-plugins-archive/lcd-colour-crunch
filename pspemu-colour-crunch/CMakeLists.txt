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

add_link_options(
  --entry=module_start
)

# Build self

set(ELF "pspemu-colour-crunch.elf")
set(SELF "pspemu-colour-crunch.skprx")
set(MODULE_INFO "pspemu-colour-crunch.yml")

add_executable("${ELF}"
  pspemu-colour-crunch.c
)

target_link_libraries("${ELF}"
  taihenForKernel_stub
  SceRegMgrForDriver_stub
)

dolce_create_self("${SELF}"
  "${ELF}"
  CONFIG "${MODULE_INFO}"
)
