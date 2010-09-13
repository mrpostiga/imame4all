#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "minimal.h"
#include "iOS_frontend_list.h"
#include "iOS_frontend_menu.h"
#include "iOS_frontend_splash.h"
#include "shared.h"

int game_num_avail=0;
static int last_game_selected=0;
char playemu[16] = "mame\0";
char playgame[16] = "builtinn\0";

int iOS_inGame=0;
int iOS_exitGame=0;

int iOS_video_aspect=0;
int iOS_video_rotate=0;
int iOS_video_sync=0;
int iOS_frameskip=-1;
int iOS_sound = 4;
int iOS_clock_cpu= 80;
int iOS_clock_sound=80;
int iOS_cheat=0;
int iOS_landscape_buttons=2;

extern int iOS_aspectRatio;
extern int iOS_cropVideo;
extern int iOS_320x240;

extern int safe_render_path;
extern int isIpad;

int _master_volume = 100;

extern int iphone_main (int argc, char **argv);

static void load_bmp_8bpp(unsigned char *out, unsigned char *in) 
{
	int i,x,y;
	unsigned char r,g,b,c;
	in+=14; /* Skip HEADER */
	in+=40; /* Skip INFOHD */
	/* Set Palette */
	for (i=0;i<256;i++) {
		b=*in++;
		g=*in++;
		r=*in++;
		c=*in++;
		gp2x_video_color8(i,r,g,b);
	}
	gp2x_video_setpalette();
	/* Set Bitmap */
	unsigned short *p = (unsigned short *)out;
	for (y=239;y!=-1;y--) {
		for (x=0;x<320;x++) {
			//*out++=in[x+y*320];
			*p++=gp2x_palette[in[x+y*320]];
		}
	}
}

static void gp2x_intro_screen(void) {
	char name[256];
	FILE *f;
	gp2x_video_flip();
	sprintf(name,get_documents_path("skins/iOSsplash.bmp"));
	f=fopen(name,"rb");
	if (f) {
		fread(gp2xsplash_bmp,1,77878,f);
		fclose(f);
	}

	while(1)
	{
		load_bmp_8bpp(gp2x_screen8,gp2xsplash_bmp);
		gp2x_video_flip();

		int ExKey=gp2x_joystick_read(0);
		if(ExKey!=0)break;
		gp2x_timer_delay(50);
	}
	sprintf(name,get_documents_path("skins/iOSmenu.bmp"));
	f=fopen(name,"rb");
	if (f) {
		fread(gp2xmenu_bmp,1,77878,f);
		fclose(f);
	}
}

static void game_list_init(void)
{
	int i;
	DIR *d=opendir(get_documents_path("roms"));
	char game[32];
	if (d)
	{
		struct dirent *actual=readdir(d);
		while(actual)
		{
			for (i=0;i<NUMGAMES;i++)
			{
				if (_drivers[i].available==0)
				{
					sprintf(game,"%s.zip",_drivers[i].name);
					if (strcmp(actual->d_name,game)==0)
					{
						_drivers[i].available=1;
						game_num_avail++;
						break;
					}
				}
			}
			actual=readdir(d);
		}
		closedir(d);
	}
}


static void game_list_init(int argc)
{

	game_list_init();
}

