#include <ansi.h>
#include <weapon.h>
inherit SWORD;
void create()
{
        set_name( HIC "¾�ɽ�" NOR, ({ "luxian jian", "jian", "sword" ,"luxian"}) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",

"¾�ɽ�\n"
);
                set("value", 0);
                set("material", "purplegold");
                set("sheenness", 40);
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unequip_msg", "$N�����е�$n��������Ľ��ʡ�\n");
        }

        init_sword(100);
        setup();

}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        int damage;
        pro = (int) victim->query_temp("apply/armor_vs_spells");
        dam = (int) me->query("force");

        damage = (int) me->query("force_factor");
        if(dam > pro)
        {
        victim->start_busy(2);
        return HIY "¾�ɽ���Ȼ����ҫ�۵Ĺ�â��$n�۾����������ˡ�\n" NOR;
        }
}
