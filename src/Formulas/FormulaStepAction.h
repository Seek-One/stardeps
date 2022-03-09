//
// Created by ebeuque on 24/06/2020.
//

#ifndef STARDEPS_FORMULASTEPACTION_H
#define STARDEPS_FORMULASTEPACTION_H

#include "FormulaCommands.h"

class FormulaStepAction
{
public:
    enum ActionType {
        ActionUnknown,
        ActionCommand,
        ActionChangeDirectory,
        ActionCopy,
    };

public:
    FormulaStepAction();
    virtual ~FormulaStepAction();

    void setActionType(FormulaStepAction::ActionType iActionType);
    FormulaStepAction::ActionType getActionType() const;

    void setCommandList(const FormulaCommands& listCommand);
    const FormulaCommands& getCommandList() const;

	void setDirectory(const QString& szDirectory);
	const QString& getDirectory() const;

	void setSources(const QStringList& listSources);
	const QStringList& getSources() const;

	void setDestination(const QString& szDestination);
	const QString& getDestination() const;

    void setAction(const QString& szActionType, const QString& szAction);
    void setAction(const QString& szActionType, const QStringList& listAction);

private:
    FormulaStepAction::ActionType m_iActionType;

    // Actions commands
    FormulaCommands m_listCommand;

    // Action change directory
    QString m_szDirectory;

    // Action copy
    QStringList m_listSources;
    QString m_szDestination;
};

class FormulaStepActionList : public QList<FormulaStepAction>
{
public:
    FormulaStepActionList();
    virtual ~FormulaStepActionList();
};

#endif //STARDEPS_FORMULASTEPACTION_H