static void game_list_view(int *pos) {

	int i;
	int view_pos;
	int aux_pos=0;
	int screen_y = 45;
	int screen_x = 38;

	/* Draw background image */
	load_bmp_8bpp(gp2x_screen8,gp2xmenu_bmp);

	/* Check Limits */
	if (*pos<0)
		*pos=game_num_avail-1;
	if (*pos>(game_num_avail-1))
		*pos=0;
					   
	/* Set View Pos */
	if (*pos<10) {
		view_pos=0;
	} else {
		if (*pos>game_num_avail-11) {
			view_pos=game_num_avail-21;
			view_pos=(view_pos<0?0:view_pos);
		} else {
			view_pos=*pos-10;
		}
	}

	/* Show List */
	for (i=0;i<NUMGAMES;i++) {
		if (_drivers[i].available==1) {
			if (aux_pos>=view_pos && aux_pos<=view_pos+20) {
				gp2x_gamelist_text_out( screen_x, screen_y, _drivers[i].description);
				if (aux_pos==*pos) {
					gp2x_gamelist_text_out( screen_x-10, screen_y,">" );
					gp2x_gamelist_text_out( screen_x-13, screen_y-1,"-" );
				}
				screen_y+=8;
			}
			aux_pos++;
		}
	}

	if (game_num_avail==0)
	{
		gp2x_gamelist_text_out(35, 110, "NO AVAILABLE GAMES FOUND");
	}

	gp2x_gamelist_text_out( 8*6, (29*8)-6,"iMAME4all v1.4 by D.Valdeita");
}

static void game_list_select (int index, char *game, char *emu) {
	int i;
	int aux_pos=0;
	for (i=0;i<NUMGAMES;i++)
	{
		if (_drivers[i].available==1)
		{
			if(aux_pos==index)
			{
				strcpy(game,_drivers[i].name);
				strcpy(emu,_drivers[i].exe);
				break;
			}
			aux_pos++;
		}
	}
}

static char *game_list_description (int index)
{
	int i;
	int aux_pos=0;
	for (i=0;i<NUMGAMES;i++) {
		if (_drivers[i].available==1) {
			if(aux_pos==index) {
				return(_drivers[i].description);
			}
			aux_pos++;
		   }
	}
	return ((char *)0);
}

