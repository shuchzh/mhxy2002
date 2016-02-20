
// ��������
// "level": ����ڶ����еĵȼ�(1~?)
// 1: һ�㶴�� 
// 2: ���� 
// 3: ���� 
// 4: ���� 
// 5: ������ (��1��)
// 6: ���� (��1��)
// "title": ����ͷ��
// "info1": ������1 (��������)
// "info2": ������2
// "info3": ������3
// info:
// ([
//    level:
//    title:
//    info1:
//    info2:
// ])
#include <ansi.h>
#include <armor.h>
#define CLUB_NAME "������"
#define CLUB_ID "drinks"
#define CLUB_CHANNEL "drinks"
#define CLUB_MARK "drinks pai"
inherit ITEM;
private string *members_level = ({
	"����", //0
	"����", //1
	"����", //2
	"����", //3
	"����", //4
	"������", //5
	"����", //6
});
void create()
{
	set_name(HIR"�����"NOR,({"drinks pai","pai","club_mark"}));
	set_weight(600);
	if( clonep() ) set_default_object(__FILE__);
	else
	{
		set("value",0);
		set("material","iron");
		set("no_drop",1);
		set("no_sell",1);
		set("no_sac",1);
		set("unit","��");
	set("long",@LONG
����һ����ɫ��ľ��, ����֤���Լ��ǿ������һ���ӡ�
�������(help drinks)���鿴��ʲô����ָ������˽������
����ʷ������(about drinks)��ȡ�ý�һ�������ϡ�

LONG
);
	}
	set("club_id",CLUB_ID);
	set("club",CLUB_NAME);
        set("sub_club",({"����","����","״Ԫ��","Ů����"}));
	set("club_max_level",6);
	set("armor_prop/shield", 1);
	setup();
	set("volume",1);
}

int query_autoload() { return 1; } //save_item

void init()
{
 mapping info;
 int level;
 if(environment(this_object())!=this_player()) return;
 level=CLUB_D->check_member(CLUB_ID,getuid(this_player()));
 if(level==0)
 {
 	if(wizardp(this_player()))
 	{
 		 info = ([
		 "level": wiz_level(this_player()),
		 "title": "�������ؼ�����",
		 "info1": "��",
		 "info2": ctime(time()),
		 "info3": ""
		 ]);
		 CLUB_D->add_member(CLUB_ID,getuid(this_player()),info);
	}
	else 
	{
 		tell_object(this_player(),this_object()->name()+"ͻȻ�������Ϸɳ���������ʧ��Զ����\n");
 		this_player()->delete("club");
 		destruct(this_object());
 		return;
 	}
 }
 switch(level)
 {
  case 6:
		add_action("do_handover","handover");
  case 5:
		add_action("no_suicide","suicide"); //��ֹ��ɱ
  case 4:
		add_action("do_givepower","givepower");
		add_action("do_listmember","listmember");
  case 3:
  		add_action("do_accept","jieshou");
		add_action("do_kickout","kickout");
		add_action("do_subleader","subleader");
		add_action("do_retire","retire");
  case 2:
		add_action("do_include","include");
		add_action("do_dismiss","dismiss");
  default:
   		add_action("do_help","help");
   		add_action("do_about","about");
   		add_action("do_members","members");
   		add_action("do_leaveclub","leaveclub");
 }
}

int filter_members(object ppl,string *list)
{
        if( !environment(ppl) ) return 0;
        if( member_array(getuid(ppl),list)!=-1 ) return 1;
        return 0;
}

