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
		}
	}

	// SCM url
	if(objectRoot.contains("url")){
		value = objectRoot.value("url");
		m_pFormula->setSCMURL(value.toString());
	}

	return true;
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
