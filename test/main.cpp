
#include <QtTest>

#include <Toolkit/QtCore/Logging/Logging.h>

#include "Model/CashEventTestCase.h"
#include "Model/NamedDeviceTestCase.h"
#include "Model/ProgramTestCase.h"
#include "Model/RecordingFileTestCase.h"
#include "Model/RecordingEventTestCase.h"
#include "Database/ConfigurationExportTestCase.h"
#include "Database/DatabaseTestCase.h"
#include "Frame/FrameBufferingTestCase.h"
#include "Global/QTestUserEventFilterApplication.h"
#include "License/MachineCodeTestCase.h"
#include "Recording/RecordingFileManagerTestCase.h"
#include "Recording/RecordingFrameLoaderTestCase.h"
#include "Recording/RecordingFrameFilterTestCase.h"
#include "Recording/RecordingFileAccessorTestCase.h"
#include "Recording/RecordingFileIndexFileBuilderTestCase.h"
#include "Recording/RecordingFileMetaReaderWriterTestCase.h"
#include "Recording/RecordingFileObjectHelperTestCase.h"
#include "Recording/RecordingFileReaderWriterTestCase.h"
#include "Recording/RecordingFileIndexTestCase.h"
#include "RecordingEvent/RecordingEventFileIndexBuilderTestCase.h"
#include "Concurrent/RecordingFileDataListExtractPeriodMatcherTestCase.h"
#include "Monitoring/MonitoringTestCase.h"
#include "Programmation/ProgrammationTestCase.h"
#include "Purge/PurgeDataTestCase.h"
#include "Diffusion/DiffusionRecordingThreadTestCase.h"
#include "Diffusion/DiffusionFrameNotifierTestCase.h"
#include "Diffusion/DiffusionStreamHandlerTestCase.h"
#include "Limits/LimitsTestCase.h"

#include "Common.h"

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

	app.installEventFilter(QTestUserEventFilterApplication::instance());

	TkCore::Logger::setLogFunc(QtTkCoreDefaultLoggerFunc);
	QtInstallMsgHandler(QtConsoleMsgHandlerFunc, QtTkCoreConsoleLoggerFunc);

	bool bShowUsage = false;

	// Test file
	const char* szDirTestFile = NULL;

	char* iQtArgsV[2];
	int iQtArgsCount = 0;

	// Load params
	if(argc < 2){
		bShowUsage = true;
	}else{
		for(int i=1; i<argc; i++){
			if(p_strcasecmp(argv[i], "--help") == 0){
				bShowUsage = true;
				break;
			}else if(p_strcasecmp(argv[i], "-maxwarnings") == 0){
				iQtArgsV[0] = (char*)"-maxwarnings";
				iQtArgsV[1] = argv[i+1];
				i++;
			}else{
				szDirTestFile = argv[i];
			}
		}
	}

	if(szDirTestFile==NULL){
		bShowUsage = true;
	}

	if(bShowUsage){
		qDebug("[Main] Usage: %s testfile_directory", argv[0]);
		return -1;
	}

	qDebug("[Main] Using test directory: %s", szDirTestFile);

	int iRes = 0;

	QDir dirTmp(DIRECTORY_TMP);
	if(!dirTmp.exists()){
		iRes = (dirTmp.mkpath(".") ? 0 : -1);
		if(iRes != 0){
			qCritical("Cannot create tmp directory");
		}
	}

	QDir dirTmpRecording(DIRECTORY_RECORDING_TMP);
	if(!dirTmpRecording.exists()){
		iRes = (dirTmpRecording.mkpath(".") ? 0 : -1);
		if(iRes != 0){
			qCritical("Cannot create tmp recording directory");
		}
	}

	QDir dirTmpRecordingEvents(DIRECTORY_RECORDINGEVENTS_TMP);
	if(!dirTmpRecordingEvents.exists()){
		iRes = (dirTmpRecordingEvents.mkpath(".") ? 0 : -1);
		if(iRes != 0){
			qCritical("Cannot create tmp recording events directory");
		}
	}

	if(iRes == 0){
		CashEventTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		NamedDeviceTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		MachineCodeTestCase tc(szDirTestFile);
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		ProgramTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileReaderWriterTestCase tc(szDirTestFile);
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileMetaReaderWriterTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileAccessorTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileIndexFileBuilderTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingEventIndexFileBuilderTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileObjectHelperTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileIndexTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	// Disable test with release Win32 due to a dead lock on database commit with jenkins
#if not (defined(WIN32) and not defined(QT_DEBUG))
	if(iRes == 0){
		DatabaseTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		ProgrammationTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		ConfigurationExportTestCase tc(szDirTestFile);
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}
#endif

	if(iRes == 0){
		FrameBufferingTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFrameFilterTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	// Disable test with release Win32 due to a dead lock on database commit with jenkins
#if not (defined(WIN32) and not defined(QT_DEBUG))
	if(iRes == 0){
		RecordingFileManagerTestCase tc(szDirTestFile);
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFrameLoaderTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		DiffusionRecordingThreadTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}
#endif

	if(iRes == 0){
		DiffusionStreamHandlerTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		DiffusionFrameNotifierTestCase tc(szDirTestFile);
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingEventTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	if(iRes == 0){
		RecordingFileDataListExtractPeriodMatcherTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}

	// Disable test with release Win32 due to a dead lock on database commit with jenkins
#if not (defined(WIN32) and not defined(QT_DEBUG))
	if(iRes == 0){
		PurgeDataTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, iQtArgsV);
	}
#endif

	if(iRes == 0){
		MonitoringTestCase tc;
		iRes = QTest::qExec(&tc, iQtArgsCount, argv);
	}

#ifndef WIN32 // Not passing with wine
//	if(iRes == 0){
//		LimitsTestCase tc;
//		iRes = QTest::qExec(&tc, iQtArgsCount, argv);
//	}
#endif

	if(dirTmpRecordingEvents.exists()){
		if(!dirTmpRecordingEvents.rmpath(".")){
			iRes = -1;
			qCritical("Cannot remove tmp recording events directory");
		}
	}

	if(dirTmpRecording.exists()){
		if(!dirTmpRecording.rmpath(".")){
			iRes = -1;
			qCritical("Cannot remove tmp recording directory");
		}
	}

	if(dirTmp.exists()){
		if(!dirTmp.rmpath(".")){
			iRes = -1;
			qCritical("Cannot remove tmp directory");
		}
	}

	return (iRes == 0 ? 0 : -1);
}
