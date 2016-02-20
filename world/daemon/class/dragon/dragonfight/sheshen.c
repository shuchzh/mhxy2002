// By tianlin 2001.5.1,��������ǿ
// sheshen.c 		������

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int calculate_damage(object me, object target, int base_damage, int damge_bonus);
int perform(object me, object target)
{
	string msg, str;
	int mydf;
	int ap, dp, pp;
	int youcps, mycor, mystr, youstr;
	int damage_bonus, damage, wound;
	int delay;
	object ob;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����ս���У���ʲô����\n");

	mydf=(int)me->query_skill("dragonfight",1);
	if(mydf<100) 
		return notify_fail("�����Ϊ����������������������ľ��衣\n");
	mydf=(int)me->query_skill("dragonforce",1);
	if(mydf<100) 
		return notify_fail("�����Ϊ����������������������ľ��衣\n");
	
	if((int)me->query("force")<500) return
	    notify_fail("������������ˡ�\n");

	msg = CYN "$N���ƻӳ���ն��$n����磬\n";
	mycor=me->query_cor();
	youcps=target->query_cps();
	ob=target->query_temp("weapon");
	str="����";
	if(objectp(ob)) str="���е�"+ob->query("name");
	ap=COMBAT_D->skill_power(me, "unarmed", SKILL_USAGE_ATTACK);
	dp=COMBAT_D->skill_power(target,"dodge", SKILL_USAGE_DEFENSE);
	dp/=2;	
	pp=COMBAT_D->skill_power(target,"unarmed", SKILL_USAGE_DEFENSE);
	pp/=2;
	if(objectp(ob)) pp/=2;
	mystr=me->query_str();
	youstr=me->query_str();
	damage_bonus=mystr*(100+me->query("force_factor"))/100;

	if( random(youcps) < 15 || random(ap+dp)>dp) {
		msg += "$n����"+str+"����������ȴ��$Nһ��ץס��\n";
		msg += "$N˳���ϲ���ʹ����"BLINK""HIC"����������"NOR"��\n\n" NOR;
		msg += CYN "$N��Ų���$n����ϥ�ǣ�";
		if(random(ap+pp)>pp) {
			msg += "���������$n��С���ϡ�\n" NOR;
			damage=calculate_damage(me, target, 160, damage_bonus);
			wound=random(damage-(int)target->query_temp("apply/armor"));
			if(damage>0) {
				target->receive_damage("kee", damage, me);
				if(wound>0) target->receive_wound("kee", wound, me);
				msg+=COMBAT_D->damage_msg(damage, "����");
			}
		}
		else msg+="�����$n���ȵ����ˡ�\n" NOR;
		msg += CYN "\n������$N����ţ�����ϥײ��$n�����ߣ�\n";
		msg += "ͬʱ��������ײ��$n�����ţ�";
		if(random(ap+pp)>pp) {
			msg += "�������$n��\n" NOR;
			damage=calculate_damage(me, target, 180, damage_bonus);
			wound=random(damage-(int)target->query_temp("apply/armor"));
			if(damage>0) {
				target->receive_damage("kee", damage, me);
				if(wound>0) target->receive_wound("kee", wound, me);
				msg+=COMBAT_D->damage_msg(damage, "����");
			}
		}
		else msg+="�����$n�����ˡ�\n" NOR;
		msg += CYN "\n$N����˳��������ץס$n�ұۣ���ת����$nˤ�˳�ȥ��";
		if(random(ap+pp)>pp) {
                        msg += "���$nһ��ͷˤ�ڵ��ϡ�\n" NOR;
                        damage=calculate_damage(me, target, 200, damage_bonus);
			wound=random(damage-(int)target->query_temp("apply/armor"));
                        if(damage>0) {
                                target->receive_damage("kee", damage, me);
				if(wound>0) target->receive_wound("kee", wound, me);
                                msg+=COMBAT_D->damage_msg(damage, "����");
                        }
                }
                else msg+="�����$nһ�����ģ�ȴûˤ����\n" NOR;
		message_vision(msg, me, target);
		msg+=COMBAT_D->report_status(target, 0);
	} else {
		msg += "����$p������$P����ͼ�����Խ����\n" NOR;
		message_vision(msg, me, target);
	}
	delay = random(1)+2;
	me->start_busy(delay);
	me->add("force", -300);

	return 1;
}

int calculate_damage(object me, object target, int base_damage, int damage_bonus)
{
	int damage;
	int myexp, youexp;

	damage=base_damage+(damage_bonus+random(damage_bonus))/2;
	myexp=me->query("combat_exp");
	youexp=target->query("combat_exp");
	if(random(youexp)>myexp) {
		damage-=damage/3;
		youexp/=2;
	}
	if (wizardp(me) && me->query("env/combat")=="verbose")
		tell_object(me, sprintf(GRN "damage: %d\n" NOR, damage));

	return damage;
}
