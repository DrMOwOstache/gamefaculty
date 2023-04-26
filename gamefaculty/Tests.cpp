#include "Test.h"

#if ENABLE_TESTS >0
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "Character.h"
#include "Knight.h"
#include "Wizard.h"

#define FIRST_TEST Character_test
#define MAXSCORE 36
#define CHARITY 10

using namespace std;

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e
{
	Character_test = 0,
	Wizard_test,
	Knight_test,
    NUM_TESTS,
};

string testName(int test)
{
	if (test == Character_test)
		return "Character_test";
	if (test == Wizard_test)
		return "Wizard_test";
	if (test == Knight_test)
		return "Knight_test";

	return "";
}

uint8_t runTest(int test) {

    Character peasant;
    Wizard mage;
    Knight fighter;

    switch (test)
    {
    case Character_test:
    {
        peasant = Character("Bob", 10, 1);
        if (peasant.getHealth() != 10)
            return 1;
        if (peasant.getLevel() != 1)
            return 2;
        if (peasant.getName() != "Bob")
            return 3;

        peasant.setHealth(90);
        peasant.setLevel(10);
        peasant.setName("Neil");

        if (peasant.getHealth() != 90)
            return 4;
        if (peasant.getLevel() != 10)
            return 5;
        if (peasant.getName() != "Neil")
            return 6;
        return 0;
    }
    case Wizard_test:
    {
        std::vector<std::string> sp{ "fireball","poison splash","fire bolt","burning hands" };
        mage = Wizard("Bob", 10, 2, 20, sp, 6);
        if (mage.getHealth() != 10)
            return 1;
        if (mage.getLevel() != 1)
            return 2;
        if (mage.getName() != "Bob")
            return 3;
        if (!mage.castSpell(sp[1]))
            return 4;
    }

    default:
        break;
    }
}
    
void segfault_handler(int signal) { // everyone knows what this is
    testStatus = 255;
    longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
    if (disable_exit_handler)
        return; // allow this to be disabled
    testStatus = 255;
    longjmp(test_crash, 2);
}

void run_classes_tests(bool verbose)
{

    testsPassed = 0;
    disable_exit_handler = 0;
    atexit(exit_attempt_handler);
    signal(SIGSEGV, segfault_handler);

    for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {

        uint8_t fail_type;
        try {

            testStatus = runTest(i);
            fail_type = setjmp(test_crash);
        }
        catch (...) {
            testStatus = 255;
            fail_type = 3;
        }
        if (verbose) { // it's verbose mode
            cout << "Test " + testName(i) + ": "
                << (testStatus == 0 ? GREEN "PASSED" NC : RED "FAILED" NC);
            if (testStatus == 255) {
                cout << ": due to a " RED
                    << (fail_type == 1
                        ? "segfault"
                        : (fail_type == 2
                            ? "program exit"
                            : (fail_type == 3 ? "exception being thrown"
                                : "program interruption")))
                    << NC << endl;
                cout << "\nWARNING: Program will now stop running tests\n" << endl;
                break;
            }
            else if (testStatus != 0) {
                cout << ": test " CYAN << testStatus << NC << endl;
            }
            else {
                cout << endl;
            }
        }
        if (testStatus == 0) {
            testsPassed++;
        }
    }

    disable_exit_handler = 1;

    uint8_t totalScore = (MAXSCORE - NUM_TESTS * 3) + testsPassed * 3;
    if (testsPassed == 0)
        totalScore = 0;

    if (verbose && testStatus != 255)
        cout << "\nYou passed " << unsigned(testsPassed) << " out of " << NUM_TESTS << " tests" << endl;
    else if (testStatus == 255) {
        totalScore = CHARITY; // charity points
        if (verbose)
            cout << RED "Receiving charity points because your program crashes" NC << endl << endl;
    }

}
#endif // ENABLE_TESTS >0