static int show_options(char *game)
{
	unsigned long ExKey=0;
	int selected_option=0;
	int x_Pos = 41;
	int y_Pos = 58;
	int options_count = 9;
	char text[256];
	FILE *f;
	int i=0;

	if(!safe_render_path)
	  while(ExKey=gp2x_joystick_read(0)&0x8c0ff55){};

	/* Read game configuration */
	sprintf(text,get_documents_path("iOS/%s_v2.cfg"),game);
	f=fopen(text,"r");
	if (f) {
		fscanf(f,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&iOS_video_aspect,&iOS_video_rotate,&iOS_video_sync,
		&iOS_frameskip,&iOS_sound,&iOS_landscape_buttons,&iOS_clock_cpu,&iOS_clock_sound,&i,&iOS_cheat);
		fclose(f);
	}

	if(!safe_render_path)
	{
	   iOS_video_aspect=3;
	}

	while(1)
	{
		/* Draw background image */
		load_bmp_8bpp(gp2x_screen8,gp2xmenu_bmp);

		/* Draw the options */
		gp2x_gamelist_text_out(x_Pos,y_Pos,"Selected Game:\0");
		strncpy (text,game_list_description(last_game_selected),33);
		text[32]='\0';
		gp2x_gamelist_text_out(x_Pos,y_Pos+10,text);

		/* (1) Video Aspect */
		switch (iOS_video_aspect)
		{
			case 0: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+30,"Video Aspect  Original"); break;
			case 1: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+30,"Video Aspect  Ratio Not Kept"); break;
			case 2: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+30,"Video Aspect  With Cropping"); break;
			case 3: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+30,"Video Aspect  Fixed 320x240"); break;
		}

		/* (2) Video Rotation */
		switch (iOS_video_rotate)
		{
			case 0: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+40,"Video Rotate  No"); break;
			case 1: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+40,"Video Rotate  Yes"); break;
			case 2: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+40,"Video Rotate  TATE"); break;
		}
		
		/* (3) Video Sync */
		switch (iOS_video_sync)
		{
			case 0: gp2x_gamelist_text_out(x_Pos,y_Pos+50, "Video Sync    Normal"); break;
			case 1: gp2x_gamelist_text_out(x_Pos,y_Pos+50, "Video Sync    DblBuf"); break;
			case -1: gp2x_gamelist_text_out(x_Pos,y_Pos+50,"Video Sync    OFF"); break;
		}
		
		/* (4) Frame-Skip */
		if(iOS_frameskip==-1) {
			gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+60, "Frame-Skip    Auto");
		}
		else{
			gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+60,"Frame-Skip    %d",iOS_frameskip);
		}

		/* (5) Sound */
		switch(iOS_sound)
		{
			case 0: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","OFF"); break;

			case 1: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (11 KHz fast)"); break;
			case 2: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (22 KHz fast)"); break;
			case 3: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (33 KHz fast)"); break;
			case 4: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (44 KHz fast)"); break;

			case 5: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (11 KHz)"); break;
			case 6: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (22 KHz)"); break;
			case 7: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (33 KHz)"); break;
			case 8: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (44 KHz)"); break;

			case 9: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (11 KHz stereo)"); break;
			case 10: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (22 KHz stereo)"); break;
			case 11: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (33 KHz stereo)"); break;
			case 12: gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+70,"Sound         %s","ON (44 KHz stereo)"); break;

		}

		/* (6) Landscape Num Buttons */
		switch (iOS_landscape_buttons)
		{
			case 1: gp2x_gamelist_text_out(x_Pos,y_Pos+80, "Landscape     1 Button"); break;
			case 2: gp2x_gamelist_text_out(x_Pos,y_Pos+80, "Landscape     2 Buttons"); break;
			case 3: gp2x_gamelist_text_out(x_Pos,y_Pos+80, "Landscape     3 Buttons"); break;
			case 4: gp2x_gamelist_text_out(x_Pos,y_Pos+80, "Landscape     4 Buttons"); break;
		}

		/* (7) CPU Clock */
		gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+90,"CPU Clock     %d%%",iOS_clock_cpu);

		/* (8) Audio Clock */
		gp2x_gamelist_text_out_fmt(x_Pos,y_Pos+100,"Audio Clock   %d%%",iOS_clock_sound);


		/* (9) Cheats */
		if (iOS_cheat)
			gp2x_gamelist_text_out(x_Pos,y_Pos+110,"Cheats        ON");
		else
			gp2x_gamelist_text_out(x_Pos,y_Pos+110,"Cheats        OFF");
	
		gp2x_gamelist_text_out(x_Pos,y_Pos+140,"Press B to confirm, X to return\0");

		/* Show currently selected item */
		gp2x_gamelist_text_out(x_Pos-16,y_Pos+(selected_option*10)+30," >");

		gp2x_video_flip();

		if(safe_render_path)
		{
		   while(gp2x_joystick_read(0)&0x8c0ff55) { gp2x_timer_delay(150); }
		   while(!(ExKey=gp2x_joystick_read(0)&0x8c0ff55)) { }
		}
		else
		{
		   //ExKey=gp2x_joystick_read(0);
		   //gp2x_timer_delay(150);
		   gp2x_timer_delay(150);
		   ExKey=gp2x_joystick_read(0)&0x8c0ff55;
		}

		if(ExKey & GP2X_DOWN){
			selected_option++;
			selected_option = selected_option % options_count;
		}
		else if(ExKey & GP2X_UP){
			selected_option--;
			if(selected_option<0)
				selected_option = options_count - 1;
		}
		else if(ExKey & GP2X_R || ExKey & GP2X_L || ExKey & GP2X_RIGHT || ExKey & GP2X_LEFT)
		{
			switch(selected_option) {
			case 0:
				if(!safe_render_path)
				{
					iOS_video_aspect=3;
					break;
				}
				if((ExKey & GP2X_R) || (ExKey & GP2X_RIGHT))
				{
					iOS_video_aspect++;
					if (iOS_video_aspect>3)
						iOS_video_aspect=0;
				}
				else
				{
					iOS_video_aspect--;
					if (iOS_video_aspect<0)
						iOS_video_aspect=3;
				}
				break;
			case 1:
				if((ExKey & GP2X_R) || (ExKey & GP2X_RIGHT))
				{
					iOS_video_rotate++;
					if (iOS_video_rotate>2)
						iOS_video_rotate=0;
				}
				else
				{
					iOS_video_rotate--;
					if (iOS_video_rotate<0)
						iOS_video_rotate=2;
				}
				break;
			case 2:
				iOS_video_sync=iOS_video_sync+1;
				if (iOS_video_sync>1)
					iOS_video_sync=-1;
				break;
			case 3:
				/* "Frame-Skip" */
				if(ExKey & GP2X_R || ExKey & GP2X_RIGHT )
				{
					iOS_frameskip ++;
					if (iOS_frameskip>11)
						iOS_frameskip=-1;
				}
				else
				{
					iOS_frameskip--;
					if (iOS_frameskip<-1)
						iOS_frameskip=11;
				}
				break;
			case 4:
				if(ExKey & GP2X_R || ExKey & GP2X_RIGHT)
				{
					iOS_sound ++;
					if (iOS_sound>12)
						iOS_sound=0;
				}
				else
				{
					iOS_sound--;
					if (iOS_sound<0)
						iOS_sound=12;
				}
				break;
			case 5:
				if(ExKey & GP2X_R || ExKey & GP2X_RIGHT)
				{
					iOS_landscape_buttons ++;
					if (iOS_landscape_buttons>4)
						iOS_landscape_buttons=1;
				}
				else
				{
					iOS_landscape_buttons--;
					if (iOS_landscape_buttons<1)
						iOS_landscape_buttons=4;
				}
				break;
			case 6:
				/* "CPU Clock" */
				if(ExKey & GP2X_R || ExKey & GP2X_RIGHT)
				{
					iOS_clock_cpu += 10; /* Add 10% */
					if (iOS_clock_cpu > 200) /* 200% is the max */
						iOS_clock_cpu = 200;
				}
				else
				{
					iOS_clock_cpu -= 10; /* Subtract 10% */
					if (iOS_clock_cpu < 10) /* 10% is the min */
						iOS_clock_cpu = 10;
				}
				break;
			case 7:
				/* "Audio Clock" */
				if(ExKey & GP2X_R || ExKey & GP2X_RIGHT)
				{
					iOS_clock_sound += 10; /* Add 10% */
					if (iOS_clock_sound > 200) /* 200% is the max */
						iOS_clock_sound = 200;
				}
				else{
					iOS_clock_sound -= 10; /* Subtract 10% */
					if (iOS_clock_sound < 10) /* 10% is the min */
						iOS_clock_sound = 10;
				}
				break;
			case 8:
				iOS_cheat=!iOS_cheat;
				break;
			}
		}

		if ((ExKey & GP2X_A) || (ExKey & GP2X_B) || (ExKey & GP2X_PUSH) || (ExKey & GP2X_START))
		{
			/* Write game configuration */
			sprintf(text,get_documents_path("iOS/%s_v2.cfg"),game);
			f=fopen(text,"w");
			if (f) {
				fprintf(f,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",iOS_video_aspect,iOS_video_rotate,iOS_video_sync,
				iOS_frameskip,iOS_sound,iOS_landscape_buttons,iOS_clock_cpu,iOS_clock_sound,i,iOS_cheat);
				fclose(f);
				sync();
			}

			/* Selected game will be run */
			return 1;
		}
		else if ((ExKey & GP2X_X) || (ExKey & GP2X_Y) || (ExKey & GP2X_SELECT))
		{
			/* Return To Menu */
			return 0;
		}
	}
}

