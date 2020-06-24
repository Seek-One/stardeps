//
// Created by ebeuque on 24/06/2020.
//

#ifndef STARDEPS_COMMANDCLEAN_H
#define STARDEPS_COMMANDCLEAN_H

#include "AbstractPackageCommand.h"

class CommandClean : public AbstractPackageCommand {
public:
    CommandClean();
    virtual ~CommandClean();

protected:
    bool doExecute();

private:
    bool removeDir(const QString& szDirName);
};


#endif //STARDEPS_COMMANDCLEAN_H
