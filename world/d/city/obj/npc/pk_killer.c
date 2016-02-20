// by fly@YSZZ

// 2000.9.20

#include <ansi.h>
#define NAME_D "/u/fly/npc/random_name"
inherit NPC;

void kill_ob(object ob);// NPC��killǰ����ִ���������
void check_status(object ob);

string *color_title = ({
HIC"[��ңɽׯ]"NOR+"��������",
HIY"[�ʹ���Ժ]"NOR+"���ڸ���",
HIM"[�׺���]"NOR+"����",
HIM"[�߶���]"NOR+"����",
});
void create()
{
    mapping name;
if (random(5)>2) {
    name = NAME_D->man_name();
    set_name(name["name"],({name["id"]}));
        set("gender", "����" );
   }
else {
    name = NAME_D->woman_name();
    set_name(name["name"],({name["id"]}));
        set("gender", "Ů��" );
   }
   set("title", color_title[random(sizeof(color_title))]);
       set("long",
                "һλ�������ݵĲ�ͷ�����Ĳ��ߣ�������������
                ��˵�Ǵ��Ƹ߼۴Ӿ���������,����������\n"
        );
       set("nickname", HIW"������ͷ"NOR);
        set("attitude", "peaceful");
        set("age", 35+random(50));
       seteuid(getuid());
        set("chat_chance", 20);
        set("chat_msg", ({
               "��ͷͦ��ͦ�ظ�������Ц��������˵�������ˣ���ЩΪ������������һ���ŷ���ӡ� \n",
               (: random_move :)
       }) );
          setup();

}

void init()
{
        object ob;
        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}


void kill_ob(object ob) // NPC��killǰ����ִ��������������ǿ�����Ҫ��Щʲô��
{
 // ����Ҫ����ɱ��һ��ǿ��PKer,�����������趨һ�ε���skill��code
        int max_skill;
        if(query("killing"))  // ֻ����һ�Σ���Ȼ��������kill��ȫ����
                 { 
                        :: kill_ob(ob);
                        return;
                }
                set("killing",ob);  // ��һ�±����ɱ˭
// ���ȵõ���һ��HP��
        set("combat_exp",ob->query("combat_exp")+random(ob->query("combat_exp"))/2);  
        set("max_kee",ob->query("max_kee")*2); 
        set("max_force",ob->query("max_force")); 
        set("eff_kee",ob->query("max_kee")*2);
        set("kee",ob->query("max_kee")*2);
        set("max_sen",ob->query("max_sen")*2);
        set("max_mana",ob->query("max_mana"));
        set("eff_sen",ob->query("max_sen")*2);
        set("sen",ob->query("max_sen")*2);
        set("mana",ob->query("max_mana")*2);
        set("force",ob->query("max_force")*2);
   set("mana_factor", ob->query("max_mana")/50 );
   set("force_factor", ob->query("max_force")/50);

        max_skill=ob->query_skill("dodge");  
// ����Ҫ�Ķ���,��ʱ���

      set_skill("force",max_skill + random(20));
      set_skill("dodge",max_skill + random(20));
      set_skill("parry",max_skill + random(20));
      set_skill("unarmed",max_skill + random(20));
      set_skill("sword",max_skill + random(20));
//      set_skill("NO.1_skill",max_skill + random(20));
           map_skill("force","NO.1_skill");
           map_skill("dodge","NO.1_skill");
           map_skill("parry","NO.1_skill");
           map_skill("unarmed","NO.1_skill");
           set("class","��ңɽׯ");
   set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
           (: perform_action, "sanmai" :),
          (: perform_action, "cimu" :),
          (: perform_action, "sword.cimu" :),
          (: perform_action, "sword.sanmai" :),
        }) );

        set_leader(ob);  // ���ܣ���follow!!
        
        :: kill_ob(ob);
             call_out("check_status",3,ob); 
}

void check_status(object ob)
{
        if(!ob || ob->is_ghost()) {
                destruct(this_object());
                return; }  // ����һ�ξ�����
        if(environment(ob)!=environment()) {
                this_object()->move(environment(ob));  // ������ȫ�ܲ����ˡ�
                message_vision("$N��Ȼ��һ�������������һ������"+ob->name()+"�������ܣ���\n",this_object());
                }
                this_object()->kill_ob(ob);   

        remove_call_out("check_status");
        call_out("check_status",5,ob);  //����ִ��
}