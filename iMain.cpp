# include "iGraphics.h",

#define height 100
#define width 30
#define dis 180
/*#define p1_x 200
#define p2_x 700
#define c1_x 400
#define c2_x 900*/
#define dis2 80
#define border 50
#define Con_X 1100
#define Con_Y 700
#define layers 2
double x=550,y=350,Y1=125,Y2=125,y_1=125,y_2=125,dx=5,dy=5,p1_x,p2_x,c1_x,c2_x,comp_move=7.5;
int fl = 0 , gp_counter = 0 , gc_counter = 0 , fl1=1, fl2=1 ,flmenu=0,fltime=100,mytime=0,fl_level=1;
double py[3] , cy[3],px[3],cx[3] , player_move = 10 , prev_pos = 350.0 ;
char goal_str[40] ;
void pcXSet(void)
{
    double a,b,c,d;
    a=(Con_X-2*border)/(2*layers+1);
    p1_x=border+a-width/2;
    c1_x=border+2*a-width/2;
    p2_x=border+3*a-width/2;
    c2_x=border+4*a-width/2;

}
void iField(void)
{
    iSetColor(200,200,400);      /* just to change the color of the console */
    iFilledRectangle(0,0,Con_X,Con_Y);

    iSetColor(0,200,0);               /* green color of the field  */
    iFilledRectangle(border,border,Con_X-2*border,Con_Y-2*border);

    iSetColor(0,0,0);                  /* coloring the  goalpost */
    iFilledRectangle(50,250,-30,200);
    iFilledRectangle(1050,250,30,200);

    iSetColor(200,200,200) ;  /*designing the field */
    iLine(550,50,550,650) ;
    iCircle(550,350,150) ;
    iRectangle(50,200,200,300) ;
    iRectangle(1050,200,-200,300) ;

}
void iMenu(void)
{
    iSetColor(300,0,0);
    iFilledRectangle(Con_X/2-100,Con_Y/2,200,100);//Play Button

    iSetColor(0,0,300);
    iFilledRectangle(Con_X/2-100,Con_Y/2-100,200,100);//Exit button

    iSetColor(00,00,00);
    iText(Con_X/2-35,Con_Y/2+35,"PLAY",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(Con_X/2-35,Con_Y/2-65,"EXIT",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(border, Con_Y-border+10,"THE TIME YOU WANT TO PLAY",GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(00,00,00);
    iFilledRectangle(border,Con_Y-border-50,100,50);
    iFilledRectangle(border,Con_Y-border-150,100,50);
    iSetColor(100,100,100);
    iFilledRectangle(border,Con_Y-border-100,100,50);
    iSetColor(300,300,300);
    iText(border, Con_Y-border-30,"   2 Min",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(border, Con_Y-border-30-50,"   5 Min",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(border, Con_Y-border-30-100,"   10 Min",GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(200,0,0);
    if(fltime==2*60) iFilledCircle(border-10,Con_Y-75,7.5);
    if(fltime==5*60) iFilledCircle(border-10,Con_Y-75-50,7.5);
    if(fltime==10*60) iFilledCircle(border-10,Con_Y-75-100,7.5);
    iText(Con_X-border-150, Con_Y-border+10,"SELECT LEVEL",GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0,0,0);
    iFilledRectangle(Con_X-border-100,Con_Y-border-50,100,50);
    iFilledRectangle(Con_X-border-100,Con_Y-border-150,100,50);
    iSetColor(100,100,100);
    iFilledRectangle(Con_X-border-100,Con_Y-border-100,100,50);
    iSetColor(500,0,0);
    iText(Con_X-border-100, Con_Y-border-30,"   Easy",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(Con_X-border-100, Con_Y-border-30-50," Medium",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(Con_X-border-100, Con_Y-border-30-100,"   Hard",GLUT_BITMAP_TIMES_ROMAN_24);
    if(fl_level==1) iFilledCircle(Con_X-border-100-10,Con_Y-75,7.5);
    if(fl_level==2) iFilledCircle(Con_X-border-100-10,Con_Y-75-50,7.5);
    if(fl_level==3) iFilledCircle(Con_X-border-100-10,Con_Y-75-100,7.5);
}
double calc_intersect(double layer_x )
{
    double int_y ;
    int_y = (dy/dx)*(layer_x-x) + y ;
    return int_y ;
}



void func_goal_str()
{
    int i = 0 , j , m = gp_counter , n = gc_counter , l ;
    char ch ;
    if(n==0) goal_str[i++] = '0' ;
    while( n!=0 )
    {
        goal_str[i++] = n%10 + '0' ;
        n = n/10 ;
    }
    goal_str[i++] = ' ' ;
    goal_str[i++] = ':' ;
    goal_str[i++] = ' ' ;
    if(m==0) goal_str[i++] = '0' ;
    while( m!=0 )
    {
        goal_str[i++] = m%10 + '0' ;
        m = m/10 ;
    }
    j = 0 ;
    l = i ;
    i-- ;

    while(j<i)
    {
        ch = goal_str[j] ;
        goal_str[j] = goal_str[i] ;
        goal_str[i] = ch ;
        j++ ;
        i--;
    }
    goal_str[l] = '\0' ;
}

void iDraw()
{

    printf("%d\n" ,fltime);
    char timeStr[20];

    pcXSet();
    iClear();
    iField();
    if(flmenu==0) iMenu();
    else
    {
        //iclear();
        iField();

        iSetColor(200,0,0);    /* designing my player */

        py[1] =  y_1 ;
        py[2] = y_2 ;
        cy[1] =  Y1 ;
        cy[2] = Y2 ;
        iFilledRectangle( p1_x , py[1] , width , height );

        iFilledRectangle( p1_x , py[1]+dis , width , height);

        iFilledRectangle( p1_x , py[1]+2*dis , width , height);

        iFilledRectangle( p2_x , py[2] , width , height )    ;

        iFilledRectangle( p2_x , py[2]+dis , width , height ) ;

        iFilledRectangle( p2_x , py[2]+2*dis , width , height ) ;


        iSetColor(0,0,400);

        cy[1]=Y1;
        cy[2]=Y2;

        iFilledRectangle(c1_x,cy[1],width,height);
        iFilledRectangle(c1_x,cy[1]+dis,width,height);
        iFilledRectangle(c1_x,cy[1]+2*dis,width,height);
        iFilledRectangle(c2_x,cy[2],width,height);
        iFilledRectangle(c2_x,cy[2]+dis,width,height);
        iFilledRectangle(c2_x,cy[2]+2*dis,width,height);
        iSetColor(100,100,100);
        iFilledCircle( x , y , 10 );
        func_goal_str() ;
        iText(535, 660, goal_str , GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(timeStr,"%d:%2d",mytime/60,mytime%60);
        iText(Con_X-border, Con_Y-border, timeStr , GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(0,0,0);
        iFilledCircle(p1_x+width/2,y_1+height/2,width/3);
        iFilledCircle(p1_x+width/2,y_1+dis+height/2,width/3);
        iFilledCircle(p1_x+width/2,y_1+2*dis+height/2,width/3);//Player head faker.
        iFilledCircle(p2_x+width/2,y_2+height/2,width/3);
        iFilledCircle(p2_x+width/2,y_2+dis+height/2,width/3);
        iFilledCircle(p2_x+width/2,y_2+2*dis+height/2,width/3);

        iFilledCircle(c1_x+width/2,Y1+height/2,width/3);
        iFilledCircle(c1_x+width/2,Y1+dis+height/2,width/3);
        iFilledCircle(c1_x+width/2,Y1+2*dis+height/2,width/3);//Player head faker.
        iFilledCircle(c2_x+width/2,Y2+height/2,width/3);
        iFilledCircle(c2_x+width/2,Y2+dis+height/2,width/3);
        iFilledCircle(c2_x+width/2,Y2+2*dis+height/2,width/3);
        if(mytime>fltime)
        {
            iClear();
            //iField();
            iSetColor(200,200,200);
            iText(Con_X/2-50, Con_Y/2, "GAME OVER" , GLUT_BITMAP_TIMES_ROMAN_24);
            iText(550, 640, goal_str , GLUT_BITMAP_TIMES_ROMAN_24);
            if(gp_counter>gc_counter) iText(x,y, "YOU'VE WON", GLUT_BITMAP_TIMES_ROMAN_24);
            else if(gp_counter==gc_counter) iText(x,y, "MATCH DRAWN", GLUT_BITMAP_TIMES_ROMAN_24);
            else iText(x,y, "YOU'VE LOST", GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
}




void iMouseMove(int mx, int my)
{

}

void iMouseOver(int mx,int my)
{
   // printf("%d %d\n",mx,my);

      if(prev_pos>my && y_1-player_move>=50 && mx<Con_X/2 ) y_1-=player_move;

    if(prev_pos<my && y_1+2*dis+height+player_move<=650 &&mx<Con_X/2) y_1+=player_move;

    if(prev_pos>my && y_2-player_move>=50 && mx>Con_X/2) y_2-=player_move;

    if( prev_pos<my && y_2+2*dis+height+player_move<=650 && mx>Con_X/2) y_2+=player_move;
    prev_pos = my ;
}
    void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(mx>Con_X-border-100&&mx<Con_X-border)
        {
            if(my>Con_Y-100&&my<Con_Y-50) fl_level=1;
            if(my>Con_Y-150&&my<Con_Y-100) fl_level=2;
            if(my>Con_Y-200&&my<Con_Y-150) fl_level=3;
        }

        //place your codes here
        //	printf("x = %d, y= %d\n",mx,my);
        dx = dx;
        dy = dx;
        if(mx>Con_X/2-100&&mx<Con_X/2+100&&my>Con_Y/2&&my<Con_Y/2+100) flmenu=1;
        if(mx>Con_X/2-100&&mx<Con_X/2+100&&my>Con_Y/2-100&&my<Con_Y/2&&flmenu==0) exit(0);
        if(fltime<mytime) exit(0);
        if(mx>border&&mx<border+100)
        {
            if(my>Con_Y-100&&my<Con_Y-50) fltime=2*60;
            if(my>Con_Y-150&&my<Con_Y-100) fltime=5*60;
            if(my>Con_Y-200&&my<Con_Y-150) fltime=10*60;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        x = x;
        y = y;
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
    if( key=='a' )
    {
        flmenu = (flmenu+1)%2 ;
    }
    if(key=='s')
    {
        fl = 2 ;
    }
    /*   if (key == 'w'&&y_1+player_move<211)
       {
           y_1+= player_move ;
       }
       if (key == 's'&&y_1-player_move>49)
       {
           y_1-= player_move ;
       }
       if (key == 'q')
       {
           exit(0);
       } */

    /*  if (key == 'e'&&y_2+player_move<211)
      {
          y_2+= player_move ;
      }
      if (key == 'd'&&y_2-player_move>49)
      {
          y_2-= player_move ;
      } */
    if (key == 'q')
    {
        exit(0);
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END )
    {
        exit(0);
    }
    if (key == GLUT_KEY_UP && fl==1 && y_1+player_move<211)
    {
        y_1+= player_move ;
    }
    if (key ==  GLUT_KEY_DOWN && fl==1 && y_1-player_move>49)
    {
        y_1-= player_move ;
    }
    if (key == 'q')
    {
        exit(0);
    }

    if (key == GLUT_KEY_UP && fl==2 && y_2+player_move<211)
    {
        y_2+= player_move ;
    }
    if (key ==  GLUT_KEY_DOWN && fl==2&& y_2-player_move>49)
    {
        y_2-= player_move ;
    }

//   fl = 0 ;

    //place your codes for other keys here
}

void BALLmove(void)
{
    if(!flmenu||mytime>fltime) return;
    x+=dx;
    y+=dy;

    if(y<=55||y>=645)
    {
        dy = -dy ;
        if(dx>4||dx<-4) dx++;
    }
    if(x<=55||x>=1045)
    {
        dx=-dx ;
        if(dy>4||dy<-4) dy++;
    }
    if( 260<=y && y<=440 )
    {
        if( x<=55 )
        {
            gc_counter++ ;
            /*   x+= dx ;
               x = 550 ;
               y = 350 ; */
        }
        if( x>=1045 )
        {
            gp_counter++ ;
            /*    x+= dx ;
                x = 550 ;
                y = 350 ; */
        }
    }
    if( p1_x<= x-10 && x-10<=p1_x+width && dx<0 )
    {
        /*   if( (py[1]<=y+10&&y+10<=py[1]+height)||(py[1]+dis<=y+10&&y+10<=py[1]+dis+height) || (py[1]+2*dis<=y+10&&y+10<=py[1]+2*dis+height)  )
           {
               dx = -dx ;
           } */
        if( (py[1]<=y&&y<=py[1]+height)||(py[1]+dis<=y&&y<=py[1]+dis+height) || (py[1]+2*dis<=y&&y<=py[1]+2*dis+height)  )
        {
            dx = -dx ;
        }
    }
    if( p2_x<= x-10 && x-10<=p2_x+width && dx<0 )
    {
        /*   if( (py[1]<=y+10&&y+10<=py[1]+height)||(py[1]+dis<=y+10&&y+10<=py[1]+dis+height) || (py[1]+2*dis<=y+10&&y+10<=py[1]+2*dis+height)  )
           {
               dx = -dx ;
           } */
        if( (py[2]<=y&&y<=py[2]+height)||(py[2]+dis<=y&&y<=py[2]+dis+height) || (py[2]+2*dis<=y&&y<=py[2]+2*dis+height)  )
        {
            dx = -dx ;
        }
    }
    if( c1_x<= x && x<=c1_x+width && dx>0 )
    {
        /*if( (py[1]<=y+10&&y+10<=py[1]+height)||(py[1]+dis<=y+10&&y+10<=py[1]+dis+height) || (py[1]+2*dis<=y+10&&y+10<=py[1]+2*dis+height)  )
        {
            dx = -dx ;
        }*/
        if( (cy[1]<=y&&y<=cy[1]+height)||(cy[1]+dis<=y&&y<=cy[1]+dis+height) || (cy[1]+2*dis<=y&&y<=cy[1]+2*dis+height)  )
        {
            dx = -dx ;
        }
    }
    if( c2_x<= x && x<=c2_x+width && dx>0 )
    {
        /*   if( (py[1]<=y+10&&y+10<=py[1]+height)||(py[1]+dis<=y+10&&y+10<=py[1]+dis+height) || (py[1]+2*dis<=y+10&&y+10<=py[1]+2*dis+height)  )
           {
               dx = -dx ;
           } */
        if( (cy[2]<=y&&y<=cy[2]+height)||(cy[2]+dis<=y&&y<=cy[2]+dis+height) || (cy[2]+2*dis<=y&&y<=cy[2]+2*dis+height)  )
        {
            dx = -dx ;
        }
    }
}
void CompLayerMoveEasy(void)
{
    if(fl_level!=1) return ;
    if( x<=c1_x && dx >0  )
    {
        if(Y1-comp_move>50)
    {
        if(y<Y1||(y<Y1+dis&&y>Y1+height+(dis2/2))||(y<Y1+2*dis&&y>Y1+dis+height+(dis2/2)))
        {
            Y1-=comp_move;
        }
    }
    if(Y1+height+dis*2+comp_move<650)
    {
        if(y>Y1+height+2*dis||(y>Y1+height&&y<Y1+height+(dis2/2))||(y>Y1+dis+height&&y<Y1+dis+height+(dis2/2)))
        {
            Y1+=comp_move;

        }
    }
    }
    else if( x<=c2_x  && dx>=0 )
    {
        if(Y2-comp_move>50)
    {
        if(y<Y2||(y<Y2+dis&&y>Y2+height+(dis2/2))||(y<Y2+2*dis&&y>Y2+dis+height+(dis2/2)))
        {
            Y2-=comp_move;
        }
    }
    if(Y2+height+dis*2+comp_move<650)
    {
        if(y>Y2+height+2*dis||(y>Y2+height&&y<Y2+height+(dis2/2))||(y>Y2+dis+height&&y<Y2+dis+height+(dis2/2)))
        {
            Y2+=comp_move;

        }
    }
    }

}
void CompLayerMoveMedium(void)
{
    if(fl_level!=2) return ;
    if(Y1-comp_move>50)
    {
        if(y<Y1||(y<Y1+dis&&y>Y1+height+(dis2/2))||(y<Y1+2*dis&&y>Y1+dis+height+(dis2/2)))
        {
            Y1-=comp_move;
        }
    }
    if(Y1+height+dis*2+comp_move<650)
    {
        if(y>Y1+height+2*dis||(y>Y1+height&&y<Y1+height+(dis2/2))||(y>Y1+dis+height&&y<Y1+dis+height+(dis2/2)))
        {
            Y1+=comp_move;

        }
    }
    if(Y2-comp_move>50)
    {
        if(y<Y2||(y<Y2+dis&&y>Y2+height+(dis2/2))||(y<Y2+2*dis&&y>Y2+dis+height+(dis2/2)))
        {
            Y2-=comp_move;
        }
    }
    if(Y2+height+dis*2+comp_move<650)
    {
        if(y>Y2+height+2*dis||(y>Y2+height&&y<Y2+height+(dis2/2))||(y>Y2+dis+height&&y<Y2+dis+height+(dis2/2)))
        {
            Y2+=comp_move;

        }
    }

}
void CompLayerMoveHard()
{
    if(fl_level!=3) return ;
    if( x<c1_x && dx>0  )
    {
        double yi = calc_intersect(c1_x) ;

    if( yi<=Y1 && Y1-comp_move>=50.0 ) Y1 -= comp_move ;

    else if( yi>Y1+height && yi<=Y1+height+dis2/2 && yi+2*dis >650 && Y1-comp_move>=50  ) Y1 -= comp_move ;
    else if( yi>Y1+dis+height && yi<Y1+height+dis+dis2/2 && yi+dis>650 && Y1-comp_move>=50  ) Y1 -= comp_move ;
    else if( (yi>Y1+height+dis2/2&&yi<Y1+dis || yi>Y1+dis+height+dis2/2&&yi<Y1+2*dis) && Y1-comp_move>=50  ) Y1 -= comp_move ;
    else if( ((yi>Y1+height && yi<Y1+dis)||(yi>Y1+dis+height && yi<Y1+2*dis ) || yi>Y1+2*dis+height)&& Y1+2*dis+height+comp_move<=650 )   Y1+=comp_move ;

    }
    else if( x<c2_x && dx>0 )
    {
        double yi = calc_intersect(c2_x) ;

    if( yi<=Y2 && Y2-comp_move>=50.0 ) Y2 -= comp_move ;

    else if( yi>Y2+height && yi<=Y2+height+dis2/2 && yi+2*dis >650 && Y2-comp_move>=50  ) Y2 -= comp_move ;
    else if( yi>Y2+dis+height && yi<Y2+height+dis+dis2/2 && yi+dis>650 && Y2-comp_move>=50  ) Y2 -= comp_move ;
    else if( (yi>Y2+height+dis2/2&&yi<Y2+dis || yi>Y2+dis+height+dis2/2&&yi<Y2+2*dis) && Y2-comp_move>=50  ) Y2 -= comp_move ;



    }
}
void Ispeed(void)

{
    if(fl_level==1) return;
    if(mytime>2*60) return;
    if(dx>0) dx+=0.5;
    else dx-=0.5;
    if(dy>0) dy+=0.5;
    else dy-=0.5;
    //if(fl_level==3){ comp_move+=0.5);}
}

void ExitTimer(void)
{
   if(flmenu==0) return;
   mytime++;
    //if(mytime>fltime) exit(0);
}

int main()
{
    int i;
   // printf("Enter The Time you want to play in minutes");
    //scanf("%d" ,&i);
    //cy[1] = 125 ; cy[2] = 125 ;
    i=500;
    iSetTimer(10, CompLayerMoveEasy) ;
    iSetTimer(10, CompLayerMoveMedium) ;
    iSetTimer(10, CompLayerMoveHard);
    iSetTimer(10,BALLmove);
    iSetTimer(1000,ExitTimer);
    iSetTimer(10*1000,Ispeed);

    iInitialize(Con_X, Con_Y, "FOOTBALL");

    return 0;
}
