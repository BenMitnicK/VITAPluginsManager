/*
 * 
 * Made by NeoLTK with xerpi draw
 * 
 */

#include "header.h"

void init() {
	struct stat st = {0};

	if (stat(disablePath, &st) == -1) {
		sceIoMkdir(disablePath,  0777);
	}

	init_video();
}

void finish() {
	end_video();
	sceKernelExitProcess(0);
}

int main(int argc, char *argv[]) {
	init();

	Plugins plugins[50];
	
	Menu panelMenu[3];
	panelMenu[0].title = "Enable";
	panelMenu[1].title = "Disable";
	panelMenu[2].title = "Scan plugins";
	panelMenu[2].function = &securityCheck;

	RightPanel rightPanel;
	rightPanel.panelMenu = panelMenu;
	rightPanel.active = false;
	rightPanel.navOffset = 0;

	Manager pluginsManager;
	pluginsManager.plugins = plugins;
	pluginsManager.rightPanel = &rightPanel;
	pluginsManager.navOffset = 0;
	pluginsManager.active = true;

	getPlugins(plugins);
	getConfigs(plugins);

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

	while(pluginsManager.active){
		sceCtrlPeekBufferPositive(0, &(pluginsManager.pad), 1);
		clear_screen();

		controle(&pluginsManager);
		menuDraw(&pluginsManager);		

		swap_buffers();
		sceDisplayWaitVblankStart();
	}

	finish();
	return 0;
}
