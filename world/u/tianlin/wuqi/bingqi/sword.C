//By tianlin@mhxy for 2002.1.2.
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(WHT "���Ǻ��⽣" NOR, ({"hanguang jian", "sword", "jian", "bingpo"}));
        set_weight(10000);
                set("unit", "��");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ���ñ�����ı�����\n");
                set("value", 220000);
                set("rumor_msg",1);
                set("is_monitored", 1);
                set("no_sell",1);
                set("no_get",1);
                set("no_give",1);
                set("no_drop",1);
	         set("wield_msg","$n"HIB"��ৡ��شӽ����е���������$N"HIB"�����У����⻹أ��������ͣ��\n"NOR);
	         set("unwield_msg",HIB"$N�����е�"NOR"$n"HIB"�������䣬��ɫ���������ˣ�\n"NOR);
		  set("weapon_prop/courage", 10);
        }
        init_sword(100+random(100));
        setup();
}