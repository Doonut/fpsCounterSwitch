#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <switch.h>

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(NULL);
	int frames = 0;
    struct timeval secTime, now;
    gettimeofday(&secTime, NULL);
	// Main loop
	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();
		
		gettimeofday(&now, NULL);
    	if (now.tv_usec <= secTime.tv_usec){
      		frames = frames + 1;
    	}else{
			consoleClear();
      		printf("\x1b[22;36HFPS: %d\n", frames);
      		gettimeofday(&secTime, NULL);
      		frames = 0;
    	}

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu
		
		gfxFlushBuffers();
		//gfxSwapBuffers();
		//gfxWaitForVsync();
	}

	gfxExit();
	return 0;
}

