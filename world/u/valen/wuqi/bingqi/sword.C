//By tianlin@mhxy for 2002.1.2.
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(RED "������ƽ�" NOR, ({"jueqing sword", "sword", "jian", "jueqing"}));
        set_weight(10000);
                set("unit", "��");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ��������ħ�ı�����\n");
                set("value", 220000);
	         set("wield_msg","$n��ৡ��شӽ����е���������$N�����У����⻹أ��������ͣ��\n");
	         set("unwield_msg","$N�����е�$n�������䣬��ɫ���������ˣ�\n");
		  set("weapon_prop/courage", 10);
        }
        init_sword(80);
        setup();
}