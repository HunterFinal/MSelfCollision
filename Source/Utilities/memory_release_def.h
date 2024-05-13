#pragma once

#define SAVE_RELEASE

#define SAVE_DELETE(p) {if((p)!=nullptr){delete (p);(p) = nullptr;}}
#define SAVE_DELETE_ARRAY(p) {if((p)!=nullptr){delete[] (p);(p) = nullptr;}}
