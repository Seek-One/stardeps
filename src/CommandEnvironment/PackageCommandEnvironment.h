/*
 * PackageCommandEnvironment.h
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDENVIRONMENT_PACKAGECOMMANDENVIRONMENT_H_
#define SRC_COMMANDENVIRONMENT_PACKAGECOMMANDENVIRONMENT_H_

#include <QDir>

#include "AbstractCommandEnvironment.h"

#include "Formulas/Formula.h"

class PackageCommandEnvironment : public AbstractCommandEnvironment
{
public:
	PackageCommandEnvironment();
	virtual ~PackageCommandEnvironment();

	void setPackageName(const QString& szPackageName);
	const QString& getPackageName() const;

	void setPackageVersion(const QString& szVersion);
	const QString& getPackageVersion() const;

	QString getPackageNameVersion() const;
	static QString getPackageNameVersion(const QString& szPackageName, const QString& szPackageVersion);

	void addPackageOption(const QString& szOption);
	const QStringList& getPackageOptions() const;

	const QSharedPointer<Formula>& getFormula() const;

	QDir getRootPackageDir(const QString& szPackageName, const QString& szVersion) const;
	QDir getSourcePackageDir(const QString& szPackageName, const QString& szVersion) const;
	QDir getBuildPackageDir(const QString& szPackageName, const QString& szVersion) const;
	QDir getReleasePackageDir(const QString& szPackageName, const QString& szVersion) const;

protected:
	virtual bool doProcessArgument(int i, const QString& szArg);
	virtual bool doLoad();

private:
	bool loadFormula(const QString& szPackageName, QSharedPointer<Formula>& pFormula);
	bool checkDependencies(const QSharedPointer<Formula>& pFormula);
	bool checkDependencyPresent(const PackageDependency& dependency, QDir& pathOut, QString& szOutVersion);

	enum FindMode {
	    FindSource = 1,
	    FindRelease = 2,
	};
	bool findPackageVersions(const QString& szPackageName, FindMode iMode, QList<QString>& listVersions);

private:
	QString m_szPackageName;
	QString m_szPackageVersion;
	QStringList m_listPackageOptions;

	QSharedPointer<Formula> m_pFormula;
};

#endif /* SRC_COMMANDENVIRONMENT_PACKAGECOMMANDENVIRONMENT_H_ */
