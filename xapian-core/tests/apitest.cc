/* apitest.cc: tests the Xapian API
 *
 * Copyright 1999,2000,2001 BrightStation PLC
 * Copyright 2002 Ananova Ltd
 * Copyright 2003,2004,2006,2007 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <config.h>

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <xapian.h>
#include "testsuite.h"
#include "testutils.h"
#include "backendmanager.h"
#include "backendmanager_flint.h"
#include "backendmanager_inmemory.h"
#include "backendmanager_quartz.h"
#include "backendmanager_remoteprog.h"
#include "backendmanager_remotetcp.h"
#include "utils.h"

#include "apitest.h"

static BackendManager * backendmanager;

const char * get_dbtype()
{
    return backendmanager->get_dbtype();
}

Xapian::Database
get_database(const string &dbname)
{
    return backendmanager->get_database(dbname);
}

Xapian::Database
get_database(const string &dbname, const string &dbname2)
{
    vector<string> dbnames;
    dbnames.push_back(dbname);
    dbnames.push_back(dbname2);
    return backendmanager->get_database(dbnames);
}

Xapian::WritableDatabase
get_writable_database(const string &dbname)
{
    return backendmanager->get_writable_database(dbname);
}

Xapian::Database
get_remote_database(const string &dbname, unsigned int timeout)
{
    vector<string> dbnames;
    dbnames.push_back(dbname);
    return backendmanager->get_remote_database(dbnames, timeout);
}

Xapian::Database
get_writable_database_as_database()
{
    return backendmanager->get_writable_database_as_database();
}

Xapian::WritableDatabase
get_writable_database_again()
{
    return backendmanager->get_writable_database_again();
}

#define RUNTESTS(B, T) if (backend.empty() || backend == (B)) {\
    cout << "Running " << #T << " tests with " << (B) << " backend..." << endl;\
    result = max(result, test_driver::run(T##_tests));\
    } else (void)0

#define USE_BACKEND(B, S) ((B).empty() || (B) == (S))

int main(int argc, char **argv)
{
    string backend;
    test_driver::add_command_line_option("backend", 'b', &backend);

    test_driver::parse_command_line(argc, argv);

    string srcdir = test_driver::get_srcdir();

    int result = 0;

    if (USE_BACKEND(backend, "none")) {
	backendmanager = new BackendManager;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("none", nodb);
	RUNTESTS("none", unicode);

	delete backendmanager;
    }

#ifdef XAPIAN_HAS_INMEMORY_BACKEND
    if (USE_BACKEND(backend, "inmemory")) {
	backendmanager = new BackendManagerInMemory;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("inmemory", anydb);
	RUNTESTS("inmemory", specchar);
	RUNTESTS("inmemory", writabledb);
	RUNTESTS("inmemory", localdb);
	RUNTESTS("inmemory", positionaldb);
	RUNTESTS("inmemory", doclendb);
	RUNTESTS("inmemory", collfreq);
	RUNTESTS("inmemory", allterms);
	RUNTESTS("inmemory", multivalue);

	delete backendmanager;
    }
#endif

#ifdef XAPIAN_HAS_FLINT_BACKEND
    if (USE_BACKEND(backend, "flint")) {
	backendmanager = new BackendManagerFlint;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("flint", anydb);
	RUNTESTS("flint", specchar);
	RUNTESTS("flint", writabledb);
	RUNTESTS("flint", localdb);
	RUNTESTS("flint", positionaldb);
	RUNTESTS("flint", doclendb);
	RUNTESTS("flint", collfreq);
	RUNTESTS("flint", allterms);
	RUNTESTS("flint", multivalue);
	RUNTESTS("flint", transactiondb);
	RUNTESTS("flint", flint);

	delete backendmanager;
    }
#endif

#ifdef XAPIAN_HAS_QUARTZ_BACKEND
    if (USE_BACKEND(backend, "quartz")) {
	backendmanager = new BackendManagerQuartz;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("quartz", anydb);
	RUNTESTS("quartz", specchar);
	RUNTESTS("quartz", writabledb);
	RUNTESTS("quartz", localdb);
	RUNTESTS("quartz", positionaldb);
	RUNTESTS("quartz", doclendb);
	RUNTESTS("quartz", collfreq);
	RUNTESTS("quartz", allterms);
	RUNTESTS("quartz", multivalue);
	RUNTESTS("quartz", transactiondb);
	RUNTESTS("quartz", quartz);

	delete backendmanager;
    }
#endif

#ifdef XAPIAN_HAS_REMOTE_BACKEND
    if (USE_BACKEND(backend, "remoteprog")) {
	backendmanager = new BackendManagerRemoteProg;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("remoteprog", anydb);
	RUNTESTS("remoteprog", specchar);
	RUNTESTS("remoteprog", writabledb);
	RUNTESTS("remoteprog", remotedb);
	RUNTESTS("remoteprog", positionaldb);
	RUNTESTS("remoteprog", doclendb);
	RUNTESTS("remoteprog", collfreq);
	RUNTESTS("remoteprog", allterms);
	RUNTESTS("remoteprog", multivalue);
	RUNTESTS("remoteprog", transactiondb);

	delete backendmanager;
    }

    if (USE_BACKEND(backend, "remotetcp")) {
	backendmanager = new BackendManagerRemoteTcp;
	backendmanager->set_datadir(srcdir + "/testdata/");

	RUNTESTS("remotetcp", anydb);
	RUNTESTS("remotetcp", specchar);
	RUNTESTS("remotetcp", writabledb);
	RUNTESTS("remotetcp", remotedb);
	RUNTESTS("remotetcp", positionaldb);
	RUNTESTS("remotetcp", doclendb);
	RUNTESTS("remotetcp", collfreq);
	RUNTESTS("remotetcp", allterms);
	RUNTESTS("remotetcp", multivalue);
	RUNTESTS("remotetcp", transactiondb);

	delete backendmanager;
    }
#endif

    return result;
}
