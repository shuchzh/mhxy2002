// created 17-06-2001 ����Ʈ(piao)

inherit ROOM;
void create()
{
        set("short", "��÷ɽׯ");
        set("long", @LONG
������ǽ���ʢ������÷ɽׯ���˵ؾ�ɫ���ˣ�һ���ļ�
�����ɼ�ǧ�˰�̬��÷������÷ɽׯ��ׯ���������Ŵ�ѩ��ÿ
�컹�кö཭������ǰ���ݻ�����ż���������Կ��������к�
�������Ĵ����
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "south" :"/d/changan/seashore2",
    "north" : __DIR__"road",

]));
        set("objects", ([
                __DIR__"npc/yingke" :1,
                        ]) );
  set("outdoors", 1);
        set("coor/x",180);
	set("coor/y",-400);
	set("coor/z",30);
	setup();
        replace_program(ROOM);
}