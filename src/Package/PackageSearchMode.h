//
// Created by ebeuque on 07/02/23.
//

#ifndef STARDEPS_PACKAGESEARCHMODE_H
#define STARDEPS_PACKAGESEARCHMODE_H

#include <QString>

class PackageSearchMode {
public:
	enum SearchMode {
		All = 0,
		Environment = 1,
		System = 2,
		Default = Environment
	};

	PackageSearchMode();
	PackageSearchMode(SearchMode iSearchMode);
	virtual ~PackageSearchMode();

	static PackageSearchMode fromString(const QString& szSearchMode);
	void setFromString(const QString& szSearchMode);
	QString toString() const;

	bool operator==(const PackageSearchMode& other) const;
	bool operator==(const PackageSearchMode::SearchMode& iSearchMode) const;
	PackageSearchMode& operator=(const PackageSearchMode& other);
	PackageSearchMode& operator=(const PackageSearchMode::SearchMode& iSearchMode);

private:
	SearchMode m_iMode;
};


#endif //STARDEPS_PACKAGESEARCHMODE_H
