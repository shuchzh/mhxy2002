//By waiwai@mszj 2000/12/02
//����Ϊexp>500�����Ҳ��ܽ�task����

void init()
{
        object ob = this_player();
        if( interactive(environment()) &&
            environment()->query("combat_exp") > 5000000 &&random(5) == 2 )
        {
         tell_object(ob,this_object()->name()+"ת�۾Ͳ�����!\n");
        remove_call_out("des");
        call_out("des",1); 
       }
}
void des()
{
        destruct(this_object());
}