#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <cstring>
#include <sstream>

#include "../src/CMailServer.h"

using namespace std;


bool matchOutput(const CMail &mail, const char *str)
{
    ostringstream oss;
    oss << mail;
    return oss.str() == str;
}

TEST_CASE("CMailServer", "[CMailServer]")
{
    CMailServer a;

    SECTION("sendMail")
    {
        a.sendMail(CMail("", "jan", "test mail"));
        CMailIterator b = a.outbox("");
        REQUIRE(b);
        REQUIRE(*b == CMail("", "jan", "test mail"));
    }

    SECTION("copy constructor")
    {
        CMailServer c;
        a = a;
        a = c;
        c = a;
    }
}

TEST_CASE("CMail", "[CMail]")
{
    SECTION("operator==")
    {
        REQUIRE(CMail("john", "peter", "test deadline") == CMail("john", "peter", "test deadline"));
        REQUIRE(!(CMail("john", "peter", "test deadline") == CMail("john", "test deadline", "peter")));
        REQUIRE(!(CMail("john", "peter", "test deadline") == CMail("peter", "john", "test deadline")));
        REQUIRE(!(CMail("john", "peter", "test deadline") == CMail("peter", "test deadline", "john")));
        REQUIRE(!(CMail("john", "peter", "test deadline") == CMail("test deadline", "john", "peter")));
        REQUIRE(!(CMail("john", "peter", "test deadline") == CMail("test deadline", "peter", "john")));
    }
}

TEST_CASE("CMailIterator", "[CMailIterator]")
{
    char from[100], to[100], body[1024];

    CMailServer s0;
    s0.sendMail(CMail("john", "peter", "some important mail"));
    strncpy(from, "john", sizeof(from));
    strncpy(to, "thomas", sizeof(to));
    strncpy(body, "another important mail", sizeof(body));
    s0.sendMail(CMail(from, to, body));
    strncpy(from, "john", sizeof(from));
    strncpy(to, "alice", sizeof(to));
    strncpy(body, "deadline notice", sizeof(body));
    s0.sendMail(CMail(from, to, body));
    s0.sendMail(CMail("alice", "john", "deadline confirmation"));
    s0.sendMail(CMail("peter", "alice", "PR gibberish"));

    CMailIterator i0 = s0.inbox("alice");
    REQUIRE((i0 && *i0 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i0 && *i0 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i0, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE(!++i0);

    CMailIterator i1 = s0.inbox("john");
    REQUIRE((i1 && *i1 == CMail("alice", "john", "deadline confirmation")));
    REQUIRE(matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
    REQUIRE(!++i1);

    CMailIterator i2 = s0.outbox("john");
    REQUIRE((i2 && *i2 == CMail("john", "peter", "some important mail")));
    REQUIRE(matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
    REQUIRE((++i2 && *i2 == CMail("john", "thomas", "another important mail")));
    REQUIRE(matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
    REQUIRE((++i2 && *i2 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
    REQUIRE(!++i2);

    CMailIterator i3 = s0.outbox("thomas");
    REQUIRE(!i3);

    CMailIterator i4 = s0.outbox("steve");
    REQUIRE(!i4);

    CMailIterator i5 = s0.outbox("thomas");
    s0.sendMail(CMail("thomas", "boss", "daily report"));
    REQUIRE(!i5);

    CMailIterator i6 = s0.outbox("thomas");
    REQUIRE((i6 && *i6 == CMail("thomas", "boss", "daily report")));
    REQUIRE(matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
    REQUIRE(!++i6);

    CMailIterator i7 = s0.inbox("alice");
    s0.sendMail(CMail("thomas", "alice", "meeting details"));
    REQUIRE((i7 && *i7 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i7 && *i7 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i7, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE(!++i7);

    CMailIterator i8 = s0.inbox("alice");
    REQUIRE((i8 && *i8 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i8 && *i8 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i8, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE((++i8 && *i8 == CMail("thomas", "alice", "meeting details")));
    REQUIRE(matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
    REQUIRE(!++i8);

    CMailServer s1(s0);
    s0.sendMail(CMail("joe", "alice", "delivery details"));
    s1.sendMail(CMail("sam", "alice", "order confirmation"));
    CMailIterator i9 = s0.inbox("alice");
    REQUIRE((i9 && *i9 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i9 && *i9 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i9, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE((++i9 && *i9 == CMail("thomas", "alice", "meeting details")));
    REQUIRE(matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
    REQUIRE((++i9 && *i9 == CMail("joe", "alice", "delivery details")));
    REQUIRE(matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
    REQUIRE(!++i9);

    CMailIterator i10 = s1.inbox("alice");
    REQUIRE((i10 && *i10 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i10 && *i10 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i10, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE((++i10 && *i10 == CMail("thomas", "alice", "meeting details")));
    REQUIRE(matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
    REQUIRE((++i10 && *i10 == CMail("sam", "alice", "order confirmation")));
    REQUIRE(matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
    REQUIRE(!++i10);

    CMailServer s2;
    s2.sendMail(CMail("alice", "alice", "mailbox test"));
    CMailIterator i11 = s2.inbox("alice");
    REQUIRE((i11 && *i11 == CMail("alice", "alice", "mailbox test")));
    REQUIRE(matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
    REQUIRE(!++i11);

    s2 = s0;
    s0.sendMail(CMail("steve", "alice", "newsletter"));
    s2.sendMail(CMail("paul", "alice", "invalid invoice"));
    CMailIterator i12 = s0.inbox("alice");
    REQUIRE((i12 && *i12 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i12 && *i12 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i12, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE((++i12 && *i12 == CMail("thomas", "alice", "meeting details")));
    REQUIRE(matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
    REQUIRE((++i12 && *i12 == CMail("joe", "alice", "delivery details")));
    REQUIRE(matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
    REQUIRE((++i12 && *i12 == CMail("steve", "alice", "newsletter")));
    REQUIRE(matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
    REQUIRE(!++i12);

    CMailIterator i13 = s2.inbox("alice");
    REQUIRE((i13 && *i13 == CMail("john", "alice", "deadline notice")));
    REQUIRE(matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
    REQUIRE((++i13 && *i13 == CMail("peter", "alice", "PR gibberish")));
    REQUIRE(matchOutput(*i13, "From: peter, To: alice, Body: PR gibberish"));
    REQUIRE((++i13 && *i13 == CMail("thomas", "alice", "meeting details")));
    REQUIRE(matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
    REQUIRE((++i13 && *i13 == CMail("joe", "alice", "delivery details")));
    REQUIRE(matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
    REQUIRE((++i13 && *i13 == CMail("paul", "alice", "invalid invoice")));
    REQUIRE(matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
    REQUIRE(!++i13);
}
