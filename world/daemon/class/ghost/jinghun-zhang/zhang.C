#include <ansi.h>
#include <skill.h>
inherit SSERVER;
int perform(object me, object target)
{
        int i,j,k,damage;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʹ�ö���ƣ�\n");
        if(!me->is_fighting())
                return notify_fail("����û���ڴ�ܣ�\n");
        if((int)me->query("max_force") < 100 )
                return notify_fail("����ڹ�̫�\n");
        if((int)me->query("force") < 100 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	if((int)me->query_skill("jinghun-zhang", 1) < 40)
        	return notify_fail("��ľ����Ƶȼ�����������ʹ����һ�У�\n");
	i=(int)me->query("combat_exp");
       j=(int)target->query("combat_exp");
             k=(int)me->query_skill("jinghun-zhang");
        me->delete("env/brief_message");
	target->delete("env/brief_message");
message_vision(HIW"\n$N��ȵ�����������"NOR,me,target);
message_vision(HIW"\nһ�ƴ���$n\n"NOR,me,target);
	if (random(i+j)>j) {
            damage=k+random(k);
target->receive_damage("kee",damage);
target->receive_wound("kee",damage/5);
target->start_busy(2);
             if (k>50) k=50;
target->apply_condition("hell_zhang",
(int)target->query_condition("hell_zhang")+1+k/10);
                COMBAT_D->report_status(target);
message_vision(CYN"\n$n����һ�Σ�ֻ������������һ����ɫ����ӡ��\n"NOR,me,target);
}
else message_vision(HIR"\n$n����һ�����㿪����һ�ƣ�\n"NOR,me,target);
me->receive_damage("sen", 30);
        me->add("force", -100);
	me->receive_damage("kee", 30);
 if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
}
}
if (me->query_temp("zhang_busy")) return notify_fail("���������ʤ������ƶ�ʹ�Ͳ����ˡ�\n");
        me->add("force", -100);
    me->start_busy(1);
return 1;
}