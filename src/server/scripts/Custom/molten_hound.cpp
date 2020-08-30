/*
*
///*    Name                  SpellID   CAST-TIME      DAMAGE */
/*SPELL_FIREBALL             = 70282, // 3 sec       ,  6198-7202*/
/*SPELL_FIRE_SPIT            = 66796, // 1 sec       ,  5088-5912*/
/*SPELL_BLAST_NOVA           = 74392, // 2 sec       ,  5688-7312*/
/*SPELL_CLEAVE				 = 74524,
/SPELL_WARSTOMP				 = 24375,
/SPELL_FIREBALLVOLLEY		 = 22425,
/SPELL_CONFLAGRATION		 = 23023,
/SPELL_STOMP                 = 58663,
/SPELL_FLAME_BUFFET          = 34121, // Flame Buffet - every 1, 5 secs in phase 1 if there is no victim in melee range and after Dive Bomb in phase 2 with same conditions
/SPELL_FLAME_QUILLS          = 34229, // Randomly after changing position in phase after watching tons of movies, set probability 20%
/SPELL_REBIRTH               = 34342, // Rebirth - beginning of second phase(after losing all health in phase 1)
/SPELL_REBIRTH_2             = 35369, // Rebirth(another, without healing to full HP) - after Dive Bomb in phase 2
/SPELL_MELT_ARMOR            = 35410, // Melt Armor - every 60
/SPELL_CHARGE                = 35412, // Charge - 30 sec cooldown
/SPELL_SUPERCHARGE           = 61920,
/SPELL_DIVE_BOMB_VISUAL      = 35367, // Bosskillers says 30 sec cooldown, wowwiki says 30 sec colldown, DBM and BigWigs addons says ~47 sec
/SPELL_DIVE_BOMB             = 35181, // after watching tonns of movies, set cooldown to 40+rand()%5.
/SPELL_BERSERK = 45078, // 10 minutes after phase 2 starts(id is wrong, but proper id is unknown)
/SPELL_CARRION_SWARM		 = 31306,
/SPELL_SLEEP				 = 31298,
/SPELL_VAMPIRIC_AURA	     = 38196,
/SPELL_INFERNO				 = 31299,
/SPELL_IMMOLATION			 = 31303,
/SPELL_INFERNO_EFFECT	     = 31302,
/SPELL_IMPALE                = 28783,
/SPELL_CAUTERIZING_FLAMES    = 59466, //Only in heroic
/SPELL_FIREBOLT              = 54235,
/H_SPELL_FIREBOLT            = 59468,
/SPELL_FLAME_BREATH          = 54282,
/H_SPELL_FLAME_BREATH        = 59469,
/SPELL_LAVA_BURN             = 54249,
/H_SPELL_LAVA_BURN           = 59594

/CREATURE_EMBER_OF_ALAR      = 19551, // Al'ar summons one Ember of Al'ar every position change in phase 1 and two after Dive Bomb. Also in phase 2 when Ember of Al'ar dies, boss loses 3% health.
/SPELL_EMBER_BLAST           = 34133, // When Ember of Al'ar dies, it casts Ember Blast

CREATURE_FLAME_PATCH_ALAR    = 20602, // Flame Patch - every 30 sec in phase 2
SPELL_FLAME_PATCH            = 35380, //
/
/
/
//EVENT_CONFLAGRATION,
//EVENT_CLEAVE,
//EVENT_BLAST_NOVA,

enum AssemblyActions
{
ACTION_SUPERCHARGE                           = 1,
};


///Charge timer////
if (Charge_Timer <= diff)
{
Unit* target= SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true);
if (target)
DoCast(target, SPELL_CHARGE);
Charge_Timer = 30000;
}
else
Charge_Timer -= diff;


///FlamePatch Timer///
if (FlamePatch_Timer <= diff)
{
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
{
Creature* Summoned = me->SummonCreature(CREATURE_FLAME_PATCH_ALAR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 120000);
if (Summoned)
{
Summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
Summoned->SetObjectScale(Summoned->GetObjectScale() * 2.5f);
Summoned->SetDisplayId(11686);
Summoned->setFaction(me->getFaction());
Summoned->SetLevel(me->getLevel());
Summoned->CastSpell(Summoned, SPELL_FLAME_PATCH, false);
}
}
FlamePatch_Timer = 30000;
}
else
FlamePatch_Timer -= diff;
}
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum YELLS
{
	SAY_AGGRO = 0
};

enum Spells
{
	SPELL_FLAME_BREATH			= 54282,
	SPELL_LAVA_BURN				= 54249
};

enum Events
{
	EVENT_FLAME_BREATH = 1,
	EVENT_LAVA_BURN    = 2
};

class molten_hound : public CreatureScript
{
public:
	molten_hound() : CreatureScript("molten_hound") { }

	struct molten_houndAI : public ScriptedAI
	{
		molten_houndAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() override
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{

			Talk(SAY_AGGRO);
			events.ScheduleEvent(EVENT_FLAME_BREATH, 15000);
			events.ScheduleEvent(EVENT_LAVA_BURN, 5000);

		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_FLAME_BREATH:
					DoCastVictim(SPELL_FLAME_BREATH);
					if (me->GetVictim() && me->EnsureVictim()->HasAura(SPELL_FLAME_BREATH))
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
							me->TauntApply(target);
					events.ScheduleEvent(EVENT_FLAME_BREATH, 30000);
					break;
				case EVENT_LAVA_BURN:
					DoCastVictim(SPELL_LAVA_BURN);
					events.ScheduleEvent(EVENT_LAVA_BURN, 10000);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new molten_houndAI(creature);
	}
};

void AddSC_molten_hound()
{
	new molten_hound();
}
