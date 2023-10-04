#include<graphics.h>
#ifndef exEGE
#define exEGE 
void putimagebysize(int dstX,int dstY,int width,int height,PIMAGE img){
	PIMAGE tmp=newimage(width,height);
	putimage(tmp,0,0,width,height,img,0,0,getwidth(img),getheight(img));
	putimage(dstX,dstY,tmp);
	delimage(tmp);
}
#endif
