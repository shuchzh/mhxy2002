// modify by ken 2001.3.9
//By tianlin@mhxy for 2002.1.24.����mieyaoϵͳ
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_mieshen();
string ask_cancel();

void create()
{
   set_name("����", ({ "yan yun", "xiao", "yun","zhongyun", }));
   set("title", "ħ�̷���");
   set("long", @LONG
��λ������˵�������˵㣬��ȴ����ħ���˵����ӣ�Ҳ��ħ�̵�����ʦ��
��Ϊ��ѧԨԴ���书������һ����Ҳ��һ���ĺ��֡�
LONG);
   set("gender", "����");
   set("age", 17);
   set("attitude", "friendly");
   set("class", "evil");
   set("str",100);
   set("per",100);
   set("max_kee", 1000);
   set("max_gin", 1000);
   set("max_sen", 1000);
   set("force", 1000);
   set("max_force", 1000);
   set("force_factor", 10);
   set("max_mana", 1000);
   set("mana", 1000);
   set("mana_factor", 10);
   set("combat_exp", 90000);
   set_skill("literate", 70);
   set_skill("spells", 70);
   set_skill("tianmo", 70);
   set_skill("unarmed", 70);
   set_skill("tigerfight", 70);
   set_skill("dodge", 70);
   set_skill("dimo-steps", 70);
   set_skill("blade", 70);
   set_skill("parry", 70);
   set_skill("force", 70);
   set_skill("evil-force", 70);
   set_skill("sword", 70);
   set_skill("nature",70);
   set_skill("tianmo-blade", 70);
   set_skill("tianxian-sword", 70);
   map_skill("spells", "tianmo");
   map_skill("unarmed", "tigerfight");
   map_skill("dodge", "dimo-steps");
   map_skill("force", "evil-force");
   map_skill("parry", "tianmo-blade");
   map_skill("blade", "tianmo-blade");
   map_skill("sword", "tianxian-sword");
   set("chat_chance_combat", 20);
   set("chat_msg_combat", ({
    (: perform_action, "blade", "tiandirenmo" :),
  }) );


   create_family("ħ��", 2, "����");
    set("inquiry", ([
     "����" : (:ask_mieshen:),
   "cancel": (:ask_cancel:),
   "����": (:ask_cancel:),
    ]));

   setup();
   carry_object("/d/obj/cloth/choupao")->wear();
   carry_object("/d/mojiao/obj/fireblade")->wield();
// carry_object("/u/ken/obj/long-blade");
}

void attempt_apprentice(object ob)
{

   command("look " + ob->query("id") );
   command("recruit " + ob->query("id") );
   return;   
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "evil");
        }
}
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("û�õĶ�����");
}
else
{
     return ("���������𣿣�");
}
}
string ask_mieshen()
{
   object me=this_player();
   
   if(me->query("family/family_name")!="ħ��")
      return ("�㲻�Ǳ�������!");

   command("pat "+me->query("id"));
   command("say �úú�,��ȥ��أ�");
   return "/d/obj/mieyao"->query_yao(me);
}

