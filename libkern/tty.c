/*
*Terminal code
*Borrowed a little from OSDev wiki can't lie
*Public domain
*Zachary Schlotman and OSDev
*/
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/types.h>

ksize_t tr;
ksize_t tc;
uint8_t tcolour;
uint16_t *tbuff;
void t_init(){
    tr = 0;
    tc = 0;
    tcolour = mkcolour(COLOUR_WHITE,COLOUR_BLACK);
    tbuff = VMEM;
    for(int y = 0; y < VH;y++){
        for(int x = 0;x < VW;x++){
            const ksize_t index = y * VW + x;
            tbuff[index] = mkent(' ',tcolour);
        }
    }
}
void _t_init(){
	tr = 0;
	tc = 0;
	tcolour = mkcolour(COLOUR_WHITE,COLOUR_BLACK);
	tbuff = VMEM;
	for(int y = 0; y < VH;y++){
		for(int x = 0;x < VW;x++){
			const ksize_t index = y * VW + x;
			tbuff[index] = mkent(' ',tcolour);
		}
	}
}
void t_clear(){
	int x;
        int y;
        for(y = 0; y < VH;x++){
                for(x = 0;x < VW;y++){
                        const ksize_t index = y * VW + x;
                        tbuff[index] = mkent(' ',tcolour);
                }
        }

}
void t_setcolour(uint8_t colour){
	tcolour = colour;
}
void putent(char c,uint8_t colour,ksize_t x,ksize_t y){
	const ksize_t index = y * VW + x;
	tbuff[index] = mkent(c,colour);
}
void putcolour(uint8_t colour1){
	//putent(' ',colour,tc,tr);
	const ksize_t index = tr * VW + tc;
	uint8_t colour = mkcolour(colour1,colour1);
	tbuff[index] = mkent(' ',colour);
	if(++tc == 80){
		tc = 0;
		if(++tr == 25){
			tc = 0;
			tr = 0;
			//t_init();
		}
	}
}
void t_displayl(){
	//while(1){
		putent('\\',tcolour,tc,tr);
		for(int i = 0; i < 1000000; i++) {inb(0x1FC); }
		putent('|',tcolour,tc,tr);
		for(int i = 0; i < 1000000;i++) {inb(0x1FC); }
		putent('/',tcolour,tc,tr);
		for(int i = 0; i < 1000000;i++) {inb(0x1FC); }
	//}
}
void t_displaylq(){
	putent('\\',tcolour,tc,tr);
	putent('|',tcolour,tc,tr);
	putent('/',tcolour,tc,tr);
}
void place_cursor(){
	putent(' ',mkcolour(COLOUR_WHITE,COLOUR_WHITE),(tc + 1),tr);
}
void clear_cursor(){
	putent(' ',tcolour,(tc + 1),tr);
}
void _t_putc(char c){
    if(c != '\n')
        putent(c,tcolour,tc,tr);
    if(c == '	')
        c = ' ';
    if(++tc == 80 || c == '\n'){
        tc = 0;
        if(++tc == 80 || c == '\n'){
            tc = 0;
            if(++tr == 25){
                tr = 0;
                tc = 0;
                t_init();
            }
        }
    }
}
void t_putc(char c){
    /*if(tr != 0){
        int *mem = (int *)0x00000500;
        while(*mem != 0)
            *mem++;
        *mem = c;
    }*/
	if(c != '\n')
		putent(c,tcolour,tc,tr);
	if(c == '	')
		c = ' ';
	if(++tc == 80 || c == '\n'){
		tc = 0;
		if(++tr == 25){
			tr = 0;
			tc = 0;
            t_init();
			/*_t_init();
            int *mem = (int*)0x00000500;
            while(*mem != 0){
                _t_putc(*mem);
                *mem++;
            }
            mem = (int*)0x00000500;
            while(*mem != 0){
                *mem = 0;
                *mem++;
            }*/
		}
	}
	unsigned short pos = (tr *80) + tc + 1;
        outb(0x3D4,0x0F);
        outb(0x3D5,(unsigned char) (pos&0xFF));
        outb(0x3D4,0x0E);
        outb(0x3D5,(unsigned char) ((pos >> 8)&0xFF));
}

void t_cputc(char c,uint8_t colour){
	if(c != '\n')
		putent(c,colour,tc,tr);
	if(++tc == 80 || c == '\n'){
		tc = 0;
		if(++tr == 25){
			tr = 0;
			tc = 0;
			t_init();
		}
	}
}
void t_write(const char *str,ksize_t s){
	int i = 0;
	while(i < s){
		t_putc(str[i]);
		i++;
	}
}
void t_writestr(const char *str){
	int i = 0;
	t_write(str,strlen(str));
}
void t_writecolour(const char *str,uint8_t colour){
	int i = 0;
	while(i < strlen(str)){
		t_cputc(str[i],colour);
		i++;
	}
}
