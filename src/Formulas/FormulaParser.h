/*
 * FormulaParser.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAPARSER_H_
#define SRC_FORMULAS_FORMULAPARSER_H_

#include <QString>
#include <QSharedPointer>

class Formula;
class FormulaStep;
class FormulaCommands;
class FormulaDependenciesList;
class FormulaVariableList;

class FormulaParser
{
public:
	FormulaParser();
	virtual ~FormulaParser();

	const QSharedPointer<Formula>& getFormula() const;

	bool parse(const QString& szFilePath);

private:
	bool parseSCM(const QJsonObject& objectRoot);
	bool parseDependencies(const QJsonObject& objectRoot, FormulaDependenciesList& listDependencies);
	bool parseOptions(const QJsonObject& objectRoot);
	bool parseRecipes(const QJsonObject& objectRoot);
	bool parseRecipe(const QJsonArray& objectRoot);
    bool parseStep(const QJsonObject& objectRoot, FormulaStep& formulaStep);
	bool parseCommands(const QJsonArray& arrayCommands, FormulaCommands& listCommands);
	bool parseVars(const QJsonObject& objectRoot, FormulaVariableList& listVariable);

private:
	QSharedPointer<Formula> m_pFormula;
};

#endif /* SRC_FORMULAS_FORMULAPARSER_H_ */
