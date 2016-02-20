// mailbox.c
#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

mapping *mails;

void get_mail_text(mapping mail, string str);

void create()
{
	set_name("����", ({ "mailbox", "box" }) );
	set("long",
		"���Ǹ������䣬���ż����ݶ���ʦ�޷����ܣ�����̸��������˽��\n\n"
		"mailto  <ĳ��>            ���Ÿ����ˡ�\n"
		"forward <�ż����> <ĳ��> ��ĳ����ת�ĸ����ˡ�\n"
		"from                      �鿴�����е��ż���\n"
		"read    <�ż����>        �Ķ�ĳһ���ż���\n"
		"discard <�ż����>        ����һ���ż���\n"
	);
	set("unit", "��");
	set("no_drop", 1);
	set("no_steal", 1);
	set("no_put", 1);
	set("no_beg", 1);
	set("no_get", 1);
	set("no_insert", 1);

	seteuid(getuid());
}

int set_owner(string id)
{
	set("owner_id", id);
	return restore();
}

void init()
{
	object ob;

	if( this_player() && environment()==this_player() ) {
		set_owner( (string)this_player()->query("id") );
		this_player()->set_temp("mbox_ob", this_object());
		set_name( this_player()->name(1) + "������", ({ "mailbox", "box" }) );
		add_action("do_mail", "mailto");
		add_action("do_forward", "forward");
		add_action("do_from", "from");
		add_action("do_read", "read");
		add_action("do_discard", "discard");
	}
}

string query_save_file()
{
	string id;

	if( !stringp(id = query("owner_id")) ) return 0;

	return DATA_DIR + "mail/" + id[0..0] + "/" + id;
}

void receive_mail(mapping mail)
{
	if( !pointerp(mails) ) mails = ({ mail });
	else mails += ({ mail });
	save();
}

void send_mail(string rcvr, mapping mail)
{
	object ppl, ob, mbx;

	// Acquire the login object of receiver and mark the arrival of newmail.
	ob = FINGER_D->acquire_login_ob(rcvr);
	if( !ob ) {
		write("û������˴��ڡ�\n");
		return;
	}
	ob->add("new_mail", 1);
	ob->save();

	// Get the mailbox or make a new one if not found.
	ppl = find_player(rcvr);
	if(ppl)
	{
        tell_object(ppl, HIG "�����ʲ��ܲ������ݸ���һ���ţ�ת�������ˡ�\n" NOR );
		mbx = ppl->query_temp("mbox_ob");
	}
	if( !mbx ) {
		mbx = new(MAILBOX_OB);
		mbx->set_owner(rcvr);
	}

	// Receive the mail and destruct the objects if receiver is off-line.
	mbx->receive_mail(mail);
	if(!ppl) {
		destruct(mbx);
		destruct(ob);
	}
}

int do_mail(string arg)
{
	mapping mail;

	if( this_player()!=environment() ) return 0;

	if( !arg || arg=="" )
		return notify_fail("��Ҫ��˭���ţ�\n");

	mail = ([
		"from":	this_player()->name(1) + "(" + this_player()->query("id") + ")",
		"title": "����",
		"to": arg,
		"time": time(),
		"text": ""
	]);
	write("�ż����⣺");
	input_to("get_mail_title", mail);
	return 1;
}

void get_mail_title(string str, mapping mail)
{
	if( str!="" ) mail["title"] = str;
	write("�ż����ݣ�\n");
	this_player()->edit( (: get_mail_text, mail :) );
}

void get_mail_text(mapping mail, string str)
{
	mail["text"] = str;
	write("��Ҫ���Լ���һ�ݱ�����(y/n)��[n]");
	input_to("confirm_copy", mail);
}

void confirm_copy(string yn, mapping mail)
{
	if( yn[0]=='y' || yn[0]=='Y' ) receive_mail(mail);
	send_mail(mail["to"], mail);
	write("Ok.\n");
}

int do_from()
{
	int i;

	if( !pointerp(mails) || !sizeof(mails) ) {
		write("����������Ŀǰû���κ��ż���\n");
		return 1;
	}
	write("�������������ڹ��� " + sizeof(mails) + " ���ż���\n\n");
	for(i=0; i<sizeof(mails); i++)
		printf("%2d %-40s FM��%-20s\n",
			i+1, mails[i]["title"], mails[i]["from"]);
	write("\n");
	return 1;
}

int do_read(string arg)
{
	int num;

	if( !arg || !sscanf(arg, "%d", num) )
		return notify_fail("��Ҫ����һ���ţ�\n");

	if( !pointerp(mails) || num < 1 || num > sizeof(mails) )
		return notify_fail("û�������ŵ��ż���\n");

	num --;

	printf("�ż����⣺%s\n�� �� �ˣ�%s\n����ʱ�䣺%s\n\n%s\n",
		mails[num]["title"], mails[num]["from"], ctime(mails[num]["time"]), mails[num]["text"] );
	return 1;
}

int do_discard(string arg)
{
	int num;

	if( !arg || !sscanf(arg, "%d", num) )
		return notify_fail("��Ҫ������һ���ţ�\n");

	if( !pointerp(mails) || num > sizeof(mails) )
		return notify_fail("û�������ŵ��ż���\n");

	num --;

	if(num == 0)
		mails = mails[num+1..sizeof(mails)-1];
	else
		mails = mails[0..num-1] + mails[num+1..sizeof(mails)-1];
	save();
	write("Ok.\n");

	return 1;
}

int do_forward(string arg)
{
	string dest;
	int num;
	mapping m;

	if( !arg || sscanf(arg, "%d %s", num, dest)!=2 )
		return notify_fail("��Ҫ����һ����ת�ĸ����ˣ�\n");

	if( !pointerp(mails) || num > sizeof(mails) )
		return notify_fail("û�������ŵ��ż���\n");

	num --;

	m = ([]);
	m["title"] = mails[num]["title"];
	m["text"] = mails[num]["text"];
	m["time"] = mails[num]["time"];
	m["from"] = mails[num]["from"] + "/ת����" + this_player()->query("name");
	m["to"] = dest;
	send_mail( dest, m );
	write("Ok.\n");

	return 1;
}

void owner_is_killed() { destruct(this_object()); }