#pragma once
#include "framework.h"

// ����������� �������� ��� ����, ����� ������� �� ���������� ����� ���� ������������ �����
// ����� ������ ��������, ������� ����� �������� �����, ����� ����������� ���� ������
// ��� ������� ��. ���� ������� SetRemoveHook
#define DllExport extern "C" __declspec(dllexport)

// ������� ������/������� ����������� ���
DllExport void SetRemoveHook(bool doSet);
