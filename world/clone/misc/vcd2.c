#include <ansi.h>

inherit ITEM;
void create()
 {
    set_name("家庭影院", ({"vcd"}) );
    set_weight(1000);
    if( clonep() )
           set_default_object(__FILE__);
    else {
        set("unit", "台");
        set("long", "一台高级家庭影院,上面有play,shut,kala,stop一些字样.\n");
         set("no_get",1);
         set("value",10000);
    }
    setup();
}

void init()
{
       add_action("do_play", "play");
}


int do_play()
{
                if (this_object()->query_temp("play")==1) return notify_fail("现在正在放着ＶＣＤ呢。\n");
                if (this_object()->query_temp("kala")!=0) return notify_fail("现在正有人唱卡啦ＯＫ呢。\n");
                this_object()->set_temp("play",1);
                call_out("start_play",2);
                return 1;
}

int start_play()
{
message("channel:chat",HIR+"〖"HIG"魔幻电台"HIR"〗："NOR+HIY"一个古怪的盒子在作怪了。\n"+NOR,users());
        call_out("continue_play",1,-1); 
        return 1;       
}

int continue_play(int release)
{

string *str1=({
"\n\n                 [1;33m  大话西游之女儿国 [m               \n",
    "师徒四人终于来到女儿国的王宫。\n",
    "唐僧  ：KAO！排场真大，你们看这里的装潢设计一定用了3DMAX加PHOTOSHOP，\n",
    "        简直是COOL毙了！\n",
    "猪八戒：是啊，这里真是太棒了，比俺高老庄还要豪华！\n",
    "孙悟空：说你是只猪你还真是只猪，人家这是皇宫，你们高老庄打\n",
    "        实了算最多也就能算个富农，你还以为你是李世民他们家\n",
    "        亲戚啊？透豆！\n",
    "沙僧  ：大师兄，别跟他一般见识，瞧他长得那样，猪头猪脑哪哪\n",
    "         跟您猴一样的精明呢？\n",
    "孙悟空：那是！\n",
    "           。。。。。。\n",
    "女儿国王：各位就是从东土大唐而来去西天取经的大师么？\n",
    "猪八戒小声对唐僧说：我KAO！这MM长得真是标致。（口水滴哒的特写）\n",
    "唐僧  ：是啊，你看她天使面容,魔鬼身材,要咪咪有咪咪,要PP有PP,\n",
    "        该大的地方大,该小的地方小,该凸的地方凸,该凹的地方凹,\n",
    "        。。。。。真是樱桃小嘴一点点，杨柳细腰赛皮管，燕语莺\n",
    "        声啊。。。。。。（鼻血一滴一滴往下流）\n",
    "孙悟空一{鼻血：我KAO！洋妞嘛，我最讨厌了。。。。。。\n",
    "沙僧鼻血长流：我觉得还可以。。。。。。\n",
    "猪八戒：我KAO！她在挖鼻孔耶！你看。。。。。。她伸出纤纤玉手点\n",
    "        出中。。。啊对不起是小手指，轻轻的挖啊挖。。。。。。\n",
    "女儿国王：好~~~~~爽！\n",
    "孙悟空：哇~~~~~~，好大的一坨！\n",
    "沙僧  ：唉~~~~~~没想到，她挖鼻孔的姿势都这么美！Yeah~~~~~我喜\n",
    "        欢！我决定了，爱你一万年！\n",
    "侍女  ：好大胆！竟然敢对我国君无理！\n",
    "孙悟空：小MM差矣！所谓是“媱窕淑女，君子好逑”，又谓“床前明月\n",
    "        光，疑是地上霜，举头望明月，低头思姑娘”。。。。。。好\n",
    "        诗好诗。。。。。。\n",
    "女儿国王：啊，没想到师父竟有如此才华，真让小女子吃惊。。。。。\n",
    "        。不瞒众位，其实小女子在女儿国二十三年了，二~~~十~~~三\n",
    "        ~~~年了！对不起失态了。。。。。。我一直都想找一个如意\n",
    "        狼君，可是这里全都是女人，来了一个张国荣没想到还是个玻\n",
    "         璃！。。。。。。所以，我想从各位之中选出一位。。。。。。\n\n",
    "                   \n话音刚落。\n",
    "猪八戒突然伸长手臂高喊：我~~~~~~~我~~~~~~~~！\n",
    "孙悟空一拳打翻了猪八戒：你他妈滚一边，磕瓜子磕出个臭虫来，你他\n",
    "       妈算老几？\n",
    "沙僧 ：是啊，你小子在高老庄不是还有个高秀英么，再说月亮上不是还\n",
    "       有个嫦娥么？\n",
    "猪八戒（委屈的）：感情破裂了！\n",
    "唐僧叹了口气：唉。。。。。。徒弟们哪，你们也太不争气了，象你们这\n",
    "       样的男子汉，虽说长得损点，但是你们至少还是有一些本领的嘛，\n",
    "       真是的！。。。。。。大~~~~丈夫何患无妻，天涯何处无芳草。。\n",
    "       。。。。可是，你们的师父~~~~~~我。。。。。。这次，你们这次\n",      
    "       成全成全我。。。。。。\n",
    "\n\n       （师徒四人争执不休）。。。。。。\n",
    "女儿国王：各位各位，你们也别争了，不如这样吧，大家不如各展本领，我\n",
    "       今天要来个比武招亲！\n",
    "师徒四人：行！\n\n",
    "    \n。。。。。。\n",
    "女儿国王：为了这次比试的公正性，我们今天特意请来了一位嘉宾来当作裁\n",
    "          判，他就是~~~~~~~江湖上人称“人见人爱，迷死人不赔命吃不了\n",
    "          兜着走”的张国荣！\n",
    "张国荣：很感谢大家对我支持，在这里我首先要谢谢国王陛下，还要谢谢我\n",
    "        的家人，以及在场的各位，然后我还要谢谢一直在我背后支持我的\n",
    "        唐先生。。。。。。Honey!I love you,yeah,yeah,yeah!\n",
    "众人  ：倒~~~~~~~~~~~~~~~~\n",
    "孙悟空：你有没有搞~~~~~错！你是来当裁判的，你以为是在红堪体育馆啊？\n",
    "张国荣：Sorry,Sorry!我之所以要讲这么多，完全是因为。。。。。。其实\n",
    "        我是一个演员。。。。。。\n",
    "（无数只西红柿、臭鸡蛋掷了过去）\n",
    "。。。。。。\n",
    "张国荣：好了，下面公布比赛的项目。\n",
    "众人凝神静听。\n",
    "张国荣：为了比赛的观赏性、娱乐性以及本着公平竞赛的原则，比赛分两个\n",
    "        阶段。由于跟电视台的磋商问题，我们直接采用淘汰赛制。好的，\n",
    "        比赛的题目是~~~~~~~扮酷！\n",
    "话音刚落，大厅内突然出现一阵烟雾。\n",
    "女儿国王：哇~~~~~~未来战士！\n",
    "猪八戒：不错！其实，我就是未来战士，阿诺。猪~~~~~华！酷吧？咦。。。\n",
    "        谁在捅我屁股？\n",
    "孙悟空一擀杖打在猪八戒头上：酷你妈个头啦，瞧你那副德性：一支雪茄插在\n",
    "        鼻子里嘴里咬着副墨镜两腿之间还夹着一把AK47。。。。。。\n",
    "猪八戒哭道：大师兄，不是你教我耍酷要有雪茄、墨镜还有枪么？\n",
    "孙悟空：KAO！我有教你这么搭配么？\n",
    "猪八戒扑到孙悟空怀里，抚摸着孙悟空的胸脯，嚎啕大哭：师兄，我错了\n",
    "        。。。。。。我不该把把雪茄插在鼻子里，不该插在鼻子里。。。\n",     
    "        。。。55555\n",
    "孙悟空轻轻拍拍猪八戒的头，一把眼泪：好了啦，别这样了，以后别这样就\n",
    "        好了啦，来，擦把眼泪，让大伙看见多不好意思啊？\n",
    "猪八戒：哦。。。。。。有够衰的，这下没搞头了，我退出。\n",
    "张国荣：好的第一个参赛者退出，NOW，The next one!\n", 
    "沙僧  ：看我的！\n",
    "一阵烟雾过后。\n",
    "众人：哇~~~~~~唐伯虎耶！\n",
    "沙僧手拿一把折扇唱：求神那个求神，诚心祈求那个灵神（用粤语）。。。。。。\n",
    "女儿国王：STOP！扮什么不好你偏要扮唐伯虎？你一大把胡子剃得光光的，\n",
    "          不想当和尚哪道你想状元哪？\n",
    "沙僧 ：我有想过啊。。。。。。\n",
    "女儿国王：想你妈个头啦，你好好的一个和尚不做还想当状元，我跟你说，\n",
    "好好做你和尚这份很有前途的职业吧！\n",
    "沙僧 ：哦知道了。。。。。。\n",
    "张国荣：那么沙僧也出局了。下面会是谁呢？请~~~~~~~看，下面出场的\n",
    "        是~~~~~~~\n",
    "大白胖子：自从我用了这牙膏，嘿，牙好胃口就好，吃嘛嘛香，您问这什\n",
    "        么牌子？您瞅准了，蓝天六不治。。。。。。\n",
    "歌声 ：回头便知，我心只有你。。。。。。\n",
    "刘德华：我为什么会有这么动人的歌声？这全是因为我经常吃“WC”牌梨\n",
    "        膏糖。“WC”牌梨膏糖是您在家休闲，外出旅游，访亲送友之必\n",
    "        备佳品。。。。。。\n",
    "张国荣：各位，对不起，刚刚是广告时间。下面我们接着进入比赛。。。。\n",
    "        。。现在只剩下两位参赛者了，到底谁能得到我们国王陛下的美人\n",
    "        归呢，是唐僧还是孙悟空？大家拭目以待。\n",
    "唐僧双手合什：贫僧并不会扮酷，只是在下想让大家看看我的真面目。\n",
    "   话音刚落，唐僧宽大的袈裟突然裂成碎片，露出铁塔般结实的肌肉。\n",
    "唐僧狞笑：其实我就是江湖上人称“打不死的小神童金刚不坏的魔鬼肌\n",
    "          肉人”！你们看，我左青龙，右边还是青龙，我上上下下左\n",
    "          左右右全是青龙。怎么样，恐怖吧。。。。。。\n",
    "           众人皆翻倒。\n\n",
    "张国荣扑进唐僧的怀里，抚摸着唐僧结实的肌肉：哇~~~~~~~好性~~~~~~感\n",
    "          哪！我喜欢！\n",
    "大厅里吐成一片。\n",
    "孙悟空：没想到，师父你居然就是“魔鬼肌肉人”！作为你的徒弟。。。\n",
    "        我实在是佩服。\n",
    "唐僧  ：怎么样，怕了吧！\n",
    "孙悟空：徒弟甘拜下风！\n",
    "唐僧  ：那么。。。。。。\n",
    "孙悟空：不用比了，弟子退出。\n",
    "女儿国王：这场比试瞎子也能看出来是谁胜出了，那么我的如意狼君便是\n",
    "          。。。。。。\n",
    "唐僧    ：慢着，我也退出！\n",
    "女儿国王：给我个理由先！拜托~~~~~！\n",
    "唐僧    ：需要吗？\n",
    "女儿国王：不需要吗？\n",
    "唐僧    ：需要吗？\n",
    "女儿国王：不需要吗？\n",
    "唐僧    ：唉。。。。。。我只是跟你随便聊聊，千万不要当真。。。。。。\n",
    "          需要吗？\n",
    "女儿国王：一定要！\n",
    "唐僧    ：既然陛下一定要。那么我就告诉你实情。其实我并不想当你的如意\n",
    "          郎君，我只是想证明给大家看，我老唐才是这四个人中的老大！他\n",
    "          们三都得听我的，无论比什么我都要强过这哥三！\n", 
    "女儿国王：你。。。。。。\n",
    "唐僧    ：你什么你，你再敢叽叽歪歪当心我扁你！徒弟们，走！\n",
    "（歌声响起“你挑着担，你还牵着马背着个猪八。。。。。。”）\n",
    "若干年后，女儿国王：曾经有一份真诚的爱情摆在他的面前，但是他没有\n",
    "珍惜，等到了失去的时候才后悔莫及，尘世间最痛苦的事莫过于此。如果\n",
    "上天可以给他一个机会再来一次的话，我想他还是不会答应我。如果非要\n",
    "把这份绝情加上一个期限，我想会是一万年！\n",
});

        if (release==0) {
                this_object()->set_temp("play",0);
                return 0;
        }
  
      if (release==-1) {
                continue_play(sizeof(str1));
                return 1;
        }
message("channel:xjmy",HIR+"〖"HIG"魔幻电台"HIR"〗："+NOR+YEL+str1[sizeof(str1)-release]+NOR,users());
      call_out("continue_play",3,release-1);
        return 1;
}

