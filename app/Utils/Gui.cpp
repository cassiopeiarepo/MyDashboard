#include "app/Utils/Gui.h"
#include <QtGlobal>

void Gui::updateSize(int new_width, int new_height) {
    width = new_width;
    height = new_height;
    prev_size = size;

    int max = qMax(width, height);
    if (max < 900) {
        size = GUI_MINI;
    } else if (max < 1600) {
        size = GUI_MIDI;
    } else {
        size = GUI_MAXI;
    }
}

void Gui::updateGlobalPos(QPoint _gloabal_pos) {
    global_pos = _gloabal_pos;
}