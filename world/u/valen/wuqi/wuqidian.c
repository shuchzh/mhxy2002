//By tianlin@mhxy for 2001.9.18
//在制作此商店时,我想要是和他们一样都设在npc身上去买东西,有点不大好,
//(1)是npc容易被杀害,要是你给npc设上no_die也行,不过也不怎么地,还没有新
//鲜感,(2)是设在ROOM里面的话,以上的问题就解决了,而且ROOM还很华丽,我自任
//为不错,大家可以模仿的作一下,请不要改作者的名字..谢谢!!!(xixi)
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", NOR"兵器"HIC"★"NOR"商店");
  set ("long", @LONG

[37m         [32;47m     ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂      [1;37;40m▎
[37m         [1;31;47m     [37;42m            [1;35m五[5m[1;36m★[0m[37;42m[1;35m级兵器专卖店[0m[37;42m            [31;47m      [37;40m▎
[37m         [32;47m     [37;42m▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄[1;47m      [40m▎
[37m      [1m   ▕[47m■■■[33;46m[37;47m■■■▕[m
[37m      [1m   ▕[47m■■■[33;46m[37;47m■■■▕[m
[37m      [1m   ▕[47m■■■[33;44m│      │      │      │      │[37;47m■■■▕[m
[37m      [1m   ▕[47m■■■[33;44m├───┼──────┼───┤[37;47m■■■▕[m
[37m      [1m   ▕[47m■■■[33;44m│﹏﹏﹏│﹏﹏﹏│﹏﹏﹏│﹏﹏﹏│[37;47m■■■▕[m
[37m      [1m   ▕[47m■■■[32;43m│※※※│※※※│※※※│※※※│[37;47m■■■▕[m
[1;33m      ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔[m
[37m  [1;41m [NO]  [兵器名]   [加法力]  [重量]  [攻击力]   [加轻功]  [售  价][m
   ( 1)  青铜剑       50       0         20        0        6000
   ( 2)  晴雷剑       80       0         30        0        10000
   ( 3)  蝉翼刀      100       0         40        0        15000
   ( 4)  忘情剑      100       0         35        0        15000
   ( 5)  狮头宝刀    150       0         60        0        35000
   ( 6)  屠龙刀      200       0         100       0        50000
   ( 7)  黄金圣杖    300       300       100       0        150000
[1;41m                                                                           [m
LONG);

  set("exits", ([ /* sizeof() == 4 */
        // "enter": __DIR__"road3",
         "east": __DIR__"daojudian",
]));

        setup();
}

void init()
{
        add_action("do_buy","buy");
}

int do_buy(string arg)
{
        object obj;
        object me=this_player();
        int afford;
        if(me->is_busy())
                return notify_fail(CYN"你现在正忙着呢。\n"NOR);
        switch(arg)
        {
                case "1":
                {
                if( !(afford=me->can_afford(20000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(20000);
                obj = new ("/u/tianlin/wuqi/daoju/dan");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一个"HIG"辟谷丸"NOR"。\n");
                break;
                }
                
                case "2":
                {
                if( !(afford=me->can_afford(50000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(50000);
                obj = new ("/u/tianlin/wuqi/daoju/xieyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一瓶"HIC"泻药"NOR"。\n");
                break;
                }

                case "3":
                {
                if( !(afford=me->can_afford(100000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(10000);
                obj = new ("/u/tianlin/wuqi/daoju/xianyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一包"HIY"仙药"NOR"。\n");
                break;
                }

                case "4":
                {
                if( !(afford=me->can_afford(100000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(10000);
                obj = new ("/u/tianlin/wuqi/daoju/shenyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一包"HIR"神药"NOR"。\n");
                break;
                }
 
                case "5":
                {
                if( !(afford=me->can_afford(500000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(500000);
                obj = new ("/u/tianlin/wuqi/daoju/renshen");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"YEL"千年人参王"NOR"。\n");
                break;
                }

                case "6":
                {
                if( !(afford=me->can_afford(700000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(700000);
                obj = new ("/u/tianlin/wuqi/daoju/bag");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一个"HIW"百宝袋"NOR"。\n");
                break;
                }

                case "7":
                {
                if( !(afford=me->can_afford(200000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(200000);
                obj = new ("/u/tianlin/wuqi/daoju/bi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一块"HIY"纪念币"NOR"。\n");
                break;
                }

                case "8":
                {
                if( !(afford=me->can_afford(90000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(90000);
                obj = new ("/u/tianlin/wuqi/daoju/shaqi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一粒"RED"杀气丸"NOR"。\n");
                break;
                }

                case "9":
                {
                if( !(afford=me->can_afford(150000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(150000);
                obj = new ("/u/tianlin/wuqi/daoju/taowang");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIM"百年猕猴桃王"NOR"。\n");
                break;
                }

                case "10":
                {
                if( !(afford=me->can_afford(2000000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(2000000);
                obj = new ("/u/tianlin/wuqi/daoju/xuelian");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIC"天山雪莲"NOR"。\n");
                break;
                }

                case "11":
                {
                if( !(afford=me->can_afford(1000000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(1000000);
                obj = new ("/u/tianlin/wuqi/daoju/lingzhi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIR"万年灵芝"NOR"。\n");
                break;
                }
        }
return 1;
}

