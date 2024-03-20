//
// Created by symct on 2024/3/20.
//

#ifndef CLF_CBF_LEARN_DISPLAY_H
#define CLF_CBF_LEARN_DISPLAY_H

#include "vector"
#define VISIBLE 1
#define INVISIBLE 0

void displayState(int textVisible, int imageVisible);
void displayVData(int textVisible, int imageVisible, std::vector<float>& vData);
void displayUData(int textVisible, int imageVisible, std::vector<float>& uData);
void displayDelta(int textVisible, int imageVisible, std::vector<float>& delta);
#endif //CLF_CBF_LEARN_DISPLAY_H
