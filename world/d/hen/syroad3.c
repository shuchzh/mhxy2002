// by happ@YSZZ
inherit ROOM;

void create ()
{
  set ("short", "商业街");
  set ("long", @LONG

        这里非常热闹，有教堂，酒吧，教堂，你在这可以赚到很多的
    钱，只要你肯干活，赚钱是没有问题的拉，北面是一家[1;33m餐厅[m，南面
    是一个[1;33m教堂[m。

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "east": __DIR__"syroad2",
         "west": __DIR__"syroad4",
          "north": __DIR__"canting",
         "south": __DIR__"jiaotang",
]));

        setup();
}
