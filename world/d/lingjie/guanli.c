// link
// 灵界管理处，涉及饭卡的充值


#include <ansi.h>
inherit BANK;

void reset_balance(object me);


void create()
{
	set("short", HIC"灵界管理处"NOR);
	set("long", @LONG
这间外表华丽实则内部装修破烂不堪的房子就是灵界管理处了，除了房子
的质量比其他地方好点儿，也找不到什么其他的优点了。房间中央有一个
高大的柜台，差不多比人都高了，上面挂着一张表（ｓｉｇｎ）。
[31m
                      灵  界  管  理  处
[37m
LONG
	);
	
	set("exits", ([
		"out"   	: __DIR__"shengdian3",
	]) );
        set("item_desc", ([
                "sign": @TEXT
这里是灵界管理处，目前我们提供的服务有：

account         查帐。
deposit         存款。
withdraw        取款。
convert         兑换钱币。

TEXT
        ]) );

	set("objects", ([//sizeof() == 1

		__DIR__"npc/guanli-officer" : 1,

			]) );


	set("no_clean_up", 0);

	setup();
}

void init()
{
    reset_balance(this_player());
    ::init();
}

void reset_balance(object me)
{
    int myexp=(me->query("daoxing")+me->query("combat_exp"))/1000;
    int allowed, removed_gold;
    string myid=me->query("id");
    string NPCNAME="管理员";

    if(myexp<1) myexp=1;
    if(myexp>100) myexp=100;
    allowed=myexp*1000000;//each year can have 100 gold, range 100-10000. 
    if (me->query("balance") > allowed)
    {
        me->set("balance_old", me->query("balance"));
        me->set("balance", allowed);
        removed_gold = (me->query("balance_old") - me->query("balance"))/10000;
        log_file("MONEY_RESET", ctime( time() )+"：幽助收缴了"+me->query("name")+"("+me->query("id")+")"+removed_gold+"两黄金。\n");
        tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+RANK_D->query_respect(me)+
                "，这、这真不知怎么说是好．．．\n"NOR);
        tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+
                "昨日爱后余生派人前来察案，发觉你老的黄金来路．．．\n"NOR);
        tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+
                "若不是在下帮你老辩解，你老的钱就全都充公给逍遥了．．．\n"NOR);
    }
    return;
}

