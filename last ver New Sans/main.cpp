#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;
void hc(){
	HWND h=GetForegroundWindow();
	ShowWindow(h,SW_HIDE);
}
struct point{
	double x,y;
}p;
struct bone{
	double x,y,h,w,atk,fpsatk;
	int type,destroy,lasthit;
	void (*move)(bone&);
	bone(){
	}
	bone(double xx,double yy,double hh,double ww,double atks,double fpsatks,int types,void (*moving)(bone&)){
		x=xx;
		y=yy;
		h=hh;
		w=ww;
		atk=atks;
		fpsatk=fpsatks;
		type=types;
		destroy=0;
		lasthit=0;
		move=moving;
	}
};
struct gb{
	double x,y,dir,w,atk,fpsatk;
	int round,spin,wait,keep,type,now,lasthit;
	gb(){
	}
	gb(double xx,double yy,double dirs,double ww,double atks,double fpsatks,int spins,int waits,int keeps,int types){
		round=random(4);
		x=xx;
		y=yy;
		dir=dirs;
		w=ww;
		atk=atks;
		fpsatk=fpsatks;
		spin=spins;
		wait=waits;
		keep=keeps;
		type=types;
		now=0;
		lasthit=0;
	}
};
struct atks{
	bool (*check)();
	void (*action)();
	atks(){
	}
	atks(bool (*checker)(),void (*actions)()){
		check=checker;
		action=actions;
	}
};
queue<bone>bones;
queue<gb>gbs;
vector<atks>attacking;
int pr,grav,running,cyanmode,sansim,chsans,lmpr,moving,t,sec,canmove,tempint[100003];
double jp,g,hp=92,kr,jumph,gravv;
PIMAGE sred,sorange,sblue[7],scyan,cbcyan,cgcyan,soblue[7],sans[16],box,ui,backword,wd[13],wl,pd[13],pl,wgb,bgb,ogb,rgb;
double look(point);
#include"misc.h"
void init(){
	char temps[255];
	initgraph(640,480,INIT_RENDERMANUAL);
	setcaption("New Sans");
	setbkcolor(BLACK);
	ege_enable_aa(true);
	sec=0;
	t=0;
	sred=newimage();
	getimage(sred,"PNG","red");
	sorange=newimage();
	getimage(sorange,"PNG","orange");
	for(int i=1;i<=4;i++){
		sblue[i]=newimage();
		sprintf(temps,"blue%d",i);
		getimage(sblue[i],"PNG",temps);
	}
	scyan=newimage();
	getimage(scyan,"PNG","cyan");
	cbcyan=newimage();
	getimage(cbcyan,"PNG","bcyan");
	cgcyan=newimage();
	getimage(cgcyan,"PNG","gcyan");
	for(int i=1;i<=4;i++){
		soblue[i]=newimage();
		sprintf(temps,"orangeblue%d",i);
		getimage(soblue[i],"PNG",temps);
	}
	for(int i=1;i<=13;i++){
		sans[i]=newimage();
		sprintf(temps,"sans%d",i);
		getimage(sans[i],"PNG",temps);
	}
	box=newimage();
	getimage(box,"PNG","fightbox");
	ui=newimage();
	getimage(ui,"PNG","ui");
	backword=newimage();
	getimage(backword,"PNG","backword");
	for(int i=0;i<=9;i++){
		wd[i]=newimage();
		sprintf(temps,"w%d",i);
		getimage(wd[i],"PNG",temps);
	}
	wl=newimage();
	getimage(wl,"PNG","wline");
	for(int i=0;i<=9;i++){
		pd[i]=newimage();
		sprintf(temps,"p%d",i);
		getimage(pd[i],"PNG",temps);
	}
	pl=newimage();
	getimage(pl,"PNG","pline");
	wgb=newimage();
	getimage(wgb,"PNG","wgb");
	bgb=newimage();
	getimage(bgb,"PNG","bgb");
	ogb=newimage();
	getimage(ogb,"PNG","ogb");
	rgb=newimage();
	getimage(rgb,"PNG","rgb");
	p={320,282.5};
	setlinewidth(5);
	randomize();
}
void press(){
	pr=0;
	if(keystate(key_up))
		pr|=1;
	if(keystate(key_down))
		pr|=2;
	if(keystate(key_left))
		pr|=4;
	if(keystate(key_right))
		pr|=8;
	if(keystate(key_esc))
		exit(0);
	if(keystate(key_enter)){
		hp=92;
		kr=0;
	}
	if((pr&1)&&(pr&2)){
		pr^=1;
		pr^=2;
	}
	if((pr&4)&&(pr&8)){
		pr^=4;
		pr^=8;
	}
}
void move(int pr){
	if(pr)
		moving=1;
	else
		moving=0;
	point n=p;
	switch(grav){
		case 0:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
			break;
		case 1:
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
			if((pr&2)&&jp>0){
				n.y+=jp;
				jp-=gravv;
			}
			else{
				jp=0;
				n.y-=g;
				g+=gravv;
			}
			if(n.y<=214.0){
				g=0;
				jp=jumph;
			}
			break;
		case 2:
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
			if((pr&1)&&jp>0){
				n.y-=jp;
				jp-=gravv;
			}
			else{
				jp=0;
				n.y+=g;
				g+=gravv;
			}
			if(n.y>=351.0){
				g=0;
				jp=jumph;
			}
			break;
		case 3:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
			if((pr&8)&&jp>0){
				n.x+=jp;
				jp-=gravv;
			}
			else{
				jp=0;
				n.x-=g;
				g+=gravv;
			}
			if(n.x<=251.5){
				g=0;
				jp=jumph;
			}
			break;
		case 4:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
			if((pr&4)&&jp>0){
				n.x-=jp;
				jp-=gravv;
			}
			else{
				jp=0;
				n.x+=g;
				g+=gravv;
			}
			if(n.x>=388.5){
				g=0;
				jp=jumph;
			}
			break;
	}
	p.x=max(min(n.x,388.5),251.5);
	p.y=max(min(n.y,351.0),214.0);
}
void pibsar(PIMAGE img,int dstX,int dstY,int width,int height,double dir){
	PIMAGE tmp=newimage(width,height),tmpp=newimage(width,height);
	putimage(tmp,0,0,width,height,img,0,0,getwidth(img),getheight(img));
	putimage_transparent(tmpp,tmp,0,0,BLACK,0,0,width,height);
	putimage_rotate(NULL,tmpp,dstX,dstY,0.5,0.5,dir);
	delimage(tmpp);
	delimage(tmp);
}
void outheart(){
	if(cyanmode){
		putimage_withalpha(NULL,scyan,p.x-8,p.y-8);
		if(canmove)
			putimage_withalpha(NULL,cgcyan,p.x-24,p.y-24);
		else
			putimage_withalpha(NULL,cbcyan,p.x-24,p.y-24);
		return;
	}
	if(running&&grav){
		putimage_withalpha(NULL,soblue[grav],p.x-8,p.y-8);
		return;
	}
	if(running){
		putimage_withalpha(NULL,sorange,p.x-8,p.y-8);
		return;
	}
	if(grav){
		putimage_withalpha(NULL,sblue[grav],p.x-8,p.y-8);
		return;
	}
	putimage_withalpha(NULL,sred,p.x-8,p.y-8);
}
void show(){
	cleardevice();
	outheart();
	if(!chsans){
		sansim%=13;
		sansim++;
	}
	chsans=(chsans+1)%3;
	putimage_transparent(NULL,sans[sansim],261,25,BLACK);
	putimage_withalpha(NULL,box,237.5,200);
	putimage(33,406,ui);
	putimage(33,379,backword);
	setfillcolor(EGERGB(191,0,0));
	bar(257,374,367,395);
	setfillcolor(EGERGB(255,0,255));
	bar(257,374,257+(hp+kr)*110.0/92,395);
	setfillcolor(EGERGB(255,255,0));
	bar(257,374,257+hp*110.0/92,395);
	int allhp=hp+kr;
	if(kr){
		putimage(418,377,pd[allhp/10]);
		putimage(433,377,pd[allhp%10]);
		putimage(457,377,pl);
		putimage(481,377,pd[9]);
		putimage(496,377,pd[2]);
	}
	else{
		putimage(418,377,wd[allhp/10]);
		putimage(433,377,wd[allhp%10]);
		putimage(457,377,wl);
		putimage(481,377,wd[9]);
		putimage(496,377,wd[2]);
	}
	int bs=bones.size();
	while(bs--){
		bone x=bones.front();
		bones.pop();
		switch(x.type){
			case 1:
				setfillcolor(0xffffff);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 2:
				setfillcolor(0x14A9FF);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 3:
				setfillcolor(0xFFA040);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 4:
				setfillcolor(0xFF0000);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
		}
		bones.push(x);
	}
	setfillcolor(0xffffffff);
	int gs=gbs.size();
	while(gs--){
		gb x=gbs.front(),y=x;
		gbs.pop();
		if(x.now<=x.spin){
			y.x=320.0+(x.x-320.0)*x.now/x.spin;
			y.y=100.5+(x.y-100.5)*x.now/x.spin;
			y.dir=(acos(-1)*2*x.round+x.dir)*x.now/x.spin;
		}
		else
			if(x.now>x.spin+x.keep){
				ege_point points[]={{x.x,x.y},{x.x+x.w*cos(x.dir),x.y+x.w*sin(x.dir)},{x.x+cos(x.dir)*50,x.y+sin(x.dir)*50},{x.x+cos(x.dir)*50+x.w*cos(x.dir),x.y+sin(x.dir)*50+x.w*sin(x.dir)}};
				ege_fillpoly(4,points);
			}
		switch(x.type){
			case 1:
				pibsar(wgb,y.x,y.y,44,y.w,y.dir);
				break;
			case 2:
				pibsar(bgb,y.x,y.y,44,y.w,y.dir);
				setfillcolor(0x14A9FF);
				break;
			case 3:
				pibsar(ogb,y.x,y.y,44,y.w,y.dir);
				setfillcolor(0xFFA040);
				break;
			case 4:
				pibsar(rgb,y.x,y.y,44,y.w,y.dir);
				setfillcolor(0xFF0000);
				break;
		}
		gbs.push(x);
	}
}
void dropkr(){
	if(kr>=40){
		kr--;
		return;
	}
	if(kr>=30){
		if(t%2==0)
			kr--;
		return;
	}
	if(kr>=20){
		if(t%5==0)
			kr--;
		return;
	}
	if(kr>=10){
		if(t%15==0)
			kr--;
		return;
	}
	if(kr)
		if(t%30==0)
			kr--;
	return;
}
void hurt(double x){
	if(kr==0&&hp==1)
		exit(0);
	if(hp>x){
		hp-=x;
		kr+=x;
	}
	else{
		kr+=2*hp-2-x;
		kr=max(kr,0.0);
		hp=1;
	}
}
void check(bone &x){
	if(x.type==2&&moving==0)
		return;
	if(x.type==3&&moving==1)
		return;
	if(p.x+2>=x.x&&p.x-2<=x.x+x.h&&p.y+2>=x.y&&p.y-2<=x.y+x.w)
		if(x.lasthit)
			hurt(x.fpsatk);
		else{
			hurt(x.atk);
			x.lasthit=1;
		}
	else
		x.lasthit=0;
}
void check(gb &x){
	if(x.type==2&&moving==0)
		return;
	if(x.type==3&&moving==1)
		return;
}
bool checkm(bone &x){
	point bc={x.x+x.h/2,x.y+x.w/2};
	point v={abs(p.x-bc.x),abs(p.y-bc.y)};
	point h={x.h/2,x.w/2};
	point pp={max(v.x-h.x,0.0),max(v.y-h.y,0.0)};
	return pp.x*pp.x+pp.y*pp.y<576.0;
}
bool checkm(gb &x){
	return false;
}
bool checkmove(){
	int bs=bones.size();
	while(bs--){
		bone x=bones.front();
		bones.pop();
		bones.push(x);
		if(checkm(x))
			return true;
	}
	int gs=gbs.size();
	while(gs--){
		gb x=gbs.front();
		gbs.pop();
		gbs.push(x);
		if(x.now>x.spin+x.wait&&x.now<=x.spin+x.wait+x.keep)
			if(checkm(x))
				return true;
	}
	return false;
}
void hit(){
	int bs=bones.size();
	while(bs--){
		bone x=bones.front();
		bones.pop();
		check(x);
		x.move(x);
		if(!x.destroy)
			bones.push(x);
	}
	int gs=gbs.size();
	while(gs--){
		gb x=gbs.front();
		gbs.pop();
		x.now++;
		if(x.now<=x.spin+x.wait+x.keep){
			if(x.now>x.spin+x.wait)
				check(x);
			gbs.push(x);
		}
	}
}
void timepass(){
	t++;
	t%=30;
	if(!t)
		sec++;
}
bool counttime(int second,int fps){
	if(sec<second||(sec==second&&t<=fps))
		return true;
	sec=0;
	t=0;
	return false;
}
void tryatk(){
	for(int i=0;i<attacking.size();i++)
		if(attacking[i].check())
			attacking[i].action();
}
double look(point x){
	if(p.x<=x.x)
		return atan(-(p.y-x.y)/(p.x-x.x))-acos(-1);
	return atan(-(p.y-x.y)/(p.x-x.x));
}
void initlevel(int orange,int gravity,int cyan,point pos={-1,-1},double jump=6,double dropsp=0.25){
	running=orange;
	grav=gravity;
	cyanmode=cyan;
	if(pos.x!=-1&&pos.y!=-1)
		p=pos;
	jumph=jump;
	gravv=dropsp;
}
void playuntil(int second,int fps){
	for(;counttime(second,fps);delay_fps(30)){
		tryatk();
		show();
		hit();
		dropkr();
		if(cyanmode)
			canmove=checkmove();
		press();
		if(canmove==0&&cyanmode==1)
			pr=0;
		if(pr){
			if(running)
				if(grav<=2)
					move(pr|(1<<(2-grav)));
				else
					move(pr|(1<<(6-grav)));
			else
				move(pr);
			lmpr=pr;
		}
		else
			if(running)
				if(!grav)
					move(lmpr);
				else
					if(grav<=2)
						move(lmpr|(1<<(2-grav)));
					else
						move(lmpr|(1<<(6-grav)));
			else
				move(pr);
		timepass();
	}
	attacking.clear();
	while(bones.size())
		bones.pop();
	while(gbs.size())
		gbs.pop();
}
void level1(){
	initlevel(0,0,0);
	attacking.push_back(atks(three_times_a_second,sbu));
	attacking.push_back(atks(three_times_a_second,sbd));
	attacking.push_back(atks(once_a_second,genf));
	attacking.push_back(atks(once_a_second_half,gen));
//	attacking.push_back(atks(once_a_second,gbgen));
	playuntil(10,0);
}
void level2(){
	initlevel(1,0,0);
	attacking.push_back(atks(many_times_a_second,sbuu));
	attacking.push_back(atks(many_times_a_second,sbdd));
	attacking.push_back(atks(many_times_a_second,sbl));
	attacking.push_back(atks(many_times_a_second,sbr));
	playuntil(10,0);
}
void level3(){
	initlevel(0,0,0);
	attacking.push_back(atks(three_second,apg));
	attacking.push_back(atks(three_second_two,apb));
	playuntil(12,0);
}
void level4(){
	initlevel(0,0,1,{320,282.5});
	attacking.push_back(atks(three_second,l4b1));
	attacking.push_back(atks(three_second_two,l4b2));
	playuntil(12,0);
}
void level5(){
	initlevel(1,2,0,{-1,-1},6,0.15);
	attacking.push_back(atks(four_second,l4b1));
	attacking.push_back(atks(four_second_two,l4b2));
	playuntil(16,0);
}
void showt(){
	cleardevice();
	outheart();
	if(!chsans){
		sansim%=13;
		sansim++;
	}
	chsans=(chsans+1)%3;
	putimage_transparent(NULL,sans[sansim],261,25,BLACK);
	putimage_withalpha(NULL,box,237.5,200);
	putimage(33,406,ui);
	putimage(33,379,backword);
	setfillcolor(EGERGB(191,0,0));
	bar(257,374,367,395);
	setfillcolor(EGERGB(255,0,255));
	bar(257,374,257+(hp+kr)*110.0/92,395);
	setfillcolor(EGERGB(255,255,0));
	bar(257,374,257+hp*110.0/92,395);
	int allhp=hp+kr;
	if(kr){
		putimage(418,377,pd[allhp/10]);
		putimage(433,377,pd[allhp%10]);
		putimage(457,377,pl);
		putimage(481,377,pd[9]);
		putimage(496,377,pd[2]);
	}
	else{
		putimage(418,377,wd[allhp/10]);
		putimage(433,377,wd[allhp%10]);
		putimage(457,377,wl);
		putimage(481,377,wd[9]);
		putimage(496,377,wd[2]);
	}
}
void turn(){//TODO
//	while(1){
//		delay_fps(30);
//		showt();
//		dropkr();
//		press();
//	}
}
int main(){
//	hc();
	init();
	while(1){
		turn();
		level1();
		turn();
		level2();
		turn();
		level3();
		turn();
		level4();
		turn();
		level5();
	}
	closegraph();
	return 0;
}
