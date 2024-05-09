#pragma once

#define SAVE_DELETE_ARRAY(p) {if((p)!=nullptr){delete[] (p);(p) = nullptr;}}
