//【蜀山剑派】dhxy-evil 2000.7.5
//yushu修改 2001.2
inherit NPC;
#include <ansi.h>
int do_report();
void create()
{
        set_name("李逍遥", ({ "li xiaoyao", "li", "xiaoyao" }));
        set("title","蜀山剑派入门弟子");
        set("long", 
"李逍遥身材较瘦，长的浓眉阔眼，气宇暄昂。\n");
        set("gender", "男性");
        set("age", 18);
	 set("class", "xiake");
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("per", 30);
        set("kee", 2800);
        set("max_kee", 2800);
        set("sen", 1600);
        set("max_sen", 1600);
        set("force", 4800);
        set("max_force", 2400);
        set("mana", 4800);
        set("max_mana", 2400);
        set("force_factor", 60);
        set("mana_factor", 60);
        set("combat_exp", 1800000);
        set("daoxing", 2500000);
        set_skill("force", 250);
        set_skill("dodge", 240);
        set_skill("unarmed", 230);
        set_skill("fumozhang", 230);
        set_skill("parry", 250);
        set_skill("sword", 250);
        set_skill("canxin-jian", 270);
  set_skill("shushan-force", 240);
  set_skill("spells", 280);
        set_skill("zuixian-steps",240);
        set_skill("literate",120);
        set_skill("xianfeng-spells",250);
        map_skill("spells", "xianfeng-spells");
        map_skill("unarmed", "fumozhang");
        map_skill("force", "shushan-force");
        map_skill("dodge", "zuixian-steps");
        map_skill("parry", "canxin-jian");
        map_skill("sword", "canxin-jian");
        set("inquiry", ([
                "救出来了"    : (: do_report :),
        ]));
        setup();
        create_family("蜀山派", 3, "弟子");
        carry_object("/obj/cloth")->wear();
        carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="蜀山派" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师叔见笑了。\n");
			else command("say 师姑见笑了。\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师兄太客气了。\n");
			else command("say 师妹太客气了。\n");
		}
		else 
		{
			command("consider");
			command("say 看在你诚心诚意的份上,我收你为徒!\n");
			command("recruit " + ob->query("id") );
                     ob->set("shushan/xiangsi_perform",1);

		}
	}
            else
	{
		command("say 看在你诚心诚意的份上,我收你为徒!\n");
		command("recruit " + ob->query("id") );
              ob->set("shushan/xiangsi_perform",1);

	}

	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "蜀山派李逍遥弟子");
              }
              return 0;
}

void init()
{
  object ob;

  ::init();
  if( interactive(ob = this_player()) && !is_fighting() )
  {
    remove_call_out("greeting");
    call_out("greeting", 1, ob);
  }
}
void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
        say( "李逍遥说道：这位" + RANK_D->query_respect(ob) +
"，能不能帮我救出灵儿！她被关进镇妖塔里了！\n");
}

int do_report()
{
 int i=random(500)+1;
 object me = this_player();
 if(me->query("obstacle/shushan") == "done" || me->query("obstacle/shenglingzhu") != "done")
        return 0;
else if(me->query("shushan/zhanyi")) { 
 me->set("zhanyi/zhenyaota",1);
 me->delete("shushan/zhanyi");
 me->add("daoxing",3000+i);
 me->add("potential",1000);
        me->add("obstacle/number",1);
          me->set("obstacle/shushan","done");
 message("system",HIC"〖"HIW"镇妖塔传讯"HIC"〗"HIY+me->query("name")+HIG"救出[1;37m镇妖塔[1;32m里的赵灵儿，受到奖励！[2;37;0m\n"NOR,users());    
 tell_object(me,"你赢得了"+chinese_number(3)+"年"+chinese_number(i/4)+"天"+chinese_number((i-(i/4)*4)*3)+"时辰的道行和"+
 chinese_number(1000)+"点潜能\n");
 me->save();
 } 
 else 
 {
 command("say 谢谢你！不能再麻烦你啦！");
 }
 return 1;
}



