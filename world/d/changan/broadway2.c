// Room: /changan/broadway2.c
//cglaem...12/12/96.

inherit ROOM;

void create ()
{
  set ("short", "��ٵ�");
  set ("long", @LONG

����һ��������ֱ�Ĺٵ�������ݵ���ʮ�����ۡ�����ͨ��
�ϲ��غ���������ֱ����ƹ��������ǡ�
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"nanyue",
  "north" : __DIR__"zhongnan",
]));
  set("outdoors", 1);

  set("objects", ([ "/d/obj/weapon/throwing/shi.c" : 1, ]));
  setup();
}





