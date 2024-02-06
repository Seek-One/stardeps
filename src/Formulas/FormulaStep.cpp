//
// Created by ebeuque on 24/06/2020.
//

#include "Version/VersionHelper.h"

#include "FormulaStep.h"

FormulaStep::FormulaStep()
{

}

FormulaStep::~FormulaStep()
{

}

void FormulaStep::setStep(const QString& szStep)
{
    m_szStep = szStep;
}

const QString& FormulaStep::getStep() const
{
    return m_szStep;
}

void FormulaStep::setPlatformList(const QStringList& listPlatforms)
{
    m_listPlatforms = listPlatforms;
}

const QStringList& FormulaStep::getPlatformList() const
{
    return m_listPlatforms;
}

void FormulaStep::setVersion(const QString& szVersion)
{
	m_szVersion = szVersion;
}

const QString& FormulaStep::getVersion() const
{
	return m_szVersion;
}

void FormulaStep::setOptionsList(const QStringList& listOptions)
{
	m_listOptions = listOptions;
}

const QStringList& FormulaStep::getOptionsList() const
{
	return m_listOptions;
}

void FormulaStep::setFormulaStepActionList(const FormulaStepActionList& listAction)
{
    m_listStepAction = listAction;
}

const FormulaStepActionList& FormulaStep::getFormulaStepActionList() const
{
    return m_listStepAction;
}

bool FormulaStep::acceptPlatform(const QString& szPlatform) const
{
    bool bRes = true;
    if(!m_listPlatforms.isEmpty()) {
        bRes = m_listPlatforms.contains(szPlatform);
    }
    return bRes;
}

bool FormulaStep::acceptVersion(const QString& szPackageVersion) const
{
	bool bRes = true;
	if(!m_szVersion.isEmpty()) {
		if(!VersionHelper::checkVersion(szPackageVersion, m_szVersion)){
			bRes = false;
		}
	}
	return bRes;
}

bool FormulaStep::acceptOptions(const PackageOptionList& listOptions) const
{
	bool bRes = true;

	QStringList::const_iterator iter;
	for(iter = m_listOptions.constBegin(); iter != m_listOptions.constEnd(); ++iter)
	{
		if(!listOptions.contains(*iter)){
			bRes = false;
			break;
		}
	}

	return bRes;
}

FormulaStepList::FormulaStepList()
{

}

FormulaStepList::~FormulaStepList()
{

}