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

	QString toString() const;

private:
	QString m_szPackage;
	QString m_szVersionMin;
	QString m_szVersionMax;
};

class PackageDependencyList : public QList<PackageDependency>
{
public:
	PackageDependencyList();
	virtual ~PackageDependencyList();
};

#endif /* SRC_PACKAGE_PACKAGEDEPENDENCY_H_ */
