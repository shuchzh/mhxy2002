// xiandan2.c δ���ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR "�ɵ�" NOR, ({ "dan", "xian dan", "xiandan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "һ��԰԰�Ļ���ɵ�����˵���˿�����ǿ���ԡ�\n");
                set("value", 10000);
		set("unit", "��");
	}
}


int do_eat(string arg)
{
	object me;

        if (! id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

        me = this_player();
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
        
                tell_object(me, HIM "��ʱ��������ȹ����ѣ�һʱ��ʹ���̣����˹�ȥ��\n" NOR);
                me->add("spi", 1);

        destruct(this_object());
	return 1;
}
void self_dest(object me)
{
    if(!me) return;
    if(!environment(me)) return;
    tell_object(environment(me),name()+
	    "���ڵ��ϣ������ˡ�\n");
    destruct(me);
}
void announce(object who)
{
    if(!this_object()) return;
    if(!who) return;
    CHANNEL_D->do_channel(this_object(), "rumor", 
	    who->query("name")+"��"HIW+
	         	MISC_D->find_place(environment(this_player()))+HIM"�õ��˴�˵�е�"+name()+HIM"��\n");
}
void init()
{ 
	add_action("do_eat", "eat");
       call_out("self_dest",1200000+random(600),this_object());
    remove_call_out("announce");
    call_out("announce",random(10),this_player());
}
