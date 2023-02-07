//
// Created by ebeuque on 06/02/23.
//

#ifndef STARDEPS_PACKAGEOPTIONLIST_H
#define STARDEPS_PACKAGEOPTIONLIST_H

#include <QList>

#include "PackageOption.h"

class PackageOptionList : public QList<PackageOption>
{
public:
	PackageOptionList();
	virtual ~PackageOptionList();

	bool contains(const QString& szOptionName) const;
	QStringList getModes(const QString& szOptionName) const;
};

#endif //STARDEPS_PACKAGEOPTIONLIST_H
