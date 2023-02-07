//
// Created by ebeuque on 06/02/23.
//

#include "PackageOptionList.h"


PackageOptionList::PackageOptionList()
{

}

PackageOptionList::~PackageOptionList()
{

}

bool PackageOptionList::contains(const QString& szOptionName) const
{
	PackageOptionList::const_iterator iter;
	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		const PackageOption& option = (*iter);
		if(option.getOptionName() == szOptionName){
			return true;
		}
	}
	return false;
}

QStringList PackageOptionList::getModes(const QString& szOptionName) const
{
	PackageOptionList::const_iterator iter;
	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		const PackageOption& option = (*iter);
		if(option.getOptionName() == szOptionName){
			return option.getModes();
		}
	}
	return QStringList();
}