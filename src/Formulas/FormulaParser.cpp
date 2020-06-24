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

FormulaParser::FormulaParser()
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

        // Options
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
        }else if(szTmp == "archive"){
            m_pFormula->setTypeSCM(Formula::SCM_Archive);
        }
	}

	// SCM url
	if(objectRoot.contains("url")){
		value = objectRoot.value("url");
		m_pFormula->setSCMURL(value.toString());
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

		if(objectOptionDataList.contains("dependencies")){
			FormulaDependenciesList listDependencies;
			bRes = parseDependencies(objectOptionDataList.value("dependencies").toObject(), listDependencies);
			if(bRes){
				formulaOption.setDependenciesList(listDependencies);
			}
		}

		if(objectOptionDataList.contains("vars")){
			FormulaVariableList listVars;
			bRes = parseVars(objectOptionDataList.value("vars").toObject(), listVars);
			if(bRes){
				formulaOption.setVariableList(listVars);
			}
		}

		m_pFormula->addOption(formulaOption);
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
		for(iter_deps = objectDepsList.constBegin(); iter_deps != objectDepsList.constEnd(); ++iter_deps)
		{
			// Package name
			QString szPackageName = iter_deps.key();
			QString szVersionMin;
			QString szVersionMax;

			// Attributes
			QJsonValue value2 = iter_deps.value();
			QJsonObject objectAttrsList = value2.toObject();

			if(objectAttrsList.contains("min")){
				szVersionMin = objectAttrsList.value("min").toString();
			}

			if(objectAttrsList.contains("max")){
				szVersionMax = objectAttrsList.value("max").toString();
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
        QJsonObject object = iter_obj->toObject();
        QJsonObject::const_iterator iter_prop;

        for(iter_prop = object.constBegin(); iter_prop != object.constEnd(); ++iter_prop)
        {
            FormulaStep formulaStep;

            // Target platform
            QString szStep = iter_prop.key();
            formulaStep.setStep(szStep);

            QJsonValue value = iter_prop.value();
            QJsonObject objectStep = value.toObject();
            bRes = parseStep(objectStep, formulaStep);

            formulaStepList.append(formulaStep);
        }
    }

    formulaRecipe.setFormulaSteps(formulaStepList);

    m_pFormula->addRecipe(QString(), formulaRecipe);

    return bRes;
}

bool FormulaParser::parseStep(const QJsonObject& objectRoot, FormulaStep& formulaStep)
{
    FormulaStepActionList formulaStepActionList;

    QJsonObject::const_iterator iter_prop;
    for(iter_prop = objectRoot.constBegin(); iter_prop != objectRoot.constEnd(); ++iter_prop)
    {
        FormulaStepAction formulaStepAction;

        // Target platform
        QString szActionType = iter_prop.key();
        if(iter_prop.value().isArray()){
            QJsonArray actionArray = iter_prop.value().toArray();
            QStringList listAction;

            QJsonArray::const_iterator iter_action;
            for(iter_action = actionArray.constBegin(); iter_action != actionArray.constEnd(); ++iter_action) {
                listAction.append((*iter_action).toString());
            }

            formulaStepAction.setAction(szActionType, listAction);
        }else{
            QString szAction = iter_prop.value().toString();
            formulaStepAction.setAction(szActionType, szAction);
        }

        formulaStepActionList.append(formulaStepAction);
    }

    formulaStep.setFormulaStepActionList(formulaStepActionList);

    return true;
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

bool FormulaParser::parseVars(const QJsonObject& objectRoot, FormulaVariableList& listVariable)
{
	QJsonObject::const_iterator iter_item;
	for(iter_item = objectRoot.constBegin(); iter_item != objectRoot.constEnd(); ++iter_item)
	{
		listVariable.insert(iter_item.key(), iter_item.value().toString());
	}
	return true;
}
