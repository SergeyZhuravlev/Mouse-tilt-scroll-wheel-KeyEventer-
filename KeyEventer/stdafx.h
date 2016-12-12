// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>
#include <shellapi.h>

// Файлы заголовков C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <tchar.h>
#include <CppLinq.h>
#include <thread>
#include <assert.h>
#include "resource.h"
#include "ISettings.h"
#include "ISystemEventer.h"
#include "IEventer.h"
#include "IExecuter.h"


// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
