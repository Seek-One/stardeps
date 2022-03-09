//
// Created by ebeuque on 24/06/2020.
//

#include "FormulaStepAction.h"

FormulaStepAction::FormulaStepAction()
{
    m_iActionType = ActionUnknown;
}

FormulaStepAction::~FormulaStepAction()
{

}

void FormulaStepAction::setActionType(FormulaStepAction::ActionType iActionType)
{
    m_iActionType = iActionType;
}

FormulaStepAction::ActionType FormulaStepAction::getActionType() const
{
    return m_iActionType;
}

void FormulaStepAction::setCommandList(const FormulaCommands& listCommands)
{
    m_listCommand = listCommands;
}

const FormulaCommands& FormulaStepAction::getCommandList() const
{
    return m_listCommand;
}


void FormulaStepAction::setDirectory(const QString& szDirectory)
{
	m_szDirectory = szDirectory;
}

const QString& FormulaStepAction::getDirectory() const
{
	return m_szDirectory;
}

void FormulaStepAction::setSources(const QStringList& listSources)
{
	m_listSources = listSources;
}

const QStringList& FormulaStepAction::getSources() const
{
	return m_listSources;
}

void FormulaStepAction::setDestination(const QString& szDestination)
{
	m_szDestination = szDestination;
}

const QString& FormulaStepAction::getDestination() const
{
	return m_szDestination;
}

void FormulaStepAction::setAction(const QString& szActionType, const QString& szAction)
{
    if(szActionType == "cmd"){
        setActionType(ActionCommand);
        m_listCommand.append(szAction);
    }
	if(szActionType == "chdir"){
		setActionType(ActionChangeDirectory);
		m_szDirectory = szAction;
	}
	if(szActionType == "copy"){
		setActionType(ActionCopy);
		QStringList tokens = szAction.split(" ");
		if(tokens.count() >= 2){
			m_szDestination = tokens.last();
			tokens.removeLast();
			m_listSources = tokens;
		}
	}
}

void FormulaStepAction::setAction(const QString& szActionType, const QStringList& listAction)
{
    if(szActionType == "cmd"){
        setActionType(ActionCommand);
        m_listCommand.append(listAction);
    }
}

FormulaStepActionList::FormulaStepActionList()
{

}

FormulaStepActionList::~FormulaStepActionList()
{

}