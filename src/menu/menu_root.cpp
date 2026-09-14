#include "menu_root.h"
#include "GEMPage.h"
#include "../app/app_state.h"
#include "../app/settings_controller.h"
#include "menu/menu_buttons.h"

GEMPage pageRoot("Settings");

GEMItem itemGoButtons("Edit Buttons", pageButtons);
GEMItem itemWifi("WiFi", appState.enableWifi, settingsController_onEnableWifiChanged);
GEMItem itemUpdates("Updates", appState.acceptUpdates, settingsController_onAcceptUpdatesChanged);
GEMItem itemBrightness("Brightness", appState.brightness, settingsController_onBrightnessChanged);

void rootMenu_init() {
    pageRoot.addMenuItem(itemGoButtons);
    pageRoot.addMenuItem(itemBrightness);
    pageRoot.addMenuItem(itemWifi);
    pageRoot.addMenuItem(itemUpdates);
}