static void gp2x_exit(void)
{
}

static void select_game(char *emu, char *game)
{

	unsigned long ExKey;

	/* No Selected game */
	strcpy(game,"builtinn");

	/* Clean screen */
	gp2x_video_flip();

	if(!safe_render_path)
	   while(ExKey=gp2x_joystick_read(0)&0x8c0ff55){};

	/* Wait until user selects a game */
	while(1)
	{
		game_list_view(&last_game_selected);
		gp2x_video_flip();

        if(safe_render_path)
        {
			if( (gp2x_joystick_read(0)&0x8c0ff55))
				gp2x_timer_delay(100);
			while(!(ExKey=gp2x_joystick_read(0)&0x8c0ff55))
			{
				if ((ExKey & GP2X_L) && (ExKey & GP2X_R)) { gp2x_exit(); }
			}
        }
        else
        {
			gp2x_timer_delay(100);
        	ExKey=gp2x_joystick_read(0);
        }

		if (ExKey & GP2X_UP) last_game_selected--;
		else if (ExKey & GP2X_DOWN) last_game_selected++;
		else if ((ExKey & GP2X_L) || ExKey & GP2X_LEFT) last_game_selected-=21;
		else if ((ExKey & GP2X_R) || ExKey & GP2X_RIGHT) last_game_selected+=21;
		//if ((ExKey & GP2X_L) && (ExKey & GP2X_R)) gp2x_exit();

		if (((ExKey & GP2X_A) || (ExKey & GP2X_B) || (ExKey & GP2X_PUSH) || (ExKey & GP2X_START)) && game_num_avail!=0)
		{
			/* Select the game */
			game_list_select(last_game_selected, game, emu);

			/* Emulation Options */
			//defaults!

			iOS_video_aspect=0;
			iOS_video_rotate=0;
			iOS_video_sync=0;
			iOS_frameskip=-1;
			iOS_cheat=0;

			if(!safe_render_path)
				iOS_sound = 1;
			else
				iOS_sound = 4;
			if(isIpad)
			{
				iOS_clock_cpu= 100;
				iOS_clock_sound= 100;
				iOS_landscape_buttons=2;
			}
			else
			{
				iOS_clock_cpu= 80;
				iOS_clock_sound= 80;
				iOS_landscape_buttons=2;
			}

			if(show_options(game))
			{
				break;
			}
		}

	}
}

