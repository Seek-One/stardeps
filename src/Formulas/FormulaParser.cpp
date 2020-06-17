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
			qDebug("[prepare] Error when parsing file: %s", qPrintable(error.errorString()));
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

		// Recipes
		if(bRes && mainObject.contains("recipes")){
			bRes = parseRecipe(mainObject.value("recipes").toObject());
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

bool FormulaParser::parseRecipe(const QJsonObject& objectRoot)
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
