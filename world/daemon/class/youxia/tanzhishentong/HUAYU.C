// huayu.c ���컨��

#include <ansi.h>
#include <combat.h>
inherit SSERVER;


int perform(object me, object target)
{
        string msg;
   string desc_msg="";
        int sword_level;
        string str;
	object weapon;
	int damage, num, lvl, p;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��"HIM"���컨��"NOR"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        lvl = (int)me->query_skill("tanzhishentong", 1);
        if (lvl < 100) return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʹ�� ��"HIM"���컨��"NOR"����\n");


        if ( (int)me->query("force") < 500)
                return notify_fail("��������������޷�ʹ�á�"HIM"���컨��"NOR"����\n");

        sword_level=(random(11));
   if ( sword_level <= 1 ) desc_msg = "" ; else
       desc_msg = chinese_number(sword_level);
  if ( sword_level > 9 ) desc_msg = "��";

message_vision(HIC"\n$N�ִӻ���ץ�������ʹ��һ��"HIM"�����컨�꡹"HIC"����ָ������������ص��˳�ȥ��\n"NOR,me,target); 
message_vision(HIW"        ��"HIM"��"HIW"��                                        ��"HIM"��"HIW"��\n\n"NOR,me,target); 
msg = HIW "                ��"HIM"��"HIW"��                        ��"HIM"��"HIW"��\n\n"NOR;
        damage = lvl * 2 + (int)me->query_skill("unarmed", 1);
	damage += random(damage / 3);
	if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 4) {
                msg += HIR"\n$n���������������ۡ��ؼ�������"+desc_msg+"ʮ����������У�\n"NOR;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage / 3);
                p = (int)target->query("kee") * 100 / (int)target->query("max_kee");
                msg += RED "\n$nֻ������ǰһ��������İ���������һ����\n"NOR;
        } 


        else {
                msg += HIC"$n�ŵø�æ��ͷ����������Ǳ������Ա�һ�������ſ����ض��˹�ȥ��\n" NOR;
	}
                     if (target->query("eff_kee")<0 || !living(target))  
{str=target->name()+"��"+""HIW""+me->name()+""HIM""+"�ó�����ľ��С�"HIW"���컨��"HIM"��ɱ���ˡ���˵ʬ���ϴ�����"+desc_msg+"ʮ�ദ������";
        message("channel:rumor",HIM"��"HIW"��Ѩ����"HIM"��ĳ�ˣ�"+str+"\n"NOR,users());
                       }

        message_vision(msg, me, target);
        me->add("force", -300);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));  ;
	me->start_busy(2);

	return 1;
}