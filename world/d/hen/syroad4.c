// by happ@YSZZ
inherit ROOM;

void create ()
{
  set ("short", "商业街");
  set ("long", @LONG

        这里非常热闹，有教堂，酒吧，教堂，你在这可以赚到很多的
    钱，只要你肯干活，赚钱是没有问题的拉，北面是一家[1;35m伐木场[m，南面
    是专门[1;35m摆地摊的地方[m。

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "east": __DIR__"syroad3",
         "west": __DIR__"syroad5",
          "north": __DIR__"famu",
         "south": __DIR__"ditan",
]));

        setup();
}
