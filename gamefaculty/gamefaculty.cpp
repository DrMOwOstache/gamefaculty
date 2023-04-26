#define _CRT_SECURE_DEBUG_NO_WARNINGS
#include "Character.h"
#include "Knight.h"
#include "Wizard.h"
#include "Test.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
#if ENABLE_TESTS > 0
    run_classes_tests(true);
#endif

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
}
