//
// Created by ebeuque on 24/06/2020.
//

#ifndef STARDEPS_FORMULASTEP_H
#define STARDEPS_FORMULASTEP_H

#include <QList>

#include "FormulaStepAction.h"

class FormulaStep
{
public:
    FormulaStep();
    virtual ~FormulaStep();

    void setStep(const QString& szStep);
    const QString& getStep() const;

    void setPlaformList(const QStringList& listPlatforms);
    const QStringList& getPlaformList() const;

	void setOptionsList(const QStringList& listOptions);
	const QStringList& getOptionsList() const;

    void setFormulaStepActionList(const FormulaStepActionList& listAction);
    const FormulaStepActionList& getFormulaStepActionList() const;

    bool acceptPlatform(const QString& szPlatform) const;
	bool acceptOptions(const QStringList& listOptions) const;

private:
    QString m_szStep;

    // Platforms filter
    QStringList m_listPlatforms;

	// Options filter
	QStringList m_listOptions;

    // List of actions
    FormulaStepActionList m_listStepAction;
};

class FormulaStepList : public QList<FormulaStep>
{
public:
    FormulaStepList();
    virtual ~FormulaStepList();
};

#endif //STARDEPS_FORMULASTEP_H
