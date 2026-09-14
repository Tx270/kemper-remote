#include "menu_root.h"
#include "GEMPage.h"
#include "../app/app_state.h"
#include "../app/settings_controller.h"

GEMPage pageRoot("Settings");

GEMItem itemWifi("Enable WiFi:", appState.enableWifi, settingsController_onEnableWifiChanged);
GEMItem itemUpdates("Accept Updates:", appState.acceptUpdates, settingsController_onAcceptUpdatesChanged);
GEMItem itemBrightness("Brightness:", appState.brightness, settingsController_onBrightnessChanged);

void rootMenu_init() {
    pageRoot.addMenuItem(itemBrightness);
    pageRoot.addMenuItem(itemWifi);
    pageRoot.addMenuItem(itemUpdates);
}