//By tianlin@mhxy and elva@mhxy for 2001.9.27
//部分优化

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("张三丰", ({ "zhang sanfeng", "zhang" }));
	set("nickname", "[1;37m太极[1;33m真人[2;37;0m");
	set("long", 
		"他就是武当派开山鼻祖、当今武林的泰山北斗张三丰真人。\n"
		"身穿一件污秽的灰色道袍，不修边幅。\n"
		"身材高大，年满百岁，满脸红光，须眉皆白。\n");
	set("gender", "男性");
	set("age", 100);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_kee", 3000);
	set("max_sen", 2800);
	set("force", 5700);
	set("max_force", 5700);
	set("mana", 4900);
	set("max_mana", 4900);
       set("force_factor", 140);
       set("mana_factor", 140);
	set("combat_exp", 5000000);
	set("daoxing", 6000000);
        set("chat_msg_combat", ({
 //               (: perform_action, "sword.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
	set_skill("force", 300);
	set_skill("wudang-force", 300);
	set_skill("dodge", 300);
	set_skill("tiyunzong", 300);
	set_skill("unarmed", 300);
	set_skill("taiji-quan", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("taiji-jian", 300);
	set_skill("liangyi-jian", 300);
	set_skill("wudang-xianfa", 300);
	set_skill("spells", 300);
	set_skill("literate", 290);

	map_skill("force", "wudang-force");
	map_skill("spells", "wudang-xianfa");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "liangyi-jian");

	create_family("武当派", 1, "开山祖师");
	set("class", "wudang");

	setup();
       carry_object("/d/wudang1/obj/jian.c")->wield();
}

void attempt_apprentice(object ob)
{
        if ( ((int)ob->query("combat_exp") < 500000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
        if ( ((int)ob->query("daoxing") < 500000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道行方面多下努力啊！");
                return;
        }
	if ((int)ob->query_skill("wudang-force", 1) < 200) {
		command("say 我武当派乃内家武功，最重视内功心法。"); 
		command("say " + RANK_D->query_respect(ob) + 
			"是否还应该在太极神功上多下点功夫？");
		return;
	}
    if ((int)ob->query_skill("wudang-xianfa", 1) < 200)
    {
        command("say 我武当派乃道家武功，高深的武功离不开道学心法。");
        command("say " + RANK_D->query_respect(ob) +
            "是否还应该多读读道德经？");
        return;
    }
	if (ob->query_int() < 30) {
		command("say 我武当派武功全从道藏悟出。");
		command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
		command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
		return;
	}
	command("chat 哈哈哈哈！！！！");
	command("chat 想不到老道在垂死之年，又觅得一个可塑之才，真是可喜可贺。");
	command("recruit " + ob->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
                ob->set("title", "[1;33m武当派[1;37m张三丰[1;31m门下[1;37m弟子[2;37;0m");
}
