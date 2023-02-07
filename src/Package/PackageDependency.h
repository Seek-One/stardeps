/*
 * PackageDependency.h
 *
 *  Created on: 10 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_PACKAGE_PACKAGEDEPENDENCY_H_
#define SRC_PACKAGE_PACKAGEDEPENDENCY_H_

#include <QString>
#include <QList>

#include "Package/PackageSearchMode.h"

class PackageDependency {
public:
	PackageDependency();
	virtual ~PackageDependency();

	void setPackage(const QString& szPackage);
	const QString& getPackage() const;
	void setVersionMin(const QString& szVersionMin);
	const QString& getVersionMin() const;
	void setVersionMax(const QString& szVersionMax);
	const QString& getVersionMax() const;
	void setPkgConfigName(const QString& szPkgConfigName);
	const QString& getPkgConfigName() const;

	const PackageSearchMode& getSearchMode() const;
	void setSearchMode(const PackageSearchMode& iSearchMode);

	QString toString() const;

	void print() const;

private:
	QString m_szPackage;
	QString m_szVersionMin;
	QString m_szVersionMax;
	QString m_szPkgConfigName;

	PackageSearchMode m_iSearchMode;
};

class PackageDependencyList : public QList<PackageDependency>
{
public:
	PackageDependencyList();
	virtual ~PackageDependencyList();
};

#endif /* SRC_PACKAGE_PACKAGEDEPENDENCY_H_ */
