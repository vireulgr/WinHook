#pragma once
#include "framework.h"

// Необходимые атрибуты для того, чтобы функция из библиотеки могла быть использована извне
// Перед каждой функцией, которая будет доступна извне, нужно прописывать этот макрос
// для примера см. ниже функцию SetRemoveHook
#define DllExport extern "C" __declspec(dllexport)

// Функция вешает/убирает глобальныйы хук
DllExport void SetRemoveHook(bool doSet);
