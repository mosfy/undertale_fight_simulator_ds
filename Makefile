# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= undertale_fight_simulator
GAME_TITLE	:= undertale_fight_simulator
GAME_SUBTITLE	:= by mosfy

# Source code paths
# -----------------

GFXDIRS		:= graphics
BINDIRS		:= data

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile
