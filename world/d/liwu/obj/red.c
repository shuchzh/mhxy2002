// ���

#include <ansi.h>
inherit ITEM;
int do_open(string arg);
     
    string *red_object=({
                      "/d/liwu/obj/dhhd",
                      "/d/liwu/obj/wnneidan",
                      "/d/liwu/obj/shougao",
                      "/d/liwu/obj/ling",
                      "/d/liwu/obj/luckdog",
                      });
              

void create()
{
	set_name(HIR"���"NOR, ({"hong bao", "bao", "hong"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���ú�ֽ�������ɵ�"+HIR"�����"NOR+"�ƺ�����˺��(tearoff)��\n");
		set("unit", "��");
		set("value", "500000");
	}
}


   void init()
  { if(query("teared"))return;
    set("no_give","ÿ����ֻ��һ�����㶼��ô�󷽣�\n");
//    set("no_get","ÿ����ֻ��һ������Ҫ��ô̰�ģ�\n");
    set("no_drop","��ô���Ķ�����Ҳ�ӣ���\n");
    add_action("do_open","tearoff");
  }

   

  int do_open(string arg)
  { 
      object me=this_player(),ob;
         int rand;

    if(query("teared"))              
         return 0;
    set("teared",1);
    set("value", "100");

    set("no_give",0);
//    set("no_get",0);
    set("no_drop",0);

    set("long", "һ���ú�ֽ�������ɵ�"+HIR"�����"NOR+"�Ѿ���˺���ˡ�\n");
        if(me->query("gender")=="����")
    tell_object(me,"���Ȳ������ؽ�"+HIR+"���"NOR+"˺����\n");
        else
    tell_object(me,"��С�������ؽ�"+HIR+"���"NOR+"�򿪣�\n");


       rand=random(sizeof(red_object)*2);

      if(rand<sizeof(red_object))
      {
           ob=new(red_object[rand]);
            if(!ob)
             tell_object(me,"���ʲôҲû�С�\n"NOR);
            else   
             {
             if(present(ob->query("id"),me))
              { destruct(ob);
                if(present("gold card",me))
                  {
                   tell_object(me,"��Ľ𿨼�����ǧ��"HIY+"�ƽ�\n"NOR);
                    me->add("card_money",50000000);
                  }
                   else
                        { ob=new("/d/liwu/obj/goldcard");
                          ob->move(me);
                          tell_object(me,"������һ��"+HIY"��"NOR+"��\n"NOR);
       			  me->add("card_money",20000000);		               
                        }  
              }
               else
                 {
                    tell_object(me,"�㷢����һ"+ob->query("unit")+ob->query("name")+"��\n"NOR);
          if(ob->query("id")=="haba gou")
          {
                    ob->set("boss_id",me->query("id"));
		  ob->set("name",me->name(1)+"�Ĺ��͹�");
                  ob->set("mud_age",200000);
                  ob->set("gender","����");
                  ob->set_leader(me);
                  ob->move(environment(me));
                  }
                 else  ob->move(me);
                 }
             }
        
      }
      else 
      {
      if(present("gold card",me))
                 {
                   tell_object(me,"��Ľ𿨼�����ǧ��"HIY+"�ƽ�"NOR+"��\n"NOR);
                   me->add("card_money",50000000);
                 }

                   else
                        { ob=new("/d/liwu/obj/goldcard");
                          ob->move(me);
                          tell_object(me,"������һ��"+HIY"��"NOR+"��\n"NOR);
                          me->add("card_money",20000000);                                
                        }  
      } 
         return 1;
  }  

  