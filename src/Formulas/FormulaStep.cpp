//
// Created by ebeuque on 24/06/2020.
//

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

void FormulaStep::setPlaformList(const QStringList& listPlatforms)
{
    m_listPlatforms = listPlatforms;
}

const QStringList& FormulaStep::getPlaformList() const
{
    return m_listPlatforms;
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

FormulaStepList::FormulaStepList()
{

}

FormulaStepList::~FormulaStepList()
{

}