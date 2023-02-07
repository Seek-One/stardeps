//
// Created by ebeuque on 06/02/23.
//

#ifndef STARDEPS_PACKAGEOPTION_H
#define STARDEPS_PACKAGEOPTION_H

#include <QString>

class PackageOption
{
public:
	PackageOption();
	PackageOption(const QString& szPackageOption);
	virtual ~PackageOption();

	const QString& getOptionName() const;
	const QStringList& getModes() const;

private:
	QString m_szOptionName;
	QStringList m_listModes;
};


#endif //STARDEPS_PACKAGEOPTION_H
