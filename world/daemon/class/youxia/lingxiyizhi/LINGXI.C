// lingxi.c ��Ϭһָ

#include <ansi.h>

inherit SSERVER;

#include <combat.h>

int perform(object me, object target)
{
	string msg;
	object weapon;
	int damage, p;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��"HIY"��Ϭһָ"NOR"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/family_name") != "��������" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á�"HIR"�������"NOR"��?\n");

        if( (int)me->query_skill("lingxiyizhi", 1) < 100 )
                return notify_fail("�����Ϭһָ������죬�޷�ʹ�á�"HIY"��Ϭһָ"NOR"����\n");

	weapon = me->query_temp("weapon");
	if (weapon) return notify_fail("��Ϭһָ�����ʹ�á�\n");

        if ( (int)me->query("force") < 500)
                return notify_fail("��������������޷�ʹ�á�"HIY"��Ϭһָ"NOR"����\n");

        msg = HIY "$N˫��һǰһ�󣬻����������ָͻ��һ��������������һ�ɣ������С�������ֱϮ$nǰ�ء�\n"NOR;

        damage = (int)me->query_skill("lingxiyizhi", 1) + (int)me->query_skill("unarmed", 1) + 100;
	damage += random(damage / 2);
	if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 3) {
                msg += HIR"$n�������������ۡ���һ������ָ������ǰ�أ�\n"NOR;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage / 3);
                p = (int)target->query("kee") * 100 / (int)target->query("max_kee");
		msg += RED "$n�ؿ�һ���ʹ����е��أ�\n" ;
	} 
	else if (random(me->query("combat_exp")) > (int)target->query("combat_exp") * 2 / 3) {
                msg += HIC"$n���Ա�һ�����ù��˾��磬û�뵽���ָ����Ȼ�л�������$n����ת������������$p�ĺ󱳡�\n"NOR;
                target->receive_damage("kee", damage / 3);
                target->receive_wound("kee", damage / 9);
                p = (int)target->query("kee") * 100 / (int)target->query("max_kee");
		msg += RED "$n�����ؿ��е�ʹ��\n" ;
	}
	else {
                msg += HIC"$n���Ա�һ�����ù��˾��磬ȴ��Ȼ�������ָ����Ȼ�л�������æ��ֻ��һ��ǰ�˲ſ��������ģ���Ǳ�֮����\n" NOR;
	}
	message_vision(msg, me, target);
        me->add("force", -300);
        me->start_busy(2);

	return 1;
}