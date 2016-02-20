// by happ@YSZZ
inherit ROOM;
#include <hen.h>

void create ()
{
  set ("short", "伐木场");
  set ("long", @LONG

        这里你可以输入 [1;32m fa_mu [m 去砍伐一些树木，苦力啊~~。

LONG);

  set("exits", ([ /* sizeof() == 4 */
        "south": __DIR__"syroad4",
]));
        setup();
}

void init()
{
                add_action("do_work","fa_mu");
}

int do_work()
{
        object ob = this_player();

        if( !present("zhandou ji",ob) ) return 0;


        ob->command_function("cls");
        ob->command_function("shape");

        ob->add("hen/life",-15);
        ob->add("hen/happy",-10);
        ob->add("hen/satisfy",-10);
        ob->add("hen/dirty",12);

        cat(LOGER);

        if( time() - ob->query("hen/last_famu") < 180 )
        {
        write("看来小鸡很讨厌重复做同一件事情。\n");
        ob->add("hen/affection",-1);
        return 1;
        }

        ob->add("hen/money",400+random(20));
        ob->set("hen/last_famu",time());
        ob->add("hen/max_life",3);
        ob->add("hen/mold",-3);
        return 1;
}
