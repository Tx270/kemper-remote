#include "menu_core.h"
#include "menu_root.h"
#include "../hal/display_driver.h"
#include "../hal/input.h"
#include "../ui/home_screen.h"

GEM_u8g2 gem(u8g2);

static const unsigned long MENU_TIMEOUT_MS = 5000;

enum UiState { UI_HOME, UI_MENU };

static UiState uiState = UI_HOME;
static unsigned long lastActivityTime = 0;

void menuCore_init() {
    gem.init();
    gem.invertKeysDuringEdit(true); // invert input for rotary encoder

    uiState = UI_HOME;
    lastActivityTime = millis();
    homeScreen_draw();
}

void menuCore_update() {
    unsigned long now = millis();
    byte key;
    bool gotKey = false;

    if (uiState == UI_HOME) {
        gotKey = input_poll(key);
    } else if (uiState == UI_MENU) {
        if (gem.readyForKey()) {
            gotKey = input_poll(key);
        }
    }

    if (gotKey) {
        lastActivityTime = now;

        if (uiState == UI_HOME) {
            uiState = UI_MENU;
            gem.setMenuPageCurrent(pageRoot);
            pageRoot.setCurrentMenuItemIndex(0);
            gem.drawMenu();
        } else if (key == GEM_KEY_CANCEL && gem.getCurrentMenuPage() == &pageRoot && !gem.isEditMode()) {
            uiState = UI_HOME;
            homeScreen_draw();      
        } else {
            gem.registerKeyPress(key);
        }
    }

    if (uiState == UI_MENU && (now - lastActivityTime >= MENU_TIMEOUT_MS)) {
        uiState = UI_HOME;
        homeScreen_draw();
    }

    // To make the home screen show live-updating content later (a
    // clock, sensor readings, etc.), add a throttled redraw here, e.g.:
    //
    //   static unsigned long lastHomeDraw = 0;
    //   if (uiState == UI_HOME && now - lastHomeDraw >= 1000) {
    //       lastHomeDraw = now;
    //       homeScreen_draw();
    //   }
}