void execute_game (char *playemu, char *playgame)
{
	char *args[255];
	char str[8][64];
	int n=0;
	int i=0;
	
	/* executable */
	args[n]=playemu; n++;

	/* playgame */
	args[n]=playgame; n++;

	args[n]="-depth"; n++;
	if(!safe_render_path)
		args[n]="8";
	else
		args[n]="16";
	n++;

	/* iOS_video_aspect */
	iOS_aspectRatio = iOS_cropVideo = iOS_320x240 = 0;
    if (iOS_video_aspect==0)
	{
    	iOS_aspectRatio = 1;
	}else if(iOS_video_aspect==2){
		iOS_cropVideo = 1;
	}else if(iOS_video_aspect==3){
		iOS_320x240 = 1;
		//printf("fixed %d,%d,%d\n",iOS_aspectRatio,iOS_cropVideo,iOS_320x240);
	}

	/* iOS_video_rotate */
	if ((iOS_video_rotate>=1) && (iOS_video_rotate<=2))
	{
		args[n]="-ror"; n++;
	}

	if ((iOS_video_rotate>=2) && (iOS_video_rotate<=2))
	{
		args[n]="-rotatecontrols"; n++;
	}
	
	/* iOS_video_sync */
    if (iOS_video_sync==1)
	{
		args[n]="-nodirty"; n++;
	}
	else if (iOS_video_sync==-1)
	{
		args[n]="-nothrottle"; n++;
	}
	
	/* iOS_frameskip */
	if (iOS_frameskip>=0)
	{
		args[n]="-frameskip"; n++;
		sprintf(str[i],"%d",iOS_frameskip);
		args[n]=str[i]; i++; n++;
	}

	/* iOS_sound */
	if (iOS_sound==0)
	{
		args[n]="-soundcard"; n++;
		args[n]="0"; n++;
	}
	if ((iOS_sound==1) || (iOS_sound==5) || (iOS_sound==9))
	{
		args[n]="-samplerate"; n++;
		args[n]="11025"; n++;
	}
	if ((iOS_sound==2) || (iOS_sound==6) || (iOS_sound==10))
	{
		args[n]="-samplerate"; n++;
		args[n]="22050"; n++;
	}
	if ((iOS_sound==3) || (iOS_sound==7) || (iOS_sound==11))
	{
		args[n]="-samplerate"; n++;
		args[n]="32000"; n++;
	}
	if ((iOS_sound==4) || (iOS_sound==8) || (iOS_sound==12))
	{
		args[n]="-samplerate"; n++;
		args[n]="44100"; n++;
	}

	if ((iOS_sound>=1) && (iOS_sound<=4))
	{
		args[n]="-fastsound"; n++;
	}
	if (iOS_sound>=9)
	{
		args[n]="-stereo"; n++;
	}

	/* iOS_clock_cpu */
	if (iOS_clock_cpu!=100)
	{
		args[n]="-uclock"; n++;
		sprintf(str[i],"%d",100-iOS_clock_cpu);
		args[n]=str[i]; i++; n++;
	}

	/* iOS_clock_sound */
	if (iOS_clock_cpu!=100)
	{
		args[n]="-uclocks"; n++;
		sprintf(str[i],"%d",100-iOS_clock_sound);
		args[n]=str[i]; i++; n++;
	}

	if (iOS_cheat)
	{
		args[n]="-cheat"; n++;
	}

	if (0)
	{
		args[n]="-romdir"; n++;
		sprintf(str[i],"%s",get_documents_path("roms"));
		args[n]=str[i]; i++; n++;
	}

	args[n]=NULL;
	
	for (i=0; i<n; i++)
	{
		printf("%s ",args[i]);
	}
	printf("\n");
	
	iOS_inGame = 1;
	iOS_exitGame=0;
	//gp2x_set_video_mode(16,320,240);
	iphone_main(n, args);
	gp2x_set_video_mode(16,320,240);
	if(isIpad)
		iOS_landscape_buttons=2;
	else
		iOS_landscape_buttons=2;

	iOS_exitGame=0;
	iOS_inGame = 0;

}