string show_level(object user)
{
 int level,rank;
 mapping info;
 string str;
 if(wizardp(user)) return "��������Ա���������ؼ�����  ";
 level=user->query("combat_exp")/100000;
 if(level>100) 	str = "��????????��";
 else if(level<11)	str = "���� "+chinese_number(level)+" ����";
 else if(level<21) 	str = "����"+chinese_number(level)+"����";
 else if(level%10==0)   str = "����"+chinese_number(level)+"����";
 else str = "��"+chinese_number(level)+"����";
 info=CLUB_D->query_member_info(CLUB_ID,getuid(user));
 rank=info["level"];
 switch(rank)
 {
 	case 6: str+="��������ͷ�ϴ�  "; break;
 	case 5: str+="�����︱����    "; break;
 	case 4: str+="�����ﳤ��      "; break;
 	case 3: str+="�����ﳬ������  "; break;
 	case 2: str+=info["info1"]+"������    "; break;
 	default: 
 		if(info["info1"]!="��")
 		{
 			str+=info["info1"]+"��Ա      "; break;
 		} else str+="������һ�㶴��  ";
 }
 return str;
}

int sort_member(object ob1, object ob2)
{
	int lv1,lv2;
	lv1=CLUB_D->check_member(CLUB_ID,getuid(ob1));
	lv2=CLUB_D->check_member(CLUB_ID,getuid(ob2));
	if(lv1 == lv2) return (int)ob1->query("level") - (int)ob2->query("level");
	else return (lv1 - lv2);
}

int do_members(string arg)
{
	object *users,me;
	string str,*list;
	int i,ppl_cnt,idle;
	me=this_player();
//	list=CLUB_D->club_members(CLUB_ID);
//	users = filter_array( users(), "filter_members", this_object(),list );
	users = CLUB_D->find_online_members(CLUB_ID);
	str = "�� "+CLUB_NAME+": \n";
	str += "��������������������������������������������������������������������������\n";

	users = sort_array(users, "sort_member", this_object());

	ppl_cnt = 0;
	i = sizeof(users);
	while( i-- )
	{
			// Skip those users in login limbo.
			if(!me->visible(users[i]) && wizardp(users[i]) ) continue;
			str = sprintf("%s%12s%-16s %s(%s)",
				str,
				show_level(users[i]),
				RANK_D->query_level(users[i]),
				users[i]->name(1),
				users[i]->query("id"),
			);
			if(users[i]->query_temp("killer")) str+=HIR" [ɱ�˷�]"NOR;
			idle=query_idle(users[i]);
			if(users[i]->query_temp("invis")) str+=HIB"(����)"NOR;
			if(users[i]->query_temp("netdead")) str+=HIG"<������>"NOR;
			if(idle>60) str +=sprintf(HIY" (����%d����)"NOR,idle/60);
			str +=sprintf("\n"NOR);
			ppl_cnt++;
	}
	str += "��������������������������������������������������������������������������\n";
	str = sprintf("%sĿǰ���� %d λ��Ա������.\n", str, ppl_cnt);
	this_player()->start_more(str);
	return 1;
}

