/*
 * FormulasParser.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Formula.h"

#include "FormulaParser.h"

FormulaParser::FormulaParser(const QString& szPlatformName)
    : m_szPlatformName(szPlatformName)
{

}

FormulaParser::~FormulaParser()
{

}

const QSharedPointer<Formula>& FormulaParser::getFormula() const
{
	return m_pFormula;
}

bool FormulaParser::parse(const QString& szFilePath)
{
	bool bRes = true;

	QByteArray fileData;

	// Load the file data
	QFile file;
	file.setFileName(szFilePath);
	bRes = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if(bRes){
		fileData = file.readAll();
		file.close();
	}

	// Create formula
	if(bRes){
		m_pFormula = QSharedPointer<Formula>(new Formula());
	}

	// JSON document
	QJsonDocument document;
	if(bRes){
		QJsonParseError error;
		document = QJsonDocument::fromJson(fileData, &error);
		if(error.error != QJsonParseError::NoError){
			bRes = false;
			qDebug("[prepare] Error when parsing file: %s at offset: %d", qPrintable(error.errorString()), error.offset);
		}
	}

	if(bRes){
		QJsonObject mainObject = document.object();

		QJsonValue value;
		QString szTmp;

		// Name
		if(mainObject.contains("name")){
			value = mainObject.value("name");
			m_pFormula->setName(value.toString());
		}

		// Home page
		if(mainObject.contains("homepage")){
			value = mainObject.value("homepage");
			m_pFormula->setHomepage(value.toString());
		}

		// SCM
		if(bRes && mainObject.contains("scm")){
			bRes = parseSCM(mainObject.value("scm").toObject());
		}

		// Dependencies
		if(bRes && mainObject.contains("dependencies")){
			FormulaDependenciesList listDependencies;
			bRes = parseDependencies(mainObject.value("dependencies").toObject(), listDependencies);
			if(bRes){
				m_pFormula->setDependenciesList(listDependencies);
			}
		}

		// Options
		if(bRes && mainObject.contains("options")){
			bRes = parseOptions(mainObject.value("options").toObject());
		}

        // Global variables
        if(bRes && mainObject.contains("vars")){
            FormulaVariableList listVars;
            bRes = parseVars(mainObject.value("vars").toObject(), listVars);
            if(bRes){
                m_pFormula->setGlobalVariables(listVars);
            }
        }

		// Recipes
		if(bRes && mainObject.contains("recipes")){
			bRes = parseRecipes(mainObject.value("recipes").toObject());
		}

        // Recipe (new method)
        if(bRes && mainObject.contains("recipe")){
            bRes = parseRecipe(mainObject.value("recipe").toArray());
        }
	}

	return bRes;
}


bool FormulaParser::parseSCM(const QJsonObject& objectRoot)
{
	QJsonValue value;
	QString szTmp;

	// SCM type
	if(objectRoot.contains("type")){
		value = objectRoot.value("type");
		szTmp = value.toString();
		if(szTmp == "git"){
			m_pFormula->setTypeSCM(Formula::SCM_Git);
		}else if(szTmp == "svn"){
			m_pFormula->setTypeSCM(Formula::SCM_Svn);
		}else if(szTmp == "mercurial"){
			m_pFormula->setTypeSCM(Formula::SCM_Mercurial);
        }else if(szTmp == "archive"){
            m_pFormula->setTypeSCM(Formula::SCM_Archive);
        }
	}

	// SCM url
	if(objectRoot.contains("url")){
		value = objectRoot.value("url");
		m_pFormula->setSCMURL(value.toString());
	}

    // SCM default branch
    if(objectRoot.contains("default-branch")){
        value = objectRoot.value("default-branch");
        m_pFormula->setSCMDefaultBranch(value.toString());
    }

	return true;
}

bool FormulaParser::parseOptions(const QJsonObject& objectRoot)
{
	bool bRes = true;

	QJsonObject::const_iterator iter_prop;

	for(iter_prop = objectRoot.constBegin(); iter_prop != objectRoot.constEnd(); ++iter_prop)
	{
		// Target platform
		QString szOptionName = iter_prop.key();

		FormulaOption formulaOption;
		formulaOption.setOptionName(szOptionName);

		// Recipe
		QJsonValue value = iter_prop.value();
		QJsonObject objectOptionDataList = value.toObject();

		if(objectOptionDataList.contains("default-state")){
			formulaOption.setDefaultState(objectOptionDataList.value("default-state").toString() == "enabled");
		}

		if(objectOptionDataList.contains("dependencies")){
			FormulaDependenciesList listDependencies;
			bRes = parseDependencies(objectOptionDataList.value("dependencies").toObject(), listDependencies);
			if(bRes){
				formulaOption.setDependenciesList(listDependencies);
			}
		}

		if(objectOptionDataList.contains("vars")){
			FormulaVariableList listVars;
			if(objectOptionDataList.value("vars").isArray()){
				bRes = parseVars(objectOptionDataList.value("vars").toArray(), listVars);
			}else{
				bRes = parseVars(objectOptionDataList.value("vars").toObject(), listVars);
			}
			if(bRes){
				FormulaOptionRule formulaOptionRule;
				formulaOptionRule.setRuleState(FormulaOptionRule::StateEnabled);
				formulaOptionRule.setVariableList(listVars);
				formulaOption.addOptionRule(formulaOptionRule);
			}
		}

		if(objectOptionDataList.contains("rules")){
			QJsonArray objectArray = objectOptionDataList.value("rules").toArray();
			QJsonArray::const_iterator iter_rule;
			for(iter_rule = objectArray.constBegin(); iter_rule != objectArray.constEnd(); ++iter_rule)
			{
				bRes = parseOptionRule((*iter_rule).toObject(), formulaOption);
				if(!bRes){
					break;
				}
			}
		}

		m_pFormula->addOption(formulaOption);
	}

	return bRes;
}

bool FormulaParser::parseOptionRule(const QJsonObject& objectRoot, FormulaOption& formulaOption)
{
	bool bRes = true;

	FormulaOptionRule formulaOptionRule;

	if(objectRoot.contains("state")){
		FormulaOptionRule::State iState = FormulaOptionRule::StateAll;
		QString szState = objectRoot.value("state").toString();
		if(szState == "enabled"){
			iState = FormulaOptionRule::StateEnabled;
		}
		if(szState == "disabled"){
			iState = FormulaOptionRule::StateDisabled;
		}
		formulaOptionRule.setRuleState(iState);
	}

	if(objectRoot.contains("vars")){
		FormulaVariableList listVars;
		if(objectRoot.value("vars").isArray()){
			bRes = parseVars(objectRoot.value("vars").toArray(), listVars);
		}else{
			bRes = parseVars(objectRoot.value("vars").toObject(), listVars);
		}
		if(bRes){
			formulaOptionRule.setVariableList(listVars);
		}
	}

	if(bRes){
		formulaOption.addOptionRule(formulaOptionRule);
	}

	return bRes;
}

bool FormulaParser::parseDependencies(const QJsonObject& objectRoot, FormulaDependenciesList& listDependencies)
{
	bool bRes = true;

	QJsonObject::const_iterator iter_prop;

	for(iter_prop = objectRoot.constBegin(); iter_prop != objectRoot.constEnd(); ++iter_prop)
	{
		// Target platform
		QString szVersion = iter_prop.key();

		// Recipe
		QJsonValue value = iter_prop.value();
		QJsonObject objectDepsList = value.toObject();

		FormulaDependencies formulaDependencies;

		QJsonObject::const_iterator iter_deps;
		for(iter_deps = objectDepsList.constBegin(); iter_deps != objectDepsList.constEnd(); ++iter_deps) {
			// Package name
			QString szPackageName = iter_deps.key();
			QString szVersionMin;
			QString szVersionMax;

			// Attributes
			QJsonValue value2 = iter_deps.value();

			// If dependencies with attributes
			if (value2.isObject()) {
				QJsonObject objectAttrsList = value2.toObject();

				if (objectAttrsList.contains("min")) {
					szVersionMin = objectAttrsList.value("min").toString();
				}

				if (objectAttrsList.contains("max")) {
					szVersionMax = objectAttrsList.value("max").toString();
				}
			}

			formulaDependencies.addDependency(szPackageName, szVersionMin, szVersionMax);
		}

		listDependencies.addDependencies(szVersion, formulaDependencies);
	}

	return bRes;
}

bool FormulaParser::parseRecipes(const QJsonObject& objectRoot)
{
	bool bRes = true;

	QJsonObject::const_iterator iter_prop;

	for(iter_prop = objectRoot.constBegin(); iter_prop != objectRoot.constEnd(); ++iter_prop)
	{
		// Target platform
		QString szTargetPlatform = iter_prop.key();

		// Recipe
		QJsonValue value = iter_prop.value();
		QJsonObject objectPlatform = value.toObject();

		FormulaRecipe formulaRecipe;

		// Recipes
        if(bRes && objectPlatform.contains("prepare")){
            FormulaCommands listCommands;
            bRes = parseCommands(objectPlatform.value("prepare").toArray(), listCommands);
            formulaRecipe.setPrepareCommands(listCommands);
        }
		if(bRes && objectPlatform.contains("configure")){
			FormulaCommands listCommands;
			bRes = parseCommands(objectPlatform.value("configure").toArray(), listCommands);
			formulaRecipe.setConfigureCommands(listCommands);
		}
		if(bRes && objectPlatform.contains("build")){
			FormulaCommands listCommands;
			bRes = parseCommands(objectPlatform.value("build").toArray(), listCommands);
			formulaRecipe.setBuildCommands(listCommands);
		}
		if(bRes && objectPlatform.contains("install")){
			FormulaCommands listCommands;
			bRes = parseCommands(objectPlatform.value("install").toArray(), listCommands);
			formulaRecipe.setInstallCommands(listCommands);
		}
		m_pFormula->addRecipe(szTargetPlatform, formulaRecipe);
	}

	return true;
}

bool FormulaParser::parseRecipe(const QJsonArray& arrayRoot)
{
    bool bRes = true;

    QJsonArray::const_iterator iter_obj;

    FormulaRecipe formulaRecipe;
    FormulaStepList formulaStepList;

    for(iter_obj = arrayRoot.constBegin(); iter_obj != arrayRoot.constEnd(); ++iter_obj)
    {
        QJsonObject objectStep = iter_obj->toObject();

        FormulaStep formulaStep;
        bRes = parseStep(objectStep, formulaStep);

        formulaStepList.append(formulaStep);
    }

    formulaRecipe.setFormulaSteps(formulaStepList);

    m_pFormula->addRecipe(QString(), formulaRecipe);

    return bRes;
}

bool FormulaParser::parseStep(const QJsonObject& objectRoot, FormulaStep& formulaStep)
{
    bool bRes = true;

    FormulaStepActionList formulaStepActionList;

    if(bRes){
        if(objectRoot.contains("step")){
            formulaStep.setStep(objectRoot.value("step").toString());
        }else{
            bRes = false;
            qCritical("[parser] step attribute is mandatory for step object");
        }
    }

    if(bRes && objectRoot.contains("platforms")){
        QStringList listPlaforms = objectRoot.value("platforms").toString().split(',');
        formulaStep.setPlaformList(listPlaforms);
    }

	if(bRes && objectRoot.contains("options")){
		QStringList listOptions = objectRoot.value("options").toString().split(',');
		formulaStep.setOptionsList(listOptions);
	}

    // Parse action
    if(bRes){
        bRes = parseStepActions(objectRoot, formulaStepActionList);
    }

    if(bRes && objectRoot.contains("actions")){
        QJsonArray actionsArray = objectRoot.value("actions").toArray();

        QJsonArray::const_iterator iter_actions;
        for(iter_actions = actionsArray.constBegin(); iter_actions != actionsArray.constEnd(); ++iter_actions)
        {
            QJsonObject actionObject = (*iter_actions).toObject();
            bRes = parseStepActions(actionObject, formulaStepActionList);
            if(!bRes){
                break;
            }
        }
    }

    formulaStep.setFormulaStepActionList(formulaStepActionList);

    return true;
}

bool FormulaParser::parseStepActions(const QJsonObject& objectRoot, FormulaStepActionList& formulaStepActionList)
{
    bool bRes = true;

    if(bRes && objectRoot.contains("cmd")){
        FormulaStepAction formulaStepAction;
        QJsonValue value = objectRoot.value("cmd");
        bRes = parseStepAction("cmd", value, formulaStepAction);
        formulaStepActionList.append(formulaStepAction);
    }

	if(bRes && objectRoot.contains("chdir")){
		FormulaStepAction formulaStepAction;
		QJsonValue value = objectRoot.value("chdir");
		bRes = parseStepAction("chdir", value, formulaStepAction);
		formulaStepActionList.append(formulaStepAction);
	}

	if(bRes && objectRoot.contains("copy")){
		FormulaStepAction formulaStepAction;
		QJsonValue value = objectRoot.value("copy");
		bRes = parseStepAction("copy", value, formulaStepAction);
		formulaStepActionList.append(formulaStepAction);
	}

    return bRes;
}

bool FormulaParser::parseStepAction(const QString& szCmd, const QJsonValue& value, FormulaStepAction& formulaStepAction)
{
    bool bRes = true;

    if(value.isArray()){
        QJsonArray actionArray = value.toArray();
        QStringList listAction;
        QJsonArray::const_iterator iter_action;
        for(iter_action = actionArray.constBegin(); iter_action != actionArray.constEnd(); ++iter_action) {
            listAction.append((*iter_action).toString());
        }
        formulaStepAction.setAction(szCmd, listAction);
    }else{
        QString szAction = value.toString();
        formulaStepAction.setAction(szCmd, szAction);
    }

    return bRes;
}

bool FormulaParser::parseCommands(const QJsonArray& arrayCommands, FormulaCommands& listCommands)
{
	QJsonArray::const_iterator iter_item;
	for(iter_item = arrayCommands.constBegin(); iter_item != arrayCommands.constEnd(); ++iter_item)
	{
		listCommands.append((*iter_item).toString());
	}
	return true;
}

bool FormulaParser::parseVar(const QString& szName, const QJsonObject& object, FormulaVariableList& listVariable)
{
	QString szValue;

	QJsonObject altValue;
	QJsonArray arrayAltValues;
	QJsonArray::const_iterator iter_altValue;

	szValue = object.value("default-value").toString();
	if(object.contains("alternatives-values")){
		arrayAltValues = object.value("alternatives-values").toArray();
		iter_altValue = arrayAltValues.constBegin();
		for(; iter_altValue != arrayAltValues.constEnd(); ++iter_altValue){
			altValue = iter_altValue->toObject();

			if(altValue.contains("platforms")){
				if(altValue.value("platforms").toString() == m_szPlatformName){
					szValue = altValue.value("value").toString();
				}
			}
		}
	}

	listVariable.addVariable(szName, szValue);

	return true;
}

bool FormulaParser::parseVars(const QJsonArray& arrayVars, FormulaVariableList& listVariable)
{
    QString szName;
    QJsonObject object;

    QJsonArray::const_iterator iter_item;
    for(iter_item = arrayVars.constBegin(); iter_item != arrayVars.constEnd(); ++iter_item)
    {
        object = iter_item->toObject();
        szName = object.value("name").toString();
        parseVar(szName, object, listVariable);
    }
    return true;
}

bool FormulaParser::parseVars(const QJsonObject& objectRoot, FormulaVariableList& listVariable)
{
	QString szName;

	QJsonObject::const_iterator iter_item;
	for(iter_item = objectRoot.constBegin(); iter_item != objectRoot.constEnd(); ++iter_item)
	{
		szName = iter_item.key();
		if(iter_item.value().isObject()){
			parseVar(szName, iter_item.value().toObject(), listVariable);
		}else{
			listVariable.addVariable(szName, iter_item.value().toString());
		}
	}
	return true;
}
