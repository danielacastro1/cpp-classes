// Title: Lab 2 Call Database Unit Test - lab2unittest.cpp
//
// Purpose: Runs validation tests on the call database component for Lab 2.
//
// Class: CSC 2430 Spring 2019
//
// Author: Max Benson, Modified by Taiwoo Park

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

#include "calldb.h"

void CompareStrings(string expected, string actual);

int main()
{
	CALLDB calldb;
	CALL call;
	stringstream inbuffer1;
	stringstream inbuffer2;
	stringstream inbuffer3;
	string expected;

	// Initialize the call database
	InitCallDB(calldb);

	// Try some calls
	assert(GetCountCallDB(calldb) == 0);
	assert(!GetCallInCallDB(calldb, 0, call));
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+") == -1);

	// Load some calls
	inbuffer1.str("110054 +12062812000 5912\n"
		"110054 +12062812000 xxxx\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n");
	assert(LoadCallDB(calldb, inbuffer1) == 1);
	assert(GetCountCallDB(calldb) == 3);
	assert(GetCallInCallDB(calldb, 0, call));
	assert(call.start == "110054");
	assert(call.phonenum == "+12062812000");
	assert(call.duration == "5912");
	assert(GetDurationCall(call)==5912);
	assert(GetStartCall(call) == "11:00:54");
	assert(GetCountryCodeCall(call) == "NA");
	assert(GetPhoneNumberCall(call) == "(206)-281-2000");
	assert(GetCallInCallDB(calldb, 1, call));
	assert(call.start == "091233");
	assert(call.phonenum == "+33140205990");
	assert(call.duration == "364");
	assert(GetDurationCall(call) == 364);
	assert(GetStartCall(call) == "09:12:33");
	assert(GetCountryCodeCall(call) == "FR");
	assert(GetPhoneNumberCall(call) == "01 40 20 59 90");
	assert(GetCallInCallDB(calldb, 2, call));
	assert(call.start == "145316");
	assert(call.phonenum == "+85223677065");
	assert(call.duration == "180");
	assert(GetDurationCall(call) == 180);
	assert(GetStartCall(call) == "14:53:16");
	assert(GetCountryCodeCall(call) == "HK");
	assert(GetPhoneNumberCall(call) == "2367 7065");
	assert(!GetCallInCallDB(calldb, 3, call));
	assert(FindByPhonePrefixInCallDB(calldb, 0, "") == 0);
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+1") == 0);
	assert(FindByPhonePrefixInCallDB(calldb, 1, "+1") == -1);
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+33") == 1);
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+8") == 2);
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+9") == -1);

	// Load some more calls
	inbuffer2.str("110054 +12062812000 5912\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n");
	assert(LoadCallDB(calldb, inbuffer2) == 0);
	assert(GetCountCallDB(calldb) == 6);
	assert(GetCallInCallDB(calldb, 3, call));
	assert(call.start == "110054");
	assert(call.phonenum == "+12062812000");
	assert(call.duration == "5912");
	assert(GetCallInCallDB(calldb, 4, call));
	assert(call.start == "091233");
	assert(call.phonenum == "+33140205990");
	assert(call.duration == "364");
	assert(GetCallInCallDB(calldb, 5, call));
	assert(call.start == "145316");
	assert(call.phonenum == "+85223677065");
	assert(call.duration == "180");
	assert(!GetCallInCallDB(calldb, 6, call));
	assert(FindByPhonePrefixInCallDB(calldb, 0, "+1") == 0);
	assert(FindByPhonePrefixInCallDB(calldb, 1, "+1") == 3);
	assert(FindByPhonePrefixInCallDB(calldb, 4, "+1") == -1);

	// Load some more calls
	inbuffer3.str("110054 +12062812000 5912\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n"
		"091233 +33140205990 364\n"
		"145316 +85223677065 180\n");
	assert(LoadCallDB(calldb, inbuffer3) == 2);
	assert(GetCountCallDB(calldb) == 15);

	// Congratulate
	cerr << "Good work, you passed the unit tests." << endl;

    return 0;
}