int do_include(string arg)
{
	string sub;
	object ob,me;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("include <����>\n");
        else
        {
                ob = present(arg, environment(me));
	        if(!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me ) return notify_fail("�������������\n");
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
		if(sizeof(ob_info))
		{
			if(me_info["level"] != 2 ) return notify_fail("ֻ�з������ܽ�����������á�\n");
			if(!stringp(sub=me_info["info1"])) return notify_fail("ֻ�з������ܽ�����������á�\n");
			if(ob_info["level"] != 1 || ob_info["info1"]!="��")
				return notify_fail("ֻ��һ�㶴�ڿ���������ķ��á�\n");
			ob_info["info1"]=sub;
			CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
		 	message_vision("$N��$n����"+sub+", ������$n�ļ��˵: ���Ϳ���ı����ˡ�\n",me,ob);
		 	ob->save();
		 	return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}

int do_dismiss(string arg)
{
	string sub;
	object ob,me;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("dismiss <����>\n");
        else
        {
                ob = present(arg, environment(me));
	        if(!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me ) return notify_fail("�������������\n");
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));		
		if(sizeof(ob_info))
		{
			if(!sub=me_info["info1"] || me_info["level"]!=2 ) return notify_fail("ֻ�з������������Աְ��\n");
			if(ob_info["level"] != 1 ) return notify_fail("�㲻���ʸ����Է���ְ��\n");
			if(ob_info["info1"] != sub) return notify_fail("�Է�����������ķ��á�\n");
			ob_info["info1"]="��";
			CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
		 	message_vision("$N�����$n��"+sub+"��ְ��, ҡҡͷ˵: ������һ���˲�...���ǿ�ϧ����\n",me,ob);
		 	ob->save();
		 	return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}
//����
int do_accept(string arg)
{
	string *clubs;
	object ob,mark,me;
	mapping info;
	me=this_player();
        if(!arg) return notify_fail("��Ҫ��˭����"+CLUB_NAME+"��\n");
        else
        {
                ob = present(arg, environment(me));
	        if (!ob) return notify_fail("�������������\n");
	        if(!userp(ob) || ob==me ) return notify_fail("�������������\n");
		if(ob->query_temp("joinclub") != me->query("id") )
		{
			return notify_fail("�Է���û�����������붴(joinclub).\n");
		}
		clubs=CLUB_D->find_player_club(getuid(ob));
		if(sizeof(clubs)>0)
		{
			if(clubs[0]==CLUB_ID) return notify_fail("�Է��Ѿ���"+CLUB_NAME+"��һ�����ˡ�\n");
			else return notify_fail("�Է��Ѿ������˱�Ķ��ɡ�\n");
		}
		 else
		{
		 mark=new(base_name(this_object()));
		 if(!mark) return notify_fail("��������ȡ��ʧ�ܡ�\n");
   //	 if( !mark->can_move(ob) ) return notify_fail(ob->name(1)+"�ò���"+mark->query("name")+"��\n");
		 message_vision("$N����$nһ"+mark->query("unit")+mark->query("name")+", ��¡�ص�ӭ��$n��Ϊ"+CLUB_NAME+"��һ���ӡ�\n",me,ob);
		 info = ([
		 "level": 1,
		 "title": "������һ�㶴��",
		 "info1": "��",
		 "info2": ctime(time()),
		 "info3": me->name_id(1)
		 ]);
		 CLUB_D->add_member(CLUB_ID,getuid(ob),info);
		 mark->move(ob);
		 ob->add("channels", ({"drinks"}));
                 ob->add("club","������");
		 ob->save();
		}
	}
	return 1;
}

int do_kickout(string arg)
{
	string *tuned_ch;
	object ob,mark,me;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("��Ҫ��˭�߳�"+CLUB_NAME+"��\n");
        else
        {
                ob = present(arg, environment(me));
	        if (!ob) return notify_fail("�������������\n");
	        if(!userp(ob) || ob==me ) return notify_fail("�������������\n");
				
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));	
		
		if(sizeof(ob_info))
		{
			if(ob_info["level"] >= me_info["level"])
				return notify_fail("�㲻���ʸ񽫶Է��߳�"+CLUB_NAME+"��\n");
			if( wiz_level(ob) > wiz_level(me) && wizardp(ob))
				return notify_fail("�㲻���ʸ񽫶Է��߳�"+CLUB_NAME+"��\n");
			tuned_ch = ob->query("channels");
			if( pointerp(tuned_ch) && member_array(CLUB_CHANNEL, tuned_ch)!=-1 )
			{
				tuned_ch -= ({ CLUB_CHANNEL });
				ob->set("channels", tuned_ch);
			}
			//ob->delete("club");
			if(!mark=present(CLUB_MARK,ob))
			{
				write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
 				message_vision("$Nû����$n��"+mark->query("name")+", ��ǿ��$n�˳�"+CLUB_NAME+"��\n",me,ob);
 				destruct(mark);
 			}
 			CLUB_D->remove_member(CLUB_ID,getuid(ob));
 			ob->save();
 			return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}

int do_subleader(string arg)
{
	string id,sub;
	object ob,me,mark;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("subleader <����> to <������>\n");
        else
        {
        	if( sscanf(arg, "%s to %s", id, sub)!=2 ) return notify_fail("subleader <����> to <������>\n");
                ob = present(id, environment(me));
	        if(!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me ) return notify_fail("�������������\n");

		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));	
		
		if(sizeof(ob_info))
		{
			if(ob_info["level"] != 1)
				return notify_fail("ֻ��һ�㶴�ڿ��Գ�Ϊ��������\n");
			if( (int) member_array(sub, query("sub_club"))<0 )
				return notify_fail("Ŀǰ���õķֶ�Ϊ <������> <������> <������> <������> \n");
			ob_info["level"]=2;
			ob_info["info1"]=sub;
			CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
			if(!mark=present(CLUB_MARK,ob))
			{
				write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
	 			message_vision("$N��$n����Ϊ"+sub+"������, ����$n��������һ����\n",me,ob);
	 			mark->move(ob);
	 		}
	 		ob->save();
	 		return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}

int do_retire(string arg)
{
	string sub;
	object ob,me,mark;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("retire <����> \n");
        else
        {
                ob = present(arg, environment(me));
	        if(!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me) return notify_fail("�������������\n");
		
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
		
		if(sizeof(ob_info))
		{
			if(ob_info["level"] != 2) return notify_fail("���󲢲��Ƿ�������\n");
			sub=ob_info["info1"];

			ob_info["level"]=1;
			ob_info["info1"]="��";
			CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);

			if(!mark=present(CLUB_MARK,ob))
			{
				write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
	 			message_vision("$N�����$n��"+sub+"������ְ��\n",me,ob);
	 			mark->move(ob);
	 		}
	 		ob->save();
	 		return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}

int do_givepower(string arg)
{
	string id,type,res;
	int level;
	object ob,me,mark;
	mapping me_info,ob_info;
	me=this_player();
	
        if(!arg) return notify_fail("givepower <����> to <�ȼ�>\n");
        else
        {
        	if( sscanf(arg, "%s to %d", id, level)!=2 ) return notify_fail("givepower <����> to <�ȼ�>\n");
                ob = present(id, environment(me));
	        if(!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me) return notify_fail("�������������\n");
		
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
		
		if(sizeof(ob_info))
		{
			if(ob_info["level"] >= me_info["level"]) return notify_fail("��û���ʸ�ı�Է���ְ��ȼ���\n");
			if( wiz_level(ob) > wiz_level(me) && wizardp(ob))
					return notify_fail("��û���ʸ�ı�Է���ְ��ȼ���\n");
			if(level >= me_info["level"])
				return notify_fail("��û���ʸ������Է���ְ��ȼ�������ȼ���\n");
			if(level == ob_info["level"])
				return notify_fail("�Է��Ѿ���"+(string)members_level[level]+"�ˡ�\n");
			if(level > 5 || level < 1 )
				return notify_fail("Ŀǰ�ȼ���Ϊ <1:����> <2:����> <3:����> <4:����> <5:������> <6:����> \n");
			if( level > ob_info["level"] )
			{
				type="����";
				res ="����$n��������һ��";
			}
			else
			{
				type = "��";
				res ="������$n�ļ������$n�ܽ���\����";
			}
			switch(level)
			{
				case 1:
					ob_info["level"]=1;
					ob_info["info1"]="��";
		 			ob_info["info2"]=ctime(time());
		 			ob_info["info3"]=me->name_id(1);
					break;
				case 2:
					return notify_fail("����subleaderָ����ָ��һ�����졣\n");
					break;
				case 3:
					ob_info["level"]=3;
					ob_info["info1"]="��";
		 			ob_info["info2"]=ctime(time());
		 			ob_info["info3"]=me->name_id(1);
					break;
				case 4:
					ob_info["level"]=4;
					ob_info["info1"]="��";
		 			ob_info["info2"]=ctime(time());
		 			ob_info["info3"]=me->name_id(1);
					break;
				case 5:
					ob_info["level"]=4;
					ob_info["info1"]="��";
		 			ob_info["info2"]=ctime(time());
		 			ob_info["info3"]=me->name_id(1);
					break;
				case 6:
					return notify_fail("����handoverָ����ָ��Ȩ�ƽ���\n");
					break;
				default: return notify_fail("��������\n");
				
			}
			CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
			if(!mark=present(CLUB_MARK,ob))
			{
				write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
				message_vision("$N��$n��ְλ�ȼ�"+type+"Ϊ"+(string)members_level[level]+"(�ȼ�"+(string)level+"), "+res+"��\n",me,ob);
				mark->move(ob);
			}
			ob->save();
			return 1;
		}
		 else return notify_fail("�Է���û�м���"+CLUB_NAME+"��\n");
	}
	return 1;
}

int do_handover(string arg)
{
	object ob,mark,me;
	mapping me_info,ob_info;
	me=this_player();
        if(!arg) return notify_fail("��Ҫ����Ȩ�ƽ���˭��\n");
        else
        {
                ob = present(arg, environment(me));
	        if (!ob) return notify_fail("�������������\n");
		if(!userp(ob) || ob==me) return notify_fail("�������������\n");
		
		if(CLUB_D->query_club_leader(CLUB_ID)!=getuid(me)) return notify_fail("�㲻�������Ķ����쵼�ˡ�\n");
		
		me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
		ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
		if(sizeof(ob_info))
		{
		 	CLUB_D->set_club_leader(CLUB_ID,getuid(ob));
		 	
		 	ob_info["level"]=6;
		 	ob_info["info1"]="��";
		 	ob_info["info2"]=ctime(time());
		 	ob_info["info3"]=me->name_id(1);
		 	CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
			
			me_info["level"]=4;
		 	me_info["info1"]="��";
		 	me_info["info2"]=ctime(time());
		 	me_info["info3"]=me->name_id(1);
			CLUB_D->set_member(CLUB_ID,getuid(me),me_info);
		 	
		 	mark=present(CLUB_MARK, me);
		 	if(!mark)
		 	{
		 		write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
				mark->move(me);
			}
			mark=present(CLUB_MARK, ob);
		 	if(!mark)
		 	{
		 		write("��������ȡ��ʧ�ܡ�\n");
			}
			else
			{
				mark->move(ob);
			}
			message_vision("$N��"+CLUB_NAME+"����ָ��Ȩ�ƽ���$n��\n",me,ob);
			message( "channel:drinks",CYN"��"+CLUB_NAME+"��"+me->name(1)+"("+capitalize(me->query("id"))+")��"+CLUB_NAME+"ָ��Ȩ�ƽ���"+ob->name(1)+"("+capitalize(ob->query("id"))+")��\n"NOR, users() );
			ob->save();
			me->save();
			return 1;
		}
		 else return notify_fail("�Է�������"+CLUB_NAME+"��һ���ӡ�\n");
	}
	return 1;
}

int do_leaveclub(string arg)
{
	string *tuned_ch;
	object mark,me;
	me=this_player();
	
	if(CLUB_D->query_club_leader(CLUB_ID)==getuid(me))
		return notify_fail("������Ƚ���Ȩת�Ʋ����뿪"+CLUB_NAME+"��\n");
	CLUB_D->remove_member(CLUB_ID,getuid(me));
	message_vision("$N�����˳���"+CLUB_NAME+"��\n",me);
	message( "channel:drinks",CYN"��"+CLUB_NAME+"��"+me->name(1)+"("+capitalize(me->query("id"))+")�����˳���"+CLUB_NAME+"��\n"NOR, users() );
	tuned_ch = me->query("channels");
	if( pointerp(tuned_ch) && member_array(CLUB_CHANNEL, tuned_ch)!=-1 )
	{
			tuned_ch -= ({ CLUB_CHANNEL });
			me->set("channels", tuned_ch);
	}
	me->delete("club");
	if(!mark=present(CLUB_MARK,me))
	{
		write("��������ȡ��ʧ�ܡ�\n");
	} else destruct(mark);
	me->save();
	return 1;
}

int no_suicide(string arg)
{
	if(CLUB_D->query_club_leader(CLUB_ID)==getuid(this_player()))
	{
		write("��Ϊ"+CLUB_NAME+"�߼�����, ����ָ��Ȩ֮ǰ��������, ���������ˡ�\n");
		return 1;
	}
	return 0;
}

int do_listmember(string arg)
{
	string *list,*members,temp,output;
	int i,j;
	mapping club;
	list=CLUB_D->club_members(CLUB_ID);
	club=CLUB_D->query_club_record(CLUB_ID);
	members=keys(club);
	output="\nĿǰ"+CLUB_NAME+"�Ǽ��а��ĳ�Ա��:\n";
	if(arg=="long")
	{
		for(i=this_object()->query("club_max_level");i>0;i--)
		{
			for(j=0;j<sizeof(members);j++)
			{
				if(club[members[j]]["level"]==i) output=sprintf("%s %12s ����ȼ�: %d\n",output,members[j],i);
			}
		}
		output=sprintf("%s \nĿǰ%s������: %d ����Ա��\n",output,CLUB_NAME,sizeof(members));
		write(output);
		return 1;
	}
	temp=CLUB_D->query_club_leader(CLUB_ID);
	output=sprintf("%s �쵼��: %12s\n",output,temp);
	list-=({temp});
	output=sprintf("%s ����:\n",output,temp);
	output+=CLUB_D->show_club_members(CLUB_ID);
	output=sprintf("%sĿǰ%s������: %d ����Ա��\n",output,CLUB_NAME,sizeof(members));
	write(output);
	return 1;
}


int do_help(string arg)
{
 if(arg=="drinks")
 {
  write(@HELP

       ��������������������������������������������������������������������
       ��                      ��������ĸ���˵��                        ��
       ���������������������������������Щ������������������Щ�������������
       ��  ָ���ʽ                    ��˵��              ��Ȩ��        ��
       ���������������������������������੤�����������������੤������������
       ��  help plate                  ��������ѶϢ        ������        ��
       ��  drinks <���ѶϢ>           ������ר��Ƶ��      ������        ��
       ��  members                     ���г����϶����Ա  ������        ��
       ��  leaveclub                   �������˳�����      ������        ��
       ��  include <����>              ����ĳ���������    ������ר��    ��
       ��  dismiss <����>              ��ȡ��ĳ�˷���ְ��  ������ר��    ��
       ��  accept <����>               ����ĳ�˼��붴��    ����������    ��
       ��  kickout <����>              ����ĳ���������    ����������    ��
       ��  subleader <����> to <������>������ĳ��Ϊ������  ����������    ��
       ��  retire <����>               ������ĳ�˷�����ְλ����������    ��
       ��  givepower <����> to <�ȼ�>  ���ı�ĳ�˵�ְλ    ����������    ��
       ��  handover <����>             ������ְ�񽻽�      ������        ��
       ��  listmember                  ����������          ����������    ��
       ���������������������������������ة������������������ة�������������
	 �� ʹ�� accept ָ�����Է����� joinclub ָ�����������Ч��
         �� ������Ŀǰ���ĸ�����: �����á��������á�����״Ԫ�á�����Ů���á���
         �� �ȼ���Ϊ: <1:����> <2:����> <3:����> <4:����> <5:������> <6:����>��

HELP
  );
  return 1;
 }
 return 0;
}
int do_about(string arg)
{
 if(arg=="drinks")
 {
  write(@ABOUT
���������������

    

ABOUT
  );
  return 1;
 }
 return 0;
}