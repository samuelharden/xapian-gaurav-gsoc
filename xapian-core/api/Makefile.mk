noinst_HEADERS +=\
	api/documentterm.h\
	api/documentvaluelist.h\
	api/editdistance.h\
	api/emptypostlist.h\
	api/leafpostlist.h\
	api/maptermlist.h\
	api/mapbigramlist.h\
	api/omenquireinternal.h\
	api/postlist.h\
	api/queryinternal.h\
	api/queryvector.h\
	api/replication.h\
	api/termlist.h\
	api/bigramlist.h\
	api/vectortermlist.h

EXTRA_DIST +=\
	api/dir_contents\
	api/Makefile

lib_src +=\
	api/compactor.cc\
	api/decvalwtsource.cc\
	api/documentvaluelist.cc\
	api/editdistance.cc\
	api/emptypostlist.cc\
	api/error.cc\
	api/errorhandler.cc\
	api/expanddecider.cc\
	api/keymaker.cc\
	api/leafpostlist.cc\
	api/matchspy.cc\
	api/omdatabase.cc\
	api/omdocument.cc\
	api/omenquire.cc\
	api/positioniterator.cc\
	api/postingiterator.cc\
	api/postingsource.cc\
	api/postlist.cc\
	api/query.cc\
	api/queryinternal.cc\
	api/registry.cc\
	api/replication.cc\
	api/sortable-serialise.cc\
	api/termiterator.cc\
	api/bigramiterator.cc\
	api/termlist.cc\
	api/bigramlist.cc\
	api/valueiterator.cc\
	api/valuerangeproc.cc\
	api/valuesetmatchdecider.cc\
	api/vectortermlist.cc\
	api/version.cc
