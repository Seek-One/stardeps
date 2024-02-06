//
// Created by ebeuque on 24/06/2020.
//

#ifndef STARDEPS_FORMULASTEP_H
#define STARDEPS_FORMULASTEP_H

#include <QList>

#include "Package/PackageOptionList.h"

#include "FormulaStepAction.h"

class FormulaStep
{
public:
    FormulaStep();
    virtual ~FormulaStep();

    void setStep(const QString& szStep);
    const QString& getStep() const;

    void setPlatformList(const QStringList& listPlatforms);
    const QStringList& getPlatformList() const;

	void setVersion(const QString& szVersion);
	const QString& getVersion() const;

	void setOptionsList(const QStringList& listOptions);
	const QStringList& getOptionsList() const;

    void setFormulaStepActionList(const FormulaStepActionList& listAction);
    const FormulaStepActionList& getFormulaStepActionList() const;

    bool acceptPlatform(const QString& szPlatform) const;
	bool acceptVersion(const QString& szVersion) const;
	bool acceptOptions(const PackageOptionList& listOptions) const;

private:
    QString m_szStep;

    // Platforms filter
    QStringList m_listPlatforms;

	// Version filter
	QString m_szVersion;

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
