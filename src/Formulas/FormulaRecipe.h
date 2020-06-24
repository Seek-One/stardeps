/*
 * FormulaRecipe.h
 *
 *  Created on: 20 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULARECIPE_H_
#define SRC_FORMULAS_FORMULARECIPE_H_

#include <QString>
#include <QSharedPointer>
#include <QList>
#include <QMap>

#include "FormulaStep.h"
#include "FormulaCommands.h"

class FormulaRecipe;

class FormulaRecipe {
public:
	FormulaRecipe();
	virtual ~FormulaRecipe();

    void setFormulaSteps(const FormulaStepList& listStep);
    const FormulaStepList& getFormulaSteps() const;

    FormulaStepActionList getFormulaStepActionList(const QString& szStep, const QString& szPlatform) const;

	void setPrepareCommands(const FormulaCommands& listCommands);
	const FormulaCommands& getPrepareCommands() const;
	void setConfigureCommands(const FormulaCommands& listCommands);
	const FormulaCommands& getConfigureCommands() const;
	void setBuildCommands(const FormulaCommands& listCommands);
	const FormulaCommands& getBuildCommands() const;
	void setInstallCommands(const FormulaCommands& listCommands);
	const FormulaCommands& getInstallCommands() const;

private:
    FormulaStepList m_listStep;
	FormulaCommands m_listPrepareCommands;
	FormulaCommands m_listConfigureCommands;
	FormulaCommands m_listBuildCommands;
	FormulaCommands m_listInstallCommands;
};

class FormulaRecipeList : public QMap<QString,FormulaRecipe>
{
public:
	FormulaRecipeList();
	virtual ~FormulaRecipeList();
};

#endif /* SRC_FORMULAS_FORMULARECIPE_H_ */
