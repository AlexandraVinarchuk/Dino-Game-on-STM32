#pragma once

void ClearScreenFunc(unsigned char  buf[256], int& res, hid_device* handle);
void SpawnRoad(unsigned char  buf[256], int& res, hid_device* handle);
void ObjLogic(bool &anyObj, unsigned char  buf[256], int &x_pos_o, int &y_pos_o, int& GameMode, int& res, hid_device* handle);
void DinoPrint(unsigned char  buf[256], int x_pos, int y_pos, int& res, hid_device* handle, int  sun_ary[21][21]);
