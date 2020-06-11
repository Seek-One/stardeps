
#include <QtTest>

#include "Formulas/FormulaDependenciesTestCase.h"
#include "Version/VersionHelperTestCase.h"

// Enable memory leak detection
#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// Must be done after pre-build lirary
#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define new DEBUG_NEW
#endif // _DEBUG

int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && defined(_DEBUG)
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	QCoreApplication app(argc, argv);

	bool bShowUsage = false;

	char* iQtArgsV[2];
	int iQtArgsCount = 0;

	// Load params
	if(argc < 1){
		bShowUsage = true;
	}else{
		for(int i=1; i<argc; i++){
			if(QString::compare(argv[i], "--help") == 0){
				bShowUsage = true;
				break;
			}else if(QString::compare(argv[i], "-maxwarnings") == 0){
				iQtArgsV[0] = (char*)"-maxwarnings";
				iQtArgsV[1] = argv[i+1];
				i++;
			}
		}
	}

	if(bShowUsage){
		qDebug("[Main] Usage: %s", argv[0]);
		return -1;
	}

	int iRes = 0;

	if(iRes == 0){
		VersionHelperTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		FormulaDependenciesTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	return (iRes == 0 ? 0 : -1);
}