extern "C" int mimain (int argc, char **argv)
{
	FILE *f;


	printf("init iOS frontend\n");
	/* GP2X Initialization */
	gp2x_init(1000,8,22050,16,0,60);

	//hack: por defecto lentos van a 11000
	if(!safe_render_path)
	{
		iOS_sound = 1;
	}
	else
	{
		iOS_sound = 4;
	}

	if(isIpad)
	{
		iOS_clock_cpu= 100;
		iOS_clock_sound= 100;
		iOS_landscape_buttons=2;
	}

	/* Show intro screen */
	gp2x_intro_screen();

	/* Initialize list of available games */
	game_list_init(argc);

	/*
	if (game_num_avail==0)
	{   while(true){
		gp2x_gamelist_text_out(35, 110, "ERROR: NO AVAILABLE GAMES FOUND");
		gp2x_video_flip();
		gp2x_joystick_press(0);
		//gp2x_exit();
		sleep(1);}
		exit(0);
	}
    */

	while(true)
	{
	/* Read default configuration */
	f=fopen(get_documents_path("iOS/mame_v2.cfg"),"r");
	if (f) {
		fscanf(f,"%d",&last_game_selected);
		fclose(f);
	}
	
	/* Select Game */
	select_game(playemu,playgame); 

	/* Write default configuration */
	f=fopen(get_documents_path("iOS/mame_v2.cfg"),"w");
	if (f) {
		fprintf(f,"%d",last_game_selected);
		fclose(f);
		sync();
	}
	
	/* Execute Game */
	execute_game (playemu,playgame);



	}
	exit (0);
}
