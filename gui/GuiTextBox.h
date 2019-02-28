//
// Created by Techdoodle on 2/27/2019.
//

#ifndef COMET_GUITEXTBOX_H
#define COMET_GUITEXTBOX_H


#include "elements/components/GuiFrame.h"

class GuiTextBox : public GuiFrame
{
private:
    string* data;
    int dataLength;
    WORD color;

    void render();
public:
    GuiTextBox(string* data, int dataLength, WORD color);
    ~GuiTextBox();
    void onResize() override;
    void handleInput(int code) override;
};


#endif //COMET_GUITEXTBOX_H
