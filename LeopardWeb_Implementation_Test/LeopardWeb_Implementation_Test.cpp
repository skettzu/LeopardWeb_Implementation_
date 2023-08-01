#include "pch.h"
#include "CppUnitTest.h"
#include "sqlite3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LeopardWebImplementationTest
{
	sqlite3* LW_DB;
	int exit = 1;
	// Don't forget to close db at the end of program
	exit = sqlite3_open("LeopardWeb_Implementation.db", &LW_DB);

	// User Tests
	TEST_CLASS(User_Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			User user();
			string username = "bob123";
			string pwd = "bob";
			int result = 1;
			Assert::AreEqual(1, user.Login(LW_DB, username, pwd)
		}
	};

	// Admin Tests
	TEST_CLASS(Admin_Test)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

		}
	};

	// Student Tests
	TEST_CLASS(Student_Test)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};

	// Instructor Tests
	TEST_CLASS(Instructor_Test)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};
}
