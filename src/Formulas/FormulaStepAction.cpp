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