// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// Room: /d/4world/center.c
inherit ROOM;

void create ()
{
  set ("short", "[37m八百里天河[m");
  set ("long", @LONG
这就是八百里天河了,果然是浩浩荡荡,一望无际.
河边的水草甚是丰盛,你不由地想把马放(fang)出
去.
LONG);
  set("exits", ([
  "east" : __DIR__"xitian",
]));

  setup();
}
void init()
{
    add_action("do_fang", "fang");
    set("no_clean_up", 0);
        setup();
}

int do_fang(string arg)
{
        object me, ob, a, b;
        me=this_player();
        if ( !arg || ((arg != "horse") ))
                return notify_fail("你要把什么放出去？\n");
  if ( !present("tian-ma", this_player()) )
     return notify_fail("你身没带天马,放什么放啊!!\n");
  if(objectp(a=present("tianpeng yuanshuai", environment(me))))
  return notify_fail("天蓬元帅大喝一声:小贼,看见本帅来了还敢偷我的水草!!\n");
  if(!me->query_temp("marks/骑"))
  return notify_fail("你还没去骑上天马,怎么能把它放出去呢!!!\n");
//  if(!me->query_temp("give_horse"))
//  return notify_fail("这马恐怕不是你自己去御马监要的吧!!\n");
  message_vision("$N下了马,把马牵到河边,让它自行吃草。\n",me);
  message_vision("只听见哗啦啦一声水响,天河中钻出了几条人影!!\n",me);
  me->delete_temp("marks/骑",1);
  ob=present("tianpeng yuanshuai");
     if( !ob) {
  seteuid(getuid());
  ob=new("/d/sky/npc/zhu");
}
  ob->move(__DIR__"river");
   return 1;
}
