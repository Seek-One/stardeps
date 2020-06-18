/*
 * QApplicationSettings.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_GLOBAL_QAPPLICATIONSETTINGS_H_
#define SRC_GLOBAL_QAPPLICATIONSETTINGS_H_

#include <QDir>

class QApplicationSettings {
public:
	QApplicationSettings();
	virtual ~QApplicationSettings();

private:
	// Application dir
	static QDir g_applicationDir;
	static QDir g_applicationDataDir;
	static int g_applicationVerboseMode;
	static QDir g_applicationCustomFormulasDir;

public:
	static const QDir& applicationDir();
	static void setApplicationDir(const QDir& dir);

	static const QDir& applicationDataDir();
	static void setApplicationDataDir(const QDir& dir);

    static const QDir& applicationCustomFormulasDir();
    static void setApplicationCustomFormulasDir(const QDir& dir);

    static QDir applicationFormulasPath();

    static int applicationVerboseMode();
    static void setApplicationVerboseMode(const int iVerboseMode);
};

#endif /* SRC_GLOBAL_QAPPLICATIONSETTINGS_H_ */
