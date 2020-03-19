/*
 * FormulasParser.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

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
		QJsonObject object;
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
		if(mainObject.contains("scm")){
			value = mainObject.value("scm");
			object = value.toObject();

			// SCM type
			if(object.contains("type")){
				value = object.value("type");
				szTmp = value.toString();
				if(szTmp == "git"){
					m_pFormula->setTypeSCM(Formula::SCM_Git);
				}else if(szTmp == "svn"){
					m_pFormula->setTypeSCM(Formula::SCM_Svn);
				}
			}

			// SCM url
			if(object.contains("url")){
				value = object.value("url");
				m_pFormula->setSCMURL(value.toString());
			}
		}

		/*
		QJsonValue value = sett2.value(QString("name"));
		qWarning() << value;
		QJsonObject item = value.toObject();
		qWarning() << tr("QJsonObject of description: ") << item;

		 in case of string value get value and convert into string
		qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
		QJsonValue subobj = item["description"];
		*/
	}

	return bRes;
}
