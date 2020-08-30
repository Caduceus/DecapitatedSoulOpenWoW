# Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
	Custom/Professions_NPC.cpp
	Custom/ragefire_creature_scripts.cpp
	Custom/Template.cpp
    Custom/Transmog/Transmogrification.h
    Custom/Transmog/Transmogrification.cpp
    Custom/Transmog/Transmogrifier.cpp
	Custom/npc_enchantment.cpp
	Custom/GOMove/GOMove.cpp
	Custom/Reforging/Reforging.cpp
	Custom/Beastmaster/Beastmaster.cpp
	Custom/Npc_trainer/npc_trainer.cpp
	Custom/max_level_item_script/max_level_item_script.cpp
	Custom/duel_reset.cpp
	Custom/learn_spells_on_level.cpp
)

message("  -> Prepared: Custom")
