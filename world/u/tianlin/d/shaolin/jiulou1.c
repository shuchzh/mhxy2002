// Room: /shaolin/jiulou1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "ӭ��¥");
	set("long", @LONG
��Բ������������ӭ��¥����˵�����˲�֪�����˲�����������
ѧʿ���ε��ˣ���ӭ��¥�������޲����ڣ���ȻΪ�����ң�����һ��
���麣�ڵļѻ����Ӵ�ӭ��¥��������¥�²��ü��ף��˿Ͷ��Ǵ�
�ҵ����ˣ������ӣ����ȡ��׾ƾ͸�·ȥ�ˡ�¥����������
LONG
	);

	set("exits", ([
		"east" : __DIR__"nanyang",
		"up" : __DIR__"jiulou2",
	]));

//	set("objects", ([
//		"/d/suburb/xkx/city/npc/xiaoer2" : 1,
//	]));

	setup();
	replace_program(ROOM);
}
