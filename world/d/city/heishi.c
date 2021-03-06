// 长安黑市   Beeby 7/17/2000

#include <ansi.h>

inherit ROOM;

string *work_msg = ({
        HIC "兵器" NOR,
        HIC "私盐" NOR,
        HIC "大米" NOR,
        HIC "木材" NOR,
        HIC "家俱" NOR,
        HIC "酒" NOR,
        HIC "铁器" NOR,
        HIC "皮货" NOR,
        HIC "马匹" NOR,
        HIC "香料" NOR,
        HIC "药材" NOR,
        HIC "首饰" NOR,
        HIC "衣料" NOR,
        HIC "水果" NOR,
});

void create ()
{
        set ("short", "长安集市");
        set ("long", @LONG
    这里是长安城集市。满街的店铺都挂着一团团、一簇簇的羊角风灯。 
一声接一声的叫卖声在各个街口、小巷深处此呼彼应，连绵不绝。集
市的 入口处，挂着一块牌子(sign)。 
LONG);
        set("item_desc", (["sign" : "在这里你可以做下面的事情。 
join        开始做生意 
", ]));
        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"ximen",
        ]));
//        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_join", "join");
}

int do_join(string arg)
{
	int workid;
	object me=this_player(),ob;
	string msg;
	int i;
	if (me->is_busy())
	 return notify_fail("你正忙着呢!\n");	
	if (me->query_temp("heishi/selling") 
	    && (me->query_temp("heishi/selltime")+60>time()))
	 return notify_fail("你还是先把手头的买卖干完吧!\n");
	if (me->query("sen")<30)
	 return notify_fail("你已经太疲倦了，还是休息一下吧!\n");
	me->add("sen",-30);
	workid=random(sizeof(work_msg));
	msg="$N开始贩卖"+work_msg[workid]+"。\n";
        switch (workid)
	{
	 case 0:
	 {
	     if (random(2)==0)
	       {
                msg+="突然冲过来一队官兵,对$N大声喝道:“大胆反贼！"+
                     "竟敢贩卖兵器! 想造反不成？还不就法!”\n";
		message_vision(msg,me);
		ob=new(__DIR__"npc/xunluobing");
	        ob->kill_ob(me);
        	ob->set_leader(me);
        	me->fight_ob(ob);
		ob->move(environment(me));
		return 1;
	       }
	     break;	
	 }	
	 case 1:
	 { 
		if (random(2)==0)
		{ 
		   if (!me->query_temp("heishi/sale_salt"))
		   {
		     msg+="突然冲过来一队官兵,一把揪住$N,大声喝道:“大胆刁民，"+
		        "竟敢贩卖私盐! 眼里还有没有王法!”\n";
		     msg+="$N赶紧递上一叠银票。\n"+
		        "官兵一边收下，一边说道:“念你初犯，"+
		        "这次就算了,下次再让我们捉住就不会再客气了。”\n";
	  	     message_vision(msg,me);
		     me->set_temp("heishi/sale_salt",1);
		     return 1;
		   }
		   else
		   {
                     msg+="突然冲过来一队官兵,一把揪住$N,大声喝道:“大胆刁民，"+
                        "竟敢贩卖私盐! 眼里还有没有王法!”\n";
                     msg+="$N赶紧递上一叠银票。\n"+
                        "官兵打量了一下$N 突然一瞪眼:“又是你!"+
                        "这次可饶不了你!”\n";
		     msg+="官兵把$N按倒在地，捆上绳索，拖走了。\n";
                     message_vision(msg,me);
                     me->delete_temp("heishi/sale_salt");
		     me->move(__DIR__"silao");
		     if (me->query("startroom"))
			me->set("mystartroom",me->query("startroom"));
		     me->set("startroom","/d/city/silao");
		     msg="咣啷一声，牢门打开来, $N被扔了进来，摔在地上，"+
			"牢门又咣啷一声关上了。\n";
		     message_vision(msg,me);
                     return 1;
		   }
		 }
	 }
	}
	message_vision(msg,me); 
	me->set_temp("heishi/workid",workid);
	call_out("do_sale",3,me);
	me->set_temp("heishi/selling",1);
	me->set_temp("heishi/selltime",time());
	me->start_busy(3);
 	return 1; 
}

int do_sale(object me)
{
	string msg;
	int exp,pot_reward,exp_reward,workid,amount;
	object ob;
	exp=(me->query("combat_exp")+
                me->query("daoxing"))/2;
        if(exp<30000) {
            exp_reward=5+random(2+exp/600);
            pot_reward=1+random(2+exp/3000);
        } else if(exp<500000) {
            exp_reward=10+random(4+exp/6000);
            pot_reward=3+random(2+exp/60000);
        } else if(exp<3000000) {
            exp_reward=15+random(8+exp/60000);
            pot_reward=5+random(4+exp/600000);
        } else {
            exp_reward=200;
            pot_reward=40;
        }
	workid=me->query_temp("heishi/workid");
	switch (workid)
	{
	  case 0:
	  {
		msg="你不动声色的干完了自已的买卖，心中不禁有些得意。\n";
		exp_reward*=4;
		pot_reward*=4;
		break;
	  }
	  case 1:
	  {
		msg="你提心吊胆的卖完了手上的货物，总算松了一口气。\n";
                exp_reward*=2;
                pot_reward*=2;
		break;
	  }
	  default:
		msg="一天的生意结束后，你觉得有些累，但心里还是很愉快。\n";
	  }
	amount=(int)(pot_reward/2);
	amount=amount?amount:1;
	if (exp>500000)
	{
	  msg+="你隐隐间又有些怅然，觉得似乎不该在这市井中混一辈子。\n"+
               "你得到了"+chinese_number(amount)+"两银子。\n";
	} else 
	{  	
	  msg+="你的道行增加了"+COMBAT_D->chinese_daoxing(exp_reward)+
	   ",潜能增加了"+chinese_number(pot_reward)+"点!\n"+
	   "你得到了"+chinese_number(amount)+"两银子。\n";
	  me->add("potential",pot_reward);
	  me->add("daoxing",exp_reward);
	}
	ob=present("silver_money",me);
	if (!ob)
         {
	   ob=new("/obj/money/silver");
	   ob->set_amount(amount);
	   ob->move(me);
         }
	else
	   ob->add_amount(amount);
	write(msg);
	me->delete_temp("heishi/selling");
	me->start_busy(2);
	me->save();
	
	
}